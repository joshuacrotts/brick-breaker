#ifndef PARTICLE_H
#define PARTICLE_H

#include "../lib/stds/include/animation.h"
#include "../lib/stds/include/draw.h"
#include "commons.h"

extern app_t app;

extern particle_t  add_particle( f32, f32, f32, f32, f32, f32, uint16_t, uint16_t,
                                 uint16_t, uint8_t, uint8_t, uint8_t, uint8_t, f32, uint32_t );
extern particle_t *add_animated_particle( f32, f32, f32, f32, f32, f32, uint16_t,
                                          uint32_t, animation_t * );
extern void        particle_update( particle_t * );
extern void        particle_draw( particle_t * );
extern void        particle_die( particle_t * );

#endif
