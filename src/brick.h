#ifndef BRICK_H
#define BRICK_H

#include "commons.h"

extern Entity* add_brick(float, float, uint32_t, int8_t);
extern void brick_update(Entity*);
extern void brick_draw(Entity*);
extern void brick_die(Entity*);
extern Animation* add_animation(char*, uint8_t, float);
extern Animation* add_spritesheet(char*, uint8_t, float, uint16_t, uint16_t);
extern void animation_update(Entity*);
extern void animation_draw(Entity*);

extern SDL_Texture* loadTexture(char*);
extern void blit(SDL_Texture*, float, float, bool);

#endif