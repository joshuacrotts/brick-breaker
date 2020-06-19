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

Level* currentLevel;
extern Entity* paddle;
extern Stage stage;

extern Level* add_level(const char*);
extern void level_update(void);
extern void level_draw(void);

#endif