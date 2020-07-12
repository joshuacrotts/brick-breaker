//=============================================================================================//
// FILENAME :       button.c
//
// DESCRIPTION :
//        Defines the functions associated with buttons, and detecting
//        button events like clicking and movement.
//
// PUBLIC FUNCTIONS :
//        void      update_buttons( void );
//        void      draw_buttons( void );
//        button_t *add_button( f32 x, f32 y, uint32_t w, uint32_t h, bool filled,
//                                     const char *font_directory, uint16_t font_size, SDL_Color *font_color,
//                                     const char *text );
//        button_t *add_button_texture( f32 x, f32 y, const char *texture_directory,
//                                             const char *font_directory, uint16_t font_size,
//                                             SDL_Color *color, const char *text );
//        void     button_update( button_t *button );
//        void     button_draw( button_t *button );
//        bool     is_mouse_over_button( button_t *button );
//        bool     is_button_clicked( button_t *button, int32_t mouse_code );
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
// AUTHOR :   Joshua Crotts        START DATE :    22 Jun 2020
//
//=============================================================================================//

#include "../include/button.h"

/**
 * Updates all buttons in the app struct.
 *
 * @param void.
 *
 * @return void.
 */
void
update_buttons( void ) {
  button_t *b;
  for ( b = app.button_head.next; b != NULL; b = b->next ) {
    button_update( b );
  }
}

/**
 * Draws all buttons in the app struct.
 *
 * @param void.
 *
 * @return void.
 */
void
draw_buttons( void ) {
  button_t *b;

  for ( b = app.button_head.next; b != NULL; b = b->next ) {
    button_draw( b );
  }
}

/**
 * Adds a button with no texture. This is useful for buttons that have to change colors overtime, or
 * just don't have an accompanying texture. Make sure to change the color with button->color = ...
 *
 * @param f32 x top-left x pos of button.
 * @param f32 y top-left y pos of button.
 * @param uint32_t w width of button.
 * @param uint32_t h height of button.
 * @param bool true if the button should be filled with color, false otherwise.
 * @param const char* string to font path used for the text.
 * @param uint16_t size of font.
 * @param SDL_Color* color to draw font.
 * @param const char* text to draw.
 *
 * @return button_t pointer.
 */
button_t *
add_button( f32 x, f32 y, uint32_t w, uint32_t h, bool is_filled, const char *font_path,
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

/**
 * Adds a button with a texture.
 *
 * @param f32 x top-left x pos of button.
 * @param f32 y top-left y pos of button.
 * @param const char* string to texture for button.
 * @param const char* string to font path used for the text.
 * @param uint16_t size of font.
 * @param SDL_Color* color to draw font.
 * @param const char* text to draw.
 *
 * @return button_t pointer.
 */
button_t *
add_button_texture( f32 x, f32 y, const char *file_path, const char *font_path, uint16_t size,
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

  int32_t fw, fh;
  get_string_size( text, button->font_path, button->font_size, &fw, &fh );

  button->text_x = button->rect.x + ( ( button->rect.w - fw ) / 2 );
  button->text_y = button->rect.y + ( ( button->rect.h - fh ) / 2 );

  return button;
}

/**
 * Updates the logic for the button parameter.
 *
 * @param button_t* pointer to button struct.
 *
 * @return void.
 */
void
button_update( button_t *b ) {}

/**
 * Draws the button.
 *
 * @param button_t* pointer to button struct.
 *
 * @return void.
 */
void
button_draw( button_t *b ) {
  if ( b->texture[b->texture_id] != NULL ) {
    blit_texture_scaled( b->texture[b->texture_id], b->rect.x, b->rect.y, b->scale_x, b->scale_y, 0,
                         SDL_FLIP_NONE, true );
  } else {
    draw_rect( &b->rect, &b->color, b->is_filled, true );
  }
  draw_text( b->text_x, b->text_y, &b->text_color, b->font_path,
             b->font_size, b->text );
}

/**
 * Determines if the mouse cursor is over the rectangle
 * box associated with the button_t struct.
 *
 * @param button_t* pointer to button struct.
 *
 * @return bool true if mouse is over, false otherwise.
 */
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

/**
 * Determines if the button was clicked on by the provided mouse-code.
 * This should most often be SDL_BUTTON_LEFT for the left mouse button.
 *
 * @param button_t* pointer to button struct.
 * @param int32_t mouse code to test if clicked.
 *
 * @return true if mouse code was used to click, false otherwise.
 */
bool
is_button_clicked( button_t *b, int32_t mouse_code ) {
  assert( mouse_code == SDL_BUTTON_LEFT || mouse_code == SDL_BUTTON_RIGHT );

  if ( is_mouse_over_button( b ) && app.mouse.button[mouse_code] ) {
    app.mouse.button[mouse_code] = 0;
    return true;
  }

  return false;
}
