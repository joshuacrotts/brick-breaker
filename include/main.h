#ifndef MAIN_H
#define MAIN_H

#include "../lib/stds/include/background.h"
#include "../lib/stds/include/draw.h"
#include "../lib/stds/include/game.h"
#include "../lib/stds/include/init.h"
#include "../lib/stds/include/particle_system.h"
#include "../lib/stds/include/sound.h"
#include "../lib/stds/include/text.h"
#include "ball.h"
#include "commons.h"
#include "debris.h"
#include "hud.h"
#include "level.h"
#include "paddle.h"
#include "particle.h"
#include "powerup.h"

struct particle_system_t *ps;
struct app_t            app;
stage_t          stage;
struct entity_t *       paddle;
struct background_t *   background;
extern level_t * currentLevel;

/*
 *
 */
extern void load_level_music( uint16_t );

#endif
