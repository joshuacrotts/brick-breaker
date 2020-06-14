#ifndef DEBRIS_H
#define DEBRIS_H

#include "commons.h"

extern Stage stage;

extern void add_debris(Entity*, uint32_t);
extern void debris_update(Debris*);
extern void debris_draw(Debris*);
extern void debris_die(Debris*);

extern void blitRect(SDL_Texture*, SDL_Rect*, float, float);

#endif