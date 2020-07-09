#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "stds.h"

enum { PS_SUCCESS, PS_FULL, PS_INVALID_FP };

extern particle_system_t *create_particle_system( int32_t max_particles );

extern int32_t insert_particle( particle_system_t *ps, particle_t *p );

extern void particle_system_update( particle_system_t *ps );

extern void particle_system_draw( particle_system_t *ps );

#endif // PARTICLE_SYSTEM_H