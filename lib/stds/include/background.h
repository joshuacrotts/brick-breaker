#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../include/draw.h"
#include "stds.h"

extern app_t app;

extern void init_parallax_background( const char *bg_directory, size_t n,
                                      float default_scroll_speed, float modified_scroll_speeds[],
                                      bool is_infinite );

extern void parallax_background_update( parallax_background_t *parallax );

extern void parallax_background_draw( parallax_background_t *parallax );

extern background_t *init_background( const char *bg_directory );

extern void background_update( background_t *bg );

extern void background_draw( background_t *bg );

extern void background_die( background_t *bg );

#endif // BACKGROUND_H
