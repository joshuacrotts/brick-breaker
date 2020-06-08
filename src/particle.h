#ifndef PARTICLE_H
#define PARTICLE_H

#include "commons.h"

extern App app;

extern Entity* add_particle(float, float, float, float, float, float, uint16_t, uint16_t, uint16_t, uint8_t, uint8_t, uint8_t, uint8_t, float);
extern void particle_tick(Entity*);
extern void particle_draw(Entity*);
extern void particle_die(Entity*);
extern void drawRect(SDL_Rect*, uint8_t, uint8_t, uint8_t, uint8_t, bool);
extern void drawCircle(int32_t, int32_t, uint32_t, uint8_t, uint8_t, uint8_t, uint8_t);

#endif
