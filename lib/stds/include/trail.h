#ifndef TRAIL_H
#define TRAIL_H

#include "draw.h"
#include "stds.h"

extern app_t app;

extern void add_trail( entity_t *parent_entity, int16_t alpha_decay_rate, int16_t starting_alpha,
                       bool is_texture, SDL_RendererFlip flip );

extern void trail_update( trail_t *t );

extern void trail_draw( trail_t *t );

#endif // TRAIL_H