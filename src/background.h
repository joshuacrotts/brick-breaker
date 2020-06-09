#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "commons.h"

Background* background;
extern App app;

extern void init_background(void);
extern void background_update(void);
extern void background_draw(void);
extern void background_die(void);

extern void blit(SDL_Texture*, float, float, bool);
extern void blitTextureScaled(SDL_Texture*, float, float, float, float, uint16_t);
extern SDL_Texture* loadTexture(const char*);

#endif
