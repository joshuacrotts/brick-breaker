#ifndef POWERUP_H
#define POWERUP_H

#include "commons.h"
#include "ball.h"
#include "../lib/stds/include/animation.h"
#include "../lib/stds/include/sound.h"

extern App app;
extern Entity* paddle;
extern Stage stage;
extern Level* currentLevel;

/*
 *
 */
extern Entity* add_powerup(float, float, uint32_t, int8_t);

/*
 *
 */
extern void powerup_update(Entity*);

/*
 *
 */
extern void powerup_draw(Entity*);

/*
 *
 */
extern void powerup_die(Entity*);

/*
 *
 */
extern void powerup_large_activate(Entity*);

/*
 *
 */
extern void powerup_large_deactivate(Entity*);

/*
 *
 */
extern void powerup_coin_activate(Entity*);

/*
 *
 */
extern void powerup_life_activate(Entity*);

/*
 *
 */
extern void powerup_multi_activate(Entity*);

#endif