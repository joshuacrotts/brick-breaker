#ifndef BRICK_H
#define BRICK_H

#include "../lib/stds/include/animation.h"
#include "../lib/stds/include/draw.h"
#include "commons.h"

/*
 *
 */
extern struct entity_t *add_brick( float, float, uint32_t, int8_t );

/*
 *
 */
extern void brick_update( struct entity_t * );

/*
 *
 */
extern void brick_draw( struct entity_t * );

/*
 *
 */
extern void brick_die( struct entity_t * );

#endif