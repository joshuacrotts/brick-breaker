#ifndef PLAYER_H
#define PLAYER_H

#include "commons.h"

extern App app;
extern Stage stage;
extern Entity* player;

extern void init_player(void);
extern void player_update(void);
extern void player_draw(void);
extern void player_die(void);
extern void animation_update(Animation*);
extern void animation_draw(Entity*);
extern void animation_die(Animation*);

extern SDL_Texture* loadTexture(const char*);
extern void blitTextureScaled(SDL_Texture*, float, float, float, float, uint16_t);
extern void blit(SDL_Texture*, float, float, bool);
extern void blitRotated(SDL_Texture*, float, float, uint16_t);
extern Animation* add_spritesheet(char*, uint8_t, float, uint16_t, uint16_t);
extern Animation* add_animation(char*, uint8_t, float);

#endif
