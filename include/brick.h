#ifndef BRICK_H
#define BRICK_H

#include "commons.h"
#include "../lib/stds/include/draw.h"
#include "../lib/stds/include/animation.h"


/*
 *
 */
extern entity_t* 
add_brick(float, float, uint32_t, int8_t);


/*
 *
 */
extern void 
brick_update(entity_t *);


/*
 *
 */
extern void 
brick_draw(entity_t *);


/*
 *
 */
extern void 
brick_die(entity_t *);

#endif