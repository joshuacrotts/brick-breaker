#ifndef BALL_H
#define BALL_H

#include "commons.h"
#include "particle.h"
#include "../lib/stds/include/draw.h"
#include "../lib/stds/include/trail.h"

extern app_t app;
extern stage_t stage;
extern level_t* currentLevel;


/*
 *
 */
entity_t* 
add_ball(float, float, uint32_t flags);


/*
 *
 */
void 
ball_update(entity_t*);


/*
 *
 */
void 
ball_draw(entity_t*);


/*
 *
 */
void 
ball_die(entity_t*);

#endif