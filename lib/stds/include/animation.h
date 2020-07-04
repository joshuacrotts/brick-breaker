/*
 * This header defines the animation functions associated with the animation_t
 * struct. A note about this is to make sure to define the position, angle, and
 * flip variables accordingly per the entity using the animation. If not, the
 * animation will not move, rotate, etc. 
 * 
 * pos_x = x coordinate of animation.
 * pos_y = y coordinate of animation.
 * angle = angle of animation.
 * flip  = SDL_FLIP_HORIZONTAL/VERTICAL/NONE.
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include "draw.h"
#include "stds.h"

extern app_t app;



/**
 * There are two ways to use an animation: through
 * a sprite sheet (specified by the last four parameters
 * x, y, w, h).
 * 
 * @param char* file directory of sprite sheet.
 * @param uint8_t number of frames.
 * @param float time spent on an individual frame per second.
 * @param uint16_t = starting top-left x pos of the sprite sheet.
 * @param uint16_t = starting top-left y pos of the sprite sheet.
 * 
 * @return animation_t* struct.
 */
extern animation_t *add_spritesheet( char *file_directory, uint8_t n, float frame_time,
                                     uint16_t start_x, uint16_t start_y );

/**
 * The other way to use animations is to specify the
 * directory of the animation files and the program
 * will load them in. All sprites must have the same
 * leading prefix, with a number at the end indicating
 * their index in the sequence (ex. spr_0, spr_1, spr_2,
 *, etc.).
 * 
 * @param char* directory to files with file prefix.
 * @param uint8_t number of frames.
 * @param float time to spend on a individual frame per second.
 * 
 * @return animation_t* struct.
 */
extern animation_t *add_animation( char *files_directory, uint8_t n, float frame_time );

/**
 * Updates the animation type. If it is a sprite sheet, it
 * advances the coordinate used to keep track of the current
 * sprite in the sheet (i.e. the x coordinate defining the top
 * left). Oppositely, if it is a series of images, we just advance
 * the pointer keeping track of each image. Once the cycle ends,
 * the pointer or coordinate is reset back to 0.
 * 
 * @param animation_t* animation to update.
 * 
 * @return void.
 */
extern void animation_update( animation_t *animation );

/**
 * Draws the animation.
 * 
 * @param animation_t* animation to draw.
 * 
 * @return void.
 */
extern void animation_draw( animation_t *animation );

/**
 * Destroys and frees the animation passed by the entity.
 *
 * @param animation_t* animation to free from memory.
 *
 * @return void.
 */
extern void animation_die( animation_t *animation );

#endif
