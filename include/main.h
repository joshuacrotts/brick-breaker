#ifndef MAIN_H
#define MAIN_H

#include "commons.h"
#include "level.h"
#include "particle.h"
#include "powerup.h"
#include "emitter.h"
#include "debris.h"
#include "paddle.h"
#include "ball.h"
#include "hud.h"
#include "../lib/stds/include/background.h"
#include "../lib/stds/include/game.h"
#include "../lib/stds/include/draw.h"
#include "../lib/stds/include/sound.h"
#include "../lib/stds/include/text.h"

app_t app;
stage_t stage;
entity_t *paddle;
background_t *background;
extern level_t *currentLevel;


/*
 *
 */
extern void 
init_game(const char*, uint32_t, uint32_t);

#endif
