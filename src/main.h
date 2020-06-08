#ifndef MAIN_H
#define MAIN_H

#include "commons.h"

App app;
Stage stage;
Entity* player;

extern void init_player(void);
extern void player_update(void);
extern void player_draw(void);
extern Entity* add_particle(float, float, float, float, float, float, uint16_t, uint16_t, uint16_t, int16_t, int16_t, int16_t, int16_t, float);

extern void initGame(const char*, int, int);
extern void updateCamera(Entity*);
extern void loop();
extern void drawText(float, float, int, int, int, const char*, ...);
extern void blitColorTextureScaled(SDL_Texture*, float, float, float, float, uint16_t, int16_t, int16_t, int16_t, int16_t);
extern void blitTextureScaled(SDL_Texture*, float, float, float, float, uint16_t);
extern void blit(SDL_Texture*, float, float);
extern SDL_Texture* loadTexture(const char*);

#endif
