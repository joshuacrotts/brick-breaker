#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "stds.h"
#include "../include/draw.h"

extern app_t app;


/*
 * Initializes the background image specified by char*.
 * It is drawn at (0, 0), or the top-left of the window.
 * 
 * @param char *file location of background image.
 * 
 * @return void.
 */
extern background_t* 
init_background(char*);


/*
 * Continuously updates the position of the background depending
 * on the camera's location. If no camera is used, its offset is
 * 0, thus not moving the background.
 * 
 * @param background_t struct to update.
 * 
 * @return void.
 */
extern void 
background_update(background_t*);


/*
 * Draws the background at its appropriate location specified by the 
 * update function. 
 * 
 * @param background_t struct to draw.
 * 
 * @return void.
 */
extern void 
background_draw(background_t*);


/*
 * Frees the context of the background struct and image.
 */
extern void 
background_die(background_t*);

#endif
