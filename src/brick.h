#ifndef BRICK_H
#define BRICK_H

#include "commons.h"

extern Entity* add_brick(float, float, uint32_t);
extern void brick_update(Entity*);
extern void brick_draw(Entity*);
extern void brick_die(Entity*);

#endif