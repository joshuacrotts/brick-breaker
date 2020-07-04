#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../include/draw.h"
#include "stds.h"

extern app_t app;

/**
 * Loads in the parallax images specified by the directory.
 * These images should be labeled in back-to-front order.
 * For instance, if we have three layers L0, L1, and L2,
 * L0 should be the layer drawn farthest from the viewport,
 * whereas L2 should be the closest. Make sure that your
 * images all have a common suffix numbering scheme as well,
 * starting at 0.
 *
 * @param char* string to directory of parallax background images.
 * @param size_t number of parallax frames.
 * @param float default scroll speed shared across all frames.
 * @param float[] array of modified scroll speeds. These values alter
 *        the default scroll speed of each frame. These values
 *        f1 <= f2 <= ... < fn, as implied, should be listed in
 *        back-to-front speed.
 * @param bool infinite_scroll, determining whether two copies of
 *        the image are rendered side-by-side to provide the illusion
 *        of an infinite background.
 */
extern void init_parallax_background( char *bg_directory, size_t n, float default_scroll_speed,
                                      float modified_scroll_speeds[], bool is_infinite );

/**
 * Updates the position of the parallax background element.
 * The offset is applied by multiplying the default scroll speed
 * multiplied by the scroll offset to give the illusion of
 * different scroll rates.
 *
 * @param parallax_backgorund_t pointer to struct.
 *
 * @return void.
 */
extern void parallax_background_update( parallax_background_t *parallax );

/**
 * Draws the parallax background frame. Two copies of the image
 * are drawn to provide the illusion of infinite scrolling if
 * specified by the boolean in the struct.
 *
 * @param parallax_background_t pointer to struct.
 *
 * @return void.
 */
extern void parallax_background_draw( parallax_background_t *parallax );

/**
 * Initializes the background image specified by char*.
 * It is drawn at (0, 0), or the top-left of the window.
 *
 * @param char *file location of background image.
 *
 * @return void.
 */
extern background_t *init_background( char *bg_directory );

/**
 * Continuously updates the position of the background depending
 * on the camera's location. If no camera is used, its offset is
 * 0, thus not moving the background.
 *
 * @param background_t pointer to update.
 *
 * @return void.
 */
extern void background_update( background_t *bg );

/**
 * Draws the background at its appropriate location specified by the
 * update function.
 *
 * @param background_t pointer to draw.
 *
 * @return void.
 */
extern void background_draw( background_t *bg );

/**
 * Frees the context of the background struct and image.
 *
 * @param background_t pointer to free.
 *
 * @return void.
 */
extern void background_die( background_t *bg );

#endif
