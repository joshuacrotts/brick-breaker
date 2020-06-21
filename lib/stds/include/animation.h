#ifndef ANIMATION_H
#define ANIMATION_H

#include "stds.h"
#include "draw.h"

extern app_t app;

/*
 * There are two ways to use an animation: through
 * a sprite sheet (specified by the last four parameters
 * x, y, w, h).
 * @param x = starting top-left x pos of the sprite sheet.
 * @param y = starting top-left y pos of the sprite sheet.
 */
extern animation_t* 
add_spritesheet(char*, uint8_t, float, uint16_t, uint16_t);


/*
 * The other way to use animations is to specify the
 * directory of the animation files and the program
 * will load them in. All sprites must have the same
 * leading prefix, with a number at the end indicating
 * their index in the sequence (ex. spr_0, spr_1, spr_2,
 *, etc.).
 */
extern animation_t* 
add_animation(char*, uint8_t, float);


/*
 * Updates the animation type. If it is a sprite sheet, it 
 * advances the coordinate used to keep track of the current 
 * sprite in the sheet (i.e. the x coordinate defining the top
 * left). Oppositely, if it is a series of images, we just advance
 * the pointer keeping track of each image. Once the cycle ends,
 * the pointer or coordinate is reset back to 0.
 * 
 * @param struct entity_t parent entity of animation.
 * 
 * @return void.
 */
extern void 
animation_update(entity_t*);


/*
 * Draws the animation type passed by the entity.
 * 
 * @param struct entity_t parent entity of animation.
 * 
 * @return void.
 */
extern void 
animation_draw(entity_t*);


/*
 * Destroys and frees the animation passed by the entity.
 * 
 * @param struct entity_t parent entity of animation.
 * 
 * @return void.
 */
extern void 
animation_die(entity_t*);

#endif
