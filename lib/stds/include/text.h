#ifndef TEXT_H
#define TEXT_H

#include "stds.h"

extern app_t app;

extern void init_fonts( void );

extern void free_fonts( void );

extern void draw_text( float x, float y, uint8_t r, uint8_t g, uint8_t b,
                       const char *font_directory, uint16_t font_size, const char *str, ... );

extern void get_string_size( const char *str, const char *font_name, uint16_t font_size,
                             int *stored_width, int *stored_height );

#endif
