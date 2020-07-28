#ifndef PARTICLE_H
#define PARTICLE_H

#include "../lib/stds/include/animation.h"
#include "../lib/stds/include/draw.h"
#include "commons.h"

extern struct app_t app;

extern struct particle_t  add_particle( float, float, float, float, float, float, uint16_t, uint16_t,
                                 uint16_t, uint8_t, uint8_t, uint8_t, uint8_t, float, uint32_t );
extern struct particle_t *add_animated_particle( float, float, float, float, float, float, uint16_t,
                                          uint32_t, struct animation_t * );
extern void        particle_update( struct particle_t * );
extern void        particle_draw( struct particle_t * );
extern void        particle_die( struct particle_t * );

#endif
