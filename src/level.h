#ifndef LEVEL_H
#define LEVEL_H

#include "commons.h"

Level* currentLevel;
extern Entity* paddle;
extern Stage stage;

extern Level* add_level(const char*);
extern Entity* add_brick(float, float, uint32_t, int8_t);
extern void add_debris(Entity*, uint32_t);
extern void level_update(void);
extern void level_draw(void);
extern void brick_update(Entity*);
extern void brick_draw(Entity*);
extern void brick_die(Entity*);
extern void ball_update(Entity*);
extern void ball_draw(Entity*);
extern void ball_die(Entity*);
extern void powerup_update(Entity*);
extern void powerup_draw(Entity*);
extern void powerup_die(Entity*);
extern void powerup_activate(Entity*);

extern void blit(SDL_Texture*, float, float, bool);

#endif