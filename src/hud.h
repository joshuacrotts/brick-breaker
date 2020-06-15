#ifndef HUD_H
#define HUD_H

#include "commons.h"

extern App app;
extern Stage stage;
extern Entity* paddle;

extern void init_HUD(void);
extern void draw_HUD(SDL_Color*);

extern void drawRect(SDL_Rect*, uint8_t, uint8_t, uint8_t, uint8_t, bool);
extern void drawText(float, float, uint8_t, uint8_t, uint8_t, const char*, ...);
extern void blit(SDL_Texture*, float, float, bool);
extern SDL_Texture* loadTexture(char*);

#endif