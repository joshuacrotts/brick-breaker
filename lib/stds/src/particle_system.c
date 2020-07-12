//=============================================================================================//
// FILENAME :       particle_system.c
//
// DESCRIPTION :
//        This file defines the particle system backed in static memory.
//
// PUBLIC FUNCTIONS :
//        particle_system_t *create_particle_system( int32_t max_particles );
//        int32_t           insert_particle( particle_system_t *ps, particle_t *p );
//        void              particle_system_update( particle_system_t *ps );
//        void              particle_system_draw( particle_system_t *ps );
//
// NOTES :
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.
//
// AUTHOR :   Joshua Crotts        START DATE :    6 Jul 2020
//
//=============================================================================================//

#include "../include/particle_system.h"

/**
 * Initializes a particle system with a size of max particles.
 *
 * @param int32_t max number of particles that can be spawned in the system at
 *        any given time.
 *
 * @return particle_system_t * pointer to emitter.
 */
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

/**
 * Adds a particle to the particle system. Returns 0 if a successful insertion
 * occurred, and 1 otherwise (generally meaning the emitter is full). 
 * 
 * @param
 * @param
 * 
 * @return void.
 */
int32_t
insert_particle( particle_system_t *ps, particle_t *p ) {
  if ( ps->alive_count == ps->max_particles - 1 ) {
    return PS_FULL;
  }

  /* Checks to ensure the function pointers are defined as they are 
     used in the update procedures. */
  if (!p->particle_update || !p->particle_draw) {
    return PS_INVALID_FP;
  }

  ps->particles[( ps->alive_count )++] = *p;
  return PS_SUCCESS;
}

/**
 * 
 * 
 * @param
 * 
 * @return void.
 */
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

/**
 * 
 * 
 * @param
 * 
 * @return void.
 */
void
particle_system_draw( particle_system_t *ps ) {
  for ( int i = 0; i < ps->alive_count; i++ ) {
    particle_t *p = &ps->particles[i];
    if ( p->particle_draw ) {
      p->particle_draw( p );
    }
  }
}