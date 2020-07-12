#ifndef TEXT_H
#define TEXT_H

#include "stds.h"

extern app_t app;

extern void init_fonts( void );

extern void free_fonts( void );

extern void draw_text( f32 x, f32 y, SDL_Color *c, const char *font_directory, 
                       uint16_t font_size, const char *str, ... );

extern void get_string_size( const char *str, const char *font_name, uint16_t font_size,
                             int32_t *stored_width, int32_t *stored_height );

#endif // TEXT_H
