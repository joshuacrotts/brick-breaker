#ifndef LEVEL_H
#define LEVEL_H

#include "../lib/stds/include/draw.h"
#include "../lib/stds/include/particle_system.h"
#include "../lib/stds/include/sound.h"
#include "ball.h"
#include "brick.h"
#include "commons.h"
#include "debris.h"
#include "paddle.h"
#include "powerup.h"
#include "score_item.h"
#include "transition.h"

level_t *                 currentLevel;
extern entity_t *         paddle;
extern particle_system_t *ps;
extern stage_t            stage;

/*
 *
 */
extern level_t *add_level( uint16_t );

/*
 *
 */
extern void level_update( void );

/*
 *
 */
extern void level_draw( void );

/*
 *
 */
extern void remove_balls( void );

/*
 *
 */
extern void set_next_level( void );

/*
 *
 */
extern void load_level_music( uint16_t );

#endif