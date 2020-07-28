#ifndef BUTTON_H
#define BUTTON_H

#include "draw.h"
#include "stds.h"
#include "text.h"

extern void update_buttons( void );

extern void draw_buttons( void );

extern struct button_t *add_button( float x, float y, uint32_t w, uint32_t h, bool filled,
                                    const char *font_directory, uint16_t font_size,
                                    SDL_Color *font_color, const char *text );

extern struct button_t *add_button_texture( float x, float y, const char *texture_directory,
                                            const char *font_directory, uint16_t font_size,
                                            SDL_Color *color, const char *text );

extern void button_update( struct button_t *button );

extern void button_draw( struct button_t *button );

extern bool is_mouse_over_button( struct button_t *button );

extern bool is_button_clicked( struct button_t *button, int32_t mouse_code );

#endif // BUTTON_H