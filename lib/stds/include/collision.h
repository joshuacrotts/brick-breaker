#ifndef COLLISION_H
#define COLLISION_H

#include "stds.h"

/**
 * Determines which side entity_t a collided onto entity_t b.
 *
 * @param entity_t* first entity.
 * @param entity_t* second entity.
 *
 * @return enum side that a collided onto b with (the side of b).
 */
extern enum CollisionSide check_aabb_collision( entity_t *a, entity_t *b );

/**
 * Determines if two rectangles are collided.
 *
 * @return true if overlap exists, false otherwise.
 */
extern bool check_intersection( float x1, float y1, int32_t w1, int32_t h1, float x2, float y2,
                                int32_t w2, int32_t h2 );

#endif