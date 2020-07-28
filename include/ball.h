#ifndef BALL_H
#define BALL_H

#include "../lib/stds/include/draw.h"
#include "../lib/stds/include/trail.h"
#include "commons.h"
#include "particle.h"

extern struct particle_system_t *ps;
extern struct app_t              app;
extern stage_t            stage;
extern level_t *          currentLevel;

/*
 *
 */
struct entity_t *add_ball( float, float, uint32_t flags );

/*
 *
 */
void ball_update( struct entity_t * );

/*
 *
 */
void ball_draw( struct entity_t * );

/*
 *
 */
void ball_die( struct entity_t * );

#endif