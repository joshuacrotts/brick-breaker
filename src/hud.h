#ifndef HUD_H
#define HUD_H

#include "commons.h"

extern App app;
extern Stage stage;

extern void drawHUD(SDL_Color*);

extern void drawRect(SDL_Rect*, uint8_t, uint8_t, uint8_t, uint8_t, bool);
extern void drawText(float, float, uint8_t, uint8_t, uint8_t, const char*, ...);

#endif