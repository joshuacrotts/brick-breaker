#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "stds.h"

enum { PS_SUCCESS, PS_FULL, PS_INVALID_FP };

extern struct particle_system_t *Stds_CreateParticleSystem( const int32_t max_particles );

extern int32_t Stds_InsertParticle( struct particle_system_t *ps, const struct particle_t *p );

extern void Stds_ParticleSystemUpdate( struct particle_system_t *ps );

extern void Stds_ParticleSystemDraw( const struct particle_system_t *ps );

#endif // PARTICLE_SYSTEM_H