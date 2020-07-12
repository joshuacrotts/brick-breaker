#ifndef BRICK_H
#define BRICK_H

#include "../lib/stds/include/animation.h"
#include "../lib/stds/include/draw.h"
#include "commons.h"

/*
 *
 */
extern entity_t *add_brick( f32, f32, uint32_t, int8_t );

/*
 *
 */
extern void brick_update( entity_t * );

/*
 *
 */
extern void brick_draw( entity_t * );

/*
 *
 */
extern void brick_die( entity_t * );

#endif