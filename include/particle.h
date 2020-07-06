#ifndef PARTICLE_H
#define PARTICLE_H

#include "../lib/stds/include/animation.h"
#include "../lib/stds/include/draw.h"
#include "commons.h"

extern app_t app;

extern entity_t *   add_particle( float, float, float, float, float, float, uint16_t, uint16_t,
                                  uint16_t, uint8_t, uint8_t, uint8_t, uint8_t, float, uint32_t );
extern entity_t *   add_animated_particle( float, float, float, float, float, float, uint16_t,
                                           uint32_t, animation_t * );
extern animation_t *add_animation( char *, uint8_t, float );
extern void         particle_update( entity_t * );
extern void         particle_draw( entity_t * );
extern void         particle_die( entity_t * );

#endif
