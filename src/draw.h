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
 * rectangle. This moves the sprite.
 */
extern void blitRect(SDL_Texture*, SDL_Rect*, int, int);

/*
 * Renders a partition of a texture, specified by src, at
 * coordinates (x, y).
 */
extern void blit(SDL_Texture*, int x, int y, bool isCenter);

/*
 * Loads an image from the specified path. An error is
 * displayed if the file cannot be found or is not
 * loadable.
 */
extern SDL_Texture* loadTexture(char*);

#endif
