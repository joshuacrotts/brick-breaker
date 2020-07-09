#include "../include/background.h"

static char input_buffer[MAX_BUFFER_SIZE];

void
init_parallax_background( const char *directory, size_t count, float normal_scroll_speed,
                          float scroll_speeds[], bool infinite_scroll ) {

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

void
parallax_background_update( parallax_background_t *p ) {
  if ( !p->infinite_scroll ) {
    p->background->x =
        ( ( 0 - app.camera.x ) * ( p->normal_scroll_speed * p->parallax_scroll_speed ) );
    p->background->x = ( float ) fmod( p->background->x, p->background->w );
  } else {
    p->background->x -= ( p->normal_scroll_speed * p->parallax_scroll_speed );
    if ( p->background->x < -p->background->w ) {
      p->background->x = 0;
    }
  }
}

void
parallax_background_draw( parallax_background_t *p ) {
  blit_texture_scaled( p->background->background_texture, p->background->x, p->background->y,
                       p->background->scale_x, p->background->scale_y, 0, SDL_FLIP_NONE, false );
  blit_texture_scaled( p->background->background_texture, p->background->x + p->background->w,
                       p->background->y, p->background->scale_x, p->background->scale_y, 0,
                       SDL_FLIP_NONE, false );
}

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

  uint32_t w;
  uint32_t h;

  background->background_texture = load_texture( file );
  SDL_QueryTexture( background->background_texture, NULL, NULL, &w, &h );

  background->w       = w;
  background->h       = h;
  background->scale_x = 1.0;
  background->scale_y = 1.0;

  return background;
}

void
background_update( background_t *background ) {}

void
background_draw( background_t *background ) {
  blit_texture_scaled( background->background_texture, background->x, background->y,
                       background->scale_x, background->scale_y, 0, SDL_FLIP_NONE, false );
}

void
background_die( background_t *background ) {
  SDL_DestroyTexture( background->background_texture );
  free( background );
}