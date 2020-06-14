#ifndef POWERUP_H
#define POWERUP_H

#include "commons.h"

extern App app;
extern Stage stage;
extern Level* currentLevel;

extern Entity* add_powerup(float, float, uint32_t, int8_t);
extern void powerup_update(Entity*);
extern void powerup_draw(Entity*);
extern void powerup_die(Entity*);
extern void powerup_activate(Entity*);

extern Animation* add_spritesheet(char*, uint8_t, float, uint16_t, uint16_t);
extern void animation_update(Entity*);
extern void animation_draw(Entity*);
extern void animation_die(Entity*);


#endif