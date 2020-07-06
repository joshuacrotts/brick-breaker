#ifndef MAIN_H
#define MAIN_H

#include "../lib/stds/include/background.h"
#include "../lib/stds/include/draw.h"
#include "../lib/stds/include/game.h"
#include "../lib/stds/include/init.h"
#include "../lib/stds/include/sound.h"
#include "../lib/stds/include/text.h"
#include "ball.h"
#include "commons.h"
#include "debris.h"
#include "emitter.h"
#include "hud.h"
#include "level.h"
#include "paddle.h"
#include "particle.h"
#include "powerup.h"

app_t           app;
stage_t         stage;
entity_t *      paddle;
background_t *  background;
extern level_t *currentLevel;

/*
 *
 */
extern void load_level_music( uint16_t );

#endif
