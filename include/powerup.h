#ifndef POWERUP_H
#define POWERUP_H

#include "../lib/stds/include/animation.h"
#include "../lib/stds/include/sound.h"
#include "ball.h"
#include "commons.h"
#include "score_item.h"

extern struct app_t     app;
extern struct entity_t *paddle;
extern stage_t   stage;
extern level_t * currentLevel;

/*
 *
 */
extern struct entity_t *add_powerup( float, float, uint32_t, int8_t );

/*
 *
 */
extern void powerup_update( struct entity_t * );

/*
 *
 */
extern void powerup_draw( struct entity_t * );

/*
 *
 */
extern void powerup_die( struct entity_t * );

/*
 *
 */
extern void powerup_large_activate( struct entity_t * );

/*
 *
 */
extern void powerup_large_deactivate( struct entity_t * );

/*
 *
 */
extern void powerup_coin_activate( struct entity_t * );

/*
 *
 */
extern void powerup_life_activate( struct entity_t * );

/*
 *
 */
extern void powerup_multi_activate( struct entity_t * );

#endif