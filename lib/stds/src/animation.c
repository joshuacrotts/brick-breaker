//=============================================================================================//
// FILENAME :       animation.c
//
// DESCRIPTION :
//        This file defines the animation functions associated with the animation_t
//        struct. A note about this is to make sure to define the position, angle, and
//        flip variables accordingly per the entity using the animation. If not, the
//        animation will not move, rotate, etc.
//
// PUBLIC FUNCTIONS :
//        extern animation_t *add_spritesheet( const char *file_directory, uint8_t n, float frame_time,
//                                     uint16_t start_x, uint16_t start_y );
//        extern animation_t *add_animation( const char *files_directory, uint8_t n, float frame_time );
//        extern void animation_update( animation_t *animation );
//        extern void animation_draw( animation_t *animation );
//        extern void animation_die( animation_t *animation );
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

#include "../include/animation.h"

static char input_buffer[MAX_BUFFER_SIZE];

/**
 * Defines a sprite sheet object, where each sprite is beside each
 * other, horizontally.
 *
 * @param const char* file directory of sprite sheet.
 * @param uint8_t number of frames.
 * @param float time spent on an individual frame per second.
 * @param uint16_t = starting top-left x pos of the sprite sheet.
 * @param uint16_t = starting top-left y pos of the sprite sheet.
 *
 * @return animation_t* struct.
 */
animation_t *
add_spritesheet( const char *directory, uint8_t no_of_frames, float frame_delay, uint16_t x,
                 uint16_t y ) {
  animation_t *a;
  a = malloc( sizeof( animation_t ) );

  if ( a == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for animation_t. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( a, 0, sizeof( animation_t ) );

  a->number_of_frames = no_of_frames;
  a->current_texture  = load_texture( directory );
  a->frame_delay      = frame_delay;
  a->frame_timer      = frame_delay * FPS;
  a->start_x          = x;
  a->start_y          = y;

  SDL_QueryTexture( a->current_texture, NULL, NULL, &a->sprite_sheet_width,
                    &a->sprite_sheet_height );

  a->w = a->sprite_sheet_width / no_of_frames;
  a->h = a->sprite_sheet_height;

  a->current_frame_id = 0;
  a->id_flags |= SPRITE_SHEET_MASK;
  a->flags |= ANIMATION_ACTIVE_MASK;

  return a;
}

/**
 * The other way to use animations is to specify the
 * directory of the animation files and the program
 * will load them in. All sprites must have the same
 * leading prefix, with a number at the end indicating
 * their index in the sequence (ex. spr_0, spr_1, spr_2,
 *, etc.).
 *
 * @param const char* directory to files with file prefix.
 * @param uint8_t number of frames.
 * @param float time to spend on a individual frame per second.
 *
 * @return animation_t* struct.
 */
animation_t *
add_animation( const char *directory, uint8_t no_of_frames, float frame_delay ) {
  animation_t *a;
  a = malloc( sizeof( animation_t ) );

  if ( a == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for animation_t. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( a, 0, sizeof( animation_t ) );
  a->frames = malloc( sizeof( SDL_Texture * ) * no_of_frames );

  if ( a->frames == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for a->frames. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  a->number_of_frames = no_of_frames;
  a->frame_delay      = frame_delay;
  a->frame_timer      = frame_delay * FPS;
  a->current_frame_id = 0;

  SDL_QueryTexture( a->current_texture, NULL, NULL, &a->w, &a->h );
  a->id_flags |= STD_ANIMATION_MASK;
  a->flags |= ANIMATION_ACTIVE_MASK;

  const uint8_t NUM_DIGITS = 3;
  char          number_buffer[NUM_DIGITS];
  char *        file_extsn = ".png";
  for ( int i = 0; i < a->number_of_frames; i++ ) {
    sprintf( number_buffer, "%d", i );
    strcpy( input_buffer, directory );
    char *file_name     = strcat( input_buffer, number_buffer );
    char *file_name_ext = strcat( input_buffer, file_extsn );
    a->frames[i]        = load_texture( file_name_ext );
    memset( input_buffer, '\0', sizeof( input_buffer ) );
  }
  a->current_texture = a->frames[0];
  a->default_texture = a->frames[0];

  return a;
}

/**
 * Updates the animation type. If it is a sprite sheet, it
 * advances the coordinate used to keep track of the current
 * sprite in the sheet (i.e. the x coordinate defining the top
 * left). Oppositely, if it is a series of images, we just advance
 * the pointer keeping track of each image. Once the cycle ends,
 * the pointer or coordinate is reset back to 0.
 *
 * @param animation_t* animation to update.
 *
 * @return void.
 */
void
animation_update( animation_t *a ) {
  if ( a->flags & ANIMATION_ACTIVE_MASK )
    a->frame_timer -= 1;

  if ( a->frame_timer < 0 ) {
    // Resets the frame countdown.
    a->frame_timer = a->frame_delay * FPS;
    a->current_frame_id += 1;

    // If we have a spritesheet, we advance x coordinate
    // of the sprite. Otherwise, we advance the pointer
    // referencing which sprite to render in the
    if ( a->id_flags & SPRITE_SHEET_MASK ) {
      a->splice_x += a->sprite_sheet_width / a->number_of_frames;
    } else {
      a->current_texture = a->frames[a->current_frame_id];
    }

    // If we reach the end of the animation sequence,
    // return to the start.
    if ( a->current_frame_id >= a->number_of_frames ) {
      a->current_frame_id = 0;
      if ( a->id_flags & SPRITE_SHEET_MASK ) {
        a->splice_x = 0;
      } else {
        a->current_frame_id = 0;
      }

      // If we have the flag enabled to cycle through the animation
      // only once (and we just finished), deactivate the flag to
      // continue and quit.
      if ( a->cycle_once ) {
        a->flags ^= ANIMATION_ACTIVE_MASK;
        a->cycle_once       = false;
        a->current_frame_id = 0;
        return;
      }
    }
  }
}

/**
 * Draws the animation.
 *
 * @param animation_t* animation to draw.
 *
 * @return void.
 */
void
animation_draw( animation_t *a ) {
  if ( a->flags & ANIMATION_ACTIVE_MASK ) {
    if ( a->id_flags & STD_ANIMATION_MASK ) {
      blit_texture_rotated( a->frames[a->current_frame_id], a->pos_x, a->pos_y, a->angle, a->flip,
                            true );
    } else if ( a->id_flags & SPRITE_SHEET_MASK ) {
      // This rectangle splices the correct frame
      // from the sprite sheet.
      SDL_Rect curr_rect = {( int32_t ) a->splice_x, ( int32_t ) a->splice_y, a->w, a->h};
      blit_rect( a->current_texture, &curr_rect, a->pos_x, a->pos_y, true );
    }
  }
}

/**
 * Destroys and frees the animation passed by the entity.
 *
 * @param animation_t* animation to free from memory.
 *
 * @return void.
 */
void
animation_die( animation_t *a ) {
  for ( int i = 0; i < a->number_of_frames; i++ ) {
    SDL_DestroyTexture( a->frames[i] );
  }

  SDL_DestroyTexture( a->current_texture );
  free( a->frames );
  free( a );
}
