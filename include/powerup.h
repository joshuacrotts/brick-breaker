#ifndef POWERUP_H
#define POWERUP_H

#include "commons.h"
#include "ball.h"
#include "../lib/stds/include/animation.h"
#include "../lib/stds/include/sound.h"

extern app_t app;
extern entity_t *paddle;
extern stage_t stage;
extern level_t *currentLevel;

/*
 *
 */
extern entity_t* 
add_powerup(float, float, uint32_t, int8_t);


/*
 *
 */
extern void 
powerup_update(entity_t *);


/*
 *
 */
extern void 
powerup_draw(entity_t *);


/*
 *
 */
extern void 
powerup_die(entity_t *);


/*
 *
 */
extern void 
powerup_large_activate(entity_t *);


/*
 *
 */
extern void 
powerup_large_deactivate(entity_t *);


/*
 *
 */
extern void 
powerup_coin_activate(entity_t *);


/*
 *
 */
extern void 
powerup_life_activate(entity_t *);


/*
 *
 */
extern void 
powerup_multi_activate(entity_t *);

#endif