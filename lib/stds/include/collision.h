#ifndef COLLISION_H
#define COLLISION_H

#include "stds.h"

extern enum CollisionSide check_aabb_collision( entity_t *a, entity_t *b );

extern bool check_intersection( float x1, float y1, int32_t w1, int32_t h1, float x2, float y2,
                                int32_t w2, int32_t h2 );

#endif