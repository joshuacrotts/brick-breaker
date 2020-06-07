#ifndef DRAW_H
#define DRAW_H

#include "stds.h"

extern App app;

/*
 * Clears the screen with a black color.
 */
extern void prepareScene();

/*
 * Presents the current scene from the application.
 */
extern void presentScene();

/*
 * Copies the graphics from the texture to a different
 * rectangle. This moves the sprite. You may pass in both
 * integers or floating-point numbers to this function, but
 * any floating-point values will be down-casted to integers.
 */
extern void blitRect(SDL_Texture*, SDL_Rect*, float, float);

/*
 * Renders a texture, specified by src, at
 * coordinates (x, y). You may pass in both integers or
 * floating-point numbers to this function, but any floating-point
 * values will be down-casted to integers.
 */
extern void blit(SDL_Texture*, float, float, bool);

/*
 * Draws a rotated SDL_Texture pointer at an x, y coordinate. You may
 * pass in both integers or floating-point numbers to this function, but
 * any floating-point values will be down-casted to integers.
 *
 * @param SDL_Texture* pointer to texture object.
 * @param float x coordinate.
 * @param int y coordinate.
 * @param int angle of rotation (0 to 360).
 */
extern void blitRotated(SDL_Texture*, float, float, int);

/*
 * Loads an image from the specified path. An error is
 * displayed if the file cannot be found or is not
 * loadable.
 */
extern SDL_Texture* loadTexture(char*);

#endif
