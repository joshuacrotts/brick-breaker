#ifndef LEVEL_H
#define LEVEL_H

#include "commons.h"
#include "paddle.h"
#include "brick.h"
#include "ball.h"
#include "score_item.h"
#include "transition.h"
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
add_level(uint16_t);


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


/*
 *
 */
extern void
remove_balls(void);


/*
 *
 */
extern void
set_next_level(void);

/*
 *
 */
extern void 
load_level_music(uint16_t);


#endif