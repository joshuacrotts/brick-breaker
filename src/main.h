#ifndef MAIN_H
#define MAIN_H

#include "commons.h"

App app;

extern SDL_Texture* loadTexture(const char*);

extern void initGame(const char*, int, int);
extern void loop();
extern void drawText(float, float, int, int, int, const char*, ...);
extern void blitColorTextureScaled(SDL_Texture*, float, float, float, float, uint16_t, int16_t, int16_t, int16_t, int16_t);
extern void blitTextureScaled(SDL_Texture*, float, float, float, float, uint16_t);

#endif
