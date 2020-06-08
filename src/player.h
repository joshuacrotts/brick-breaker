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

extern SDL_Texture* loadTexture(const char*);
extern void blitTextureScaled(SDL_Texture*, float, float, float, float, uint16_t);

#endif
