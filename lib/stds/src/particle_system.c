#include "../include/particle_system.h"

particle_system_t *
create_particle_system( int32_t max_particles ) {
  particle_system_t *ps;
  ps = malloc( sizeof( particle_system_t ) );

  if ( ps == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                 "Error: could not allocate memory for particle_system_t struct: %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( ps, 0, sizeof( particle_system_t ) );

  ps->particles     = malloc( sizeof( particle_t ) * max_particles );
  ps->max_particles = max_particles;
  ps->alive_count   = 0;
  ps->dead_index    = 0;

  return ps;
}

int32_t
insert_particle( particle_system_t *ps, particle_t *p ) {
  if ( ps->alive_count == ps->max_particles - 1 ) {
    return 1;
  }

  ps->particles[( ps->alive_count )++] = *p;
  return 0;
}

void
particle_system_update( particle_system_t *ps ) {
  for ( int i = 0; i < ps->alive_count; i++ ) {
    particle_t *p = &ps->particles[i];
    if ( p->particle_update ) {
      p->particle_update( p );
    }

    if ( p->flags & DEATH_MASK ) {

      //  Find the rear of the alive particles and grab it.
      ps->dead_index            = --( ps->alive_count );
      particle_t *back_particle = &ps->particles[ps->dead_index];

      // Swap particles.
      particle_t tmp = *back_particle;
      *back_particle = *p;
      *p             = tmp;
    }
  }
}

void
particle_system_draw( particle_system_t *ps ) {
  for ( int i = 0; i < ps->alive_count; i++ ) {
    particle_t *p = &ps->particles[i];
    if ( p->particle_draw ) {
      p->particle_draw( p );
    }
  }
}