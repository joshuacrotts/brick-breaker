#ifndef EMITTER_H
#define EMITTER_H

#include "commons.h"
#include "particle.h"

extern level_t * currentLevel;
extern entity_t *e;
extern app_t     app;
extern stage_t   stage;

/*
 *
 */
extern emitter_t *add_emitter( int32_t, int32_t, uint32_t, uint32_t );

/*
 *
 */
extern void emitter_update( emitter_t * );

/*
 *
 */
extern void emitter_draw( emitter_t * );

/*
 *
 */
extern void emitter_die( emitter_t * );

/*
 *
 */
extern void spawn_blood_particles( emitter_t *, int32_t, int32_t, uint32_t, uint32_t );

/*
 *
 */
extern void spawn_colorful_particles( emitter_t *, int32_t, int32_t, uint32_t, uint32_t );

/*
 *
 */
extern void spawn_sinusoidal_particles( emitter_t *, int32_t, int32_t, uint32_t, uint32_t );

/*
 *
 */
extern void spawn_star_particles( emitter_t *, int32_t, int32_t, uint32_t, uint32_t );

#endif
