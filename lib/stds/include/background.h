#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../include/draw.h"
#include "stds.h"

extern struct app_t app;

extern void Stds_AddParallaxBackground( const char *bg_directory, const size_t n,
                                        const float default_scroll_speed,
                                        const float modified_scroll_speeds[],
                                        const bool  is_infinite );

extern void Stds_ParallaxBackgroundUpdate( struct parallax_background_t *parallax );

extern void Stds_ParallaxBackgroundDraw( const struct parallax_background_t *parallax );

extern struct background_t *Stds_AddBackground( const char *bg_directory );

extern void Stds_BackgroundUpdate( struct background_t *bg );

extern void Stds_BackgroundDraw( const struct background_t *bg );

extern void Stds_BackgroundDie( struct background_t *bg );

#endif // BACKGROUND_H
