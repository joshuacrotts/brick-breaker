#ifndef PLAYER_H
#define PLAYER_H

#include "../../include/stds.h"
#include "../../include/draw.h"
#include "../../include/trail.h"
#include "../../include/animation.h"

entity_t* player;
extern app_t app;


/*
 *
 */
extern void 
init_player(void);


/*
 *
 */
extern void player_update(void);


/*
 *
 */
extern void player_draw(void);


#endif