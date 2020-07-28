#ifndef COLLISION_H
#define COLLISION_H

#include "stds.h"

extern enum CollisionSide Stds_CheckAABBCollision( struct entity_t *a, struct entity_t *b );

extern bool Stds_CheckCircularCollision( const struct circle_t *c1, const struct circle_t *c2 );

extern void Stds_ResolveCircularCollision( struct circle_t *c1, struct circle_t *c2 );

extern bool Stds_CheckIntersection( const float x1, const float y1, const int32_t w1,
                                    const int32_t h1, const float x2, const float y2,
                                    const int32_t w2, const int32_t h2 );

#endif // COLLISION_H