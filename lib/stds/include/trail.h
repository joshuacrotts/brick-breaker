#ifndef TRAIL_H
#define TRAIL_H

#include "stds.h"
#include "draw.h"

extern App app;

/*
 * Initializes a trail object using the supplied Entity as the parent
 * where it will stay for the duration of its life. The trail is added
 * to the App automatically, so nothing is returned.
 * 
 * @param Entity* parent entity.
 * @param int16_t rate at which the alpha decreases (should be between 0 
 *        and 255, the higher it is, the faster it goes).
 * @param int16_t starting alpha of the object.
 * 
 * @return void.
 */
extern void add_trail(Entity*, int16_t, int16_t);

/*
 *
 */
extern void trail_update(Trail*);

/*
 *
 */
extern void trail_draw(Trail*);

#endif