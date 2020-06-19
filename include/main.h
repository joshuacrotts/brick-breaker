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
#include "../lib/stds/include/draw.h"
#include "../lib/stds/include/sound.h"
#include "../lib/stds/include/text.h"

App app;
Stage stage;
Entity *paddle;
Background *background;
extern Level *currentLevel;

extern void spawn_blood_particles(Emitter *, int32_t, int32_t, uint32_t, uint32_t);
extern void spawn_colorful_particles(Emitter *, int32_t, int32_t, uint32_t, uint32_t);

extern void initGame(const char *, int, int);
extern void updateCamera(Entity *);
extern void loop();

#endif
