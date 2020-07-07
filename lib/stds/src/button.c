#include "../include/button.h"

void
update_buttons( void ) {
  button_t *b;
  for ( b = app.button_head.next; b != NULL; b = b->next ) {
    button_update( b );
  }
}

void
draw_buttons( void ) {
  button_t *b;

  for ( b = app.button_head.next; b != NULL; b = b->next ) {
    button_draw( b );
  }
}

button_t *
add_button( float x, float y, uint32_t w, uint32_t h, bool is_filled, const char *font_path,
            uint16_t size, SDL_Color *fc, const char *text ) {
  button_t *button;

  button = malloc( sizeof( button_t ) );

  if ( button == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                 "Error: could not allocate memory for button_t, %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( button, 0, sizeof( button_t ) );
  SDL_Color black    = {0, 0, 0};
  button->rect.x     = ( int32_t ) x;
  button->rect.y     = ( int32_t ) y;
  button->rect.w     = w;
  button->rect.h     = h;
  button->font_path  = font_path;
  button->font_size  = size;
  button->color      = black;
  button->text_color = *fc;
  button->is_filled  = is_filled;

  int fw, fh;
  get_string_size( text, button->font_path, button->font_size, &fw, &fh );

  button->text_x = button->rect.x + ( ( button->rect.w - fw ) / 2 );
  button->text_y = button->rect.y + ( ( button->rect.h - fh ) / 2 );

  return button;
}

button_t *
add_button_texture( float x, float y, const char *file_path, const char *font_path, uint16_t size,
                    SDL_Color *fc, const char *text ) {
  button_t *button;

  button = malloc( sizeof( button_t ) );

  if ( button == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                 "Error: could not allocate memory for button_t, %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( button, 0, sizeof( button_t ) );

  button->texture_id                  = 0;
  button->texture[button->texture_id] = load_texture( file_path );

  button->rect.x     = ( int32_t ) x;
  button->rect.y     = ( int32_t ) y;
  button->font_path  = font_path;
  button->font_size  = size;
  button->scale_x    = 1.0f;
  button->scale_y    = 1.0f;
  button->text       = text;
  button->text_color = *fc;

  SDL_QueryTexture( button->texture[button->texture_id], NULL, NULL, &button->rect.w,
                    &button->rect.h );

  int fw, fh;
  get_string_size( text, button->font_path, button->font_size, &fw, &fh );

  button->text_x = button->rect.x + ( ( button->rect.w - fw ) / 2 );
  button->text_y = button->rect.y + ( ( button->rect.h - fh ) / 2 );

  return button;
}

void
button_update( button_t *b ) {}

void
button_draw( button_t *b ) {
  if ( b->texture[b->texture_id] != NULL ) {
    blit_texture_scaled( b->texture[b->texture_id], b->rect.x, b->rect.y, b->scale_x, b->scale_y,
                         0, SDL_FLIP_NONE, true );
  } else {
    draw_rect( &b->rect, &b->color, b->is_filled, true );
  }
  draw_text( b->text_x, b->text_y, b->text_color.r, b->text_color.g, b->text_color.b, b->font_path,
             b->font_size, b->text );
}

bool
is_mouse_over_button( button_t *b ) {
  int32_t mx = app.mouse.x;
  int32_t my = app.mouse.y;

  int32_t  x = b->rect.x;
  int32_t  y = b->rect.y;
  uint32_t w = b->rect.w;
  uint32_t h = b->rect.h;
  return ( ( mx > x ) && ( mx < x + w ) ) && ( ( my > y ) && ( my < y + h ) );
}

bool
is_button_clicked( button_t *b, int32_t mouse_code ) {
  assert( mouse_code == SDL_BUTTON_LEFT || mouse_code == SDL_BUTTON_RIGHT );

  if ( is_mouse_over_button( b ) && app.mouse.button[mouse_code] ) {
    app.mouse.button[mouse_code] = 0;
    return true;
  }

  return false;
}
