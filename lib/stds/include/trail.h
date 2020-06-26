#ifndef TRAIL_H
#define TRAIL_H

#include "stds.h"
#include "draw.h"

extern app_t app;


/*
 * Initializes a trail object using the supplied Entity as the parent
 * where it will stay for the duration of its life. The trail is added
 * to the App automatically, so nothing is returned.
 * 
 * @param entity_t* parent entity.
 * @param int16_t rate at which the alpha decreases (should be between 0 
 *        and 255, the higher it is, the faster it goes).
 * @param int16_t starting alpha of the object.
 * 
 * @return void.
 */
extern void 
add_trail(entity_t *parent_entity, int16_t alpha_decay_rate, int16_t starting_alpha);


/*
 * Updates the trail by iterating through the trail's linked lists,
 * and constantly decreasing its alpha value. Once any arbitrary 
 * tail node has an alpha of 0 or less (clamped to 0), it is 
 * removed.
 * 
 * @param trail_t struct to update.
 * 
 * @return void
 */
extern void 
trail_update(trail_t *t);


/*
 * Draws the tail linked list.
 * 
 * @param trail_t struct to draw.
 * 
 * @return void.
 */
extern void trail_draw(trail_t *t);

#endif