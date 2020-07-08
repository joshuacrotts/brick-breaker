#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "stds.h"

/**
 * Initializes a particle system with a size of max particles.
 *
 * @param int32_t max number of particles that can be spawned in the system at
 *        any given time.
 *
 * @return particle_system_t * pointer to emitter.
 */
extern particle_system_t *create_particle_system( int32_t max_particles );

/**
 * Adds a particle to the particle system. Returns 0 if a successful insertion
 * occurred, and 1 otherwise (generally meaning the emitter is full).
 */
extern int32_t insert_particle( particle_system_t *ps, particle_t *p );

/*
 *
 */
extern void particle_system_update( particle_system_t *ps );

/*
 *
 */
extern void particle_system_draw( particle_system_t *ps );

#endif // PARTICLE_SYSTEM_H