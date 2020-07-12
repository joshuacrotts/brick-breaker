#ifndef ANIMATION_H
#define ANIMATION_H

#include "draw.h"
#include "stds.h"

extern app_t app;

extern animation_t *add_spritesheet( const char *file_directory, uint8_t n, f32 frame_time,
                                     uint16_t start_x, uint16_t start_y );

extern animation_t *add_animation( const char *files_directory, uint8_t n, f32 frame_time );

extern void animation_update( animation_t *animation );

extern void animation_draw( animation_t *animation );

extern void animation_die( animation_t *animation );

#endif // ANIMATION_H
