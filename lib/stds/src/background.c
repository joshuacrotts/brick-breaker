//=============================================================================================//
// FILENAME :       background.c
//
// DESCRIPTION :
//        This file defines the background fuctionality, both regular and parallax.
//
// PUBLIC FUNCTIONS :
//        void init_parallax_background( const char *bg_directory, size_t n,
//                                    f32 default_scroll_speed, f32 modified_scroll_speeds[],
//                                    bool is_infinite );
//        void parallax_background_update( parallax_background_t *parallax );
//        void parallax_background_draw( parallax_background_t *parallax );
//        background_t *init_background( const char *bg_directory );
//        void background_update( background_t *bg );
//        void background_draw( background_t *bg );
//        void background_die( background_t *bg );
//
// NOTES :
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.
//
// AUTHOR :   Joshua Crotts        START DATE :    18 Jun 2020
//
//=============================================================================================//

#include "../include/background.h"

static char input_buffer[MAX_BUFFER_SIZE];

/**
 * Loads in the parallax images specified by the directory.
 * These images should be labeled in back-to-front order.
 * For instance, if we have three layers L0, L1, and L2,
 * L0 should be the layer drawn farthest from the viewport,
 * whereas L2 should be the closest. Make sure that your
 * images all have a common suffix numbering scheme as well,
 * starting at 0.
 *
 * @param const char* string to directory of parallax background images.
 * @param size_t number of parallax frames.
 * @param f32 default scroll speed shared across all frames.
 * @param f32[] array of modified scroll speeds. These values alter
 *        the default scroll speed of each frame. These values
 *        f1 <= f2 <= ... < fn, as implied, should be listed in
 *        back-to-front speed.
 * @param bool infinite_scroll, determining whether two copies of
 *        the image are rendered side-by-side to provide the illusion
 *        of an infinite background.
 */
void
init_parallax_background( const char *directory, size_t count, f32 normal_scroll_speed,
                          f32 scroll_speeds[], bool infinite_scroll ) {

  parallax_background_t *layer;

  const uint8_t NUM_DIGITS = 3;
  char          number_buffer[NUM_DIGITS];
  char *        file_extsn = ".png";

  for ( int i = 0; i < count; i++ ) {
    layer = malloc( sizeof( parallax_background_t ) );

    if ( layer == NULL ) {
      SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                   "Could not allocate memory for parallax_background_t. %s.\n", SDL_GetError() );
      exit( EXIT_FAILURE );
    }

    memset( layer, 0, sizeof( parallax_background_t ) );

    sprintf( number_buffer, "%d", i );
    strcpy( input_buffer, directory );
    char *file_name              = strcat( input_buffer, number_buffer );
    char *file_name_ext          = strcat( input_buffer, file_extsn );
    layer->background            = init_background( file_name_ext );
    layer->parallax_scroll_speed = scroll_speeds[i];
    layer->normal_scroll_speed   = normal_scroll_speed;
    layer->infinite_scroll       = infinite_scroll;

    memset( input_buffer, '\0', sizeof( input_buffer ) );
    app.parallax_tail->next = layer;
    app.parallax_tail       = layer;
  }
}

/**
 * Updates the position of the parallax background element.
 * The offset is applied by multiplying the default scroll speed
 * multiplied by the scroll offset to give the illusion of
 * different scroll rates.
 *
 * @param parallax_backgorund_t pointer to struct.
 *
 * @return void.
 */
void
parallax_background_update( parallax_background_t *p ) {
  if ( !p->infinite_scroll ) {
    p->background->x =
        ( ( 0 - app.camera.x ) * ( p->normal_scroll_speed * p->parallax_scroll_speed ) );

    /* Repositions the background according to where it is relative to the camera. */
    p->background->x = ( f32 ) fmod( p->background->x, p->background->w );
  } else {
    p->background->x -= ( p->normal_scroll_speed * p->parallax_scroll_speed );
    if ( p->background->x < -p->background->w ) {
      p->background->x = 0;
    }
  }
}

/**
 * Draws the parallax background frame. Two copies of the image
 * are drawn to provide the illusion of infinite scrolling if
 * specified by the boolean in the struct.
 *
 * @param parallax_background_t pointer to struct.
 *
 * @return void.
 */
void
parallax_background_draw( parallax_background_t *p ) {
  /* Two copies of the image are drawn to give the illusion of depth and parallax. */
  blit_texture_scaled( p->background->background_texture, p->background->x, p->background->y,
                       p->background->scale_x, p->background->scale_y, 0, SDL_FLIP_NONE, false );
  blit_texture_scaled( p->background->background_texture, p->background->x + p->background->w,
                       p->background->y, p->background->scale_x, p->background->scale_y, 0,
                       SDL_FLIP_NONE, false );
}

/**
 * Initializes the background image specified by char*.
 * It is drawn at (0, 0), or the top-left of the window.
 *
 * @param const char *file location of background image.
 *
 * @return void.
 */
background_t *
init_background( const char *file ) {
  background_t *background;
  background = malloc( sizeof( background_t ) );

  if ( background == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for background_t. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( background, 0, sizeof( background_t ) );

  background->x = 0;
  background->y = 0;

  int32_t w;
  int32_t h;

  background->background_texture = load_texture( file );
  SDL_QueryTexture( background->background_texture, NULL, NULL, &w, &h );

  background->w       = w;
  background->h       = h;
  background->scale_x = 1.0;
  background->scale_y = 1.0;

  return background;
}

/**
 * Continuously updates the position of the background depending
 * on the camera's location. If no camera is used, its offset is
 * 0, thus not moving the background.
 *
 * @param background_t pointer to update.
 *
 * @return void.
 */
void
background_update( background_t *background ) {}

/**
 * Draws the background at its appropriate location specified by the
 * update function.
 *
 * @param background_t pointer to draw.
 *
 * @return void.
 */
void
background_draw( background_t *background ) {
  blit_texture_scaled( background->background_texture, background->x, background->y,
                       background->scale_x, background->scale_y, 0, SDL_FLIP_NONE, false );
}

/**
 * Frees the context of the background struct and image.
 *
 * @param background_t pointer to free.
 *
 * @return void.
 */
void
background_die( background_t *background ) {
  SDL_DestroyTexture( background->background_texture );
  free( background );
}
