#ifndef LEVEL_H
#define LEVEL_H

#include "commons.h"
#include "paddle.h"
#include "brick.h"
#include "ball.h"
#include "debris.h"
#include "powerup.h"
#include "../lib/stds/include/sound.h"
#include "../lib/stds/include/draw.h"

level_t* currentLevel;
extern entity_t *paddle;
extern stage_t stage;


/*
 *
 */
extern level_t* 
add_level(const char*);


/*
 *
 */
extern void 
level_update(void);


/*
 *
 */
extern void 
level_draw(void);

#endif