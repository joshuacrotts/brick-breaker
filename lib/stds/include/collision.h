#ifndef COLLISION_H
#define COLLISION_H

#include "stds.h"

extern enum CollisionSide check_aabb_collision( entity_t *a, entity_t *b );

extern bool check_intersection( f32 x1, f32 y1, int32_t w1, int32_t h1, f32 x2, f32 y2,
                                int32_t w2, int32_t h2 );

#endif // COLLISION_H