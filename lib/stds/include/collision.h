#ifndef COLLISION_H
#define COLLISION_H

#include "stds.h"

/*
 *
 */
extern enum CollisionSide
check_aabb_collision(entity_t*, entity_t*);


/*
 * 
 */
extern bool 
check_intersection(float, float, int32_t, int32_t, float, float, int32_t, int32_t);

#endif