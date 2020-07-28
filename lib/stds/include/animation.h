#ifndef ANIMATION_H
#define ANIMATION_H

#include "draw.h"
#include "stds.h"

extern struct app_t app;

extern struct animation_t *Stds_AddSpritesheet( const char *file_directory, const uint8_t n,
                                                const float frame_time, const uint16_t start_x,
                                                const uint16_t start_y, const size_t rows,
                                                const size_t cols );

extern struct animation_t *Stds_AddAnimation( const char *files_directory, const uint8_t n,
                                              const float frame_time );

extern void Stds_AnimationUpdate( struct animation_t *animation );

extern void Stds_AnimationDraw( const struct animation_t *animation );

extern void Stds_AnimationDie( struct animation_t *animation );

#endif // ANIMATION_H
