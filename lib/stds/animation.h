#ifndef ANIMATION_H
#define ANIMATION_H

#include "stds.h"

extern App app;

/*
 * There are two ways to use an animation: through
 * a sprite sheet (specified by the last four parameters
 * x, y, w, h).
 * @param x = starting top-left x pos of the sprite sheet.
 * @param y = starting top-left y pos of the sprite sheet.
 */
extern Animation* add_spritesheet(char*, uint8_t, float, uint16_t, uint16_t);

/*
 * The other way to use animations is to specify the
 * directory of the animation files and the program
 * will load them in. All sprites must have the same
 * leading prefix, with a number at the end indicating
 * their index in the sequence (ex. spr_0, spr_1, spr_2,
 *, etc.).
 */
extern Animation* add_animation(char*, uint8_t, float);

/*
 *
 */
extern void animation_update(Entity*);

/*
 *
 */
extern void animation_draw(Entity*);

/*
 *
 */
extern void animation_die(Entity*);

extern SDL_Texture* loadTexture(const char*);
extern void blit(SDL_Texture*, float, float, bool);
extern void blitRect(SDL_Texture*, SDL_Rect*, float, float);
extern void blitRotated(SDL_Texture*, float, float, uint16_t);

#endif
