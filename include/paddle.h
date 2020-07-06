#ifndef PADDLE_H
#define PADDLE_H

#include "../lib/stds/include/draw.h"
#include "commons.h"

extern entity_t *paddle;
extern app_t     app;
extern stage_t   stage;

/*
 *
 */
extern void init_paddle( void );

/*
 *
 */
extern void paddle_update( void );

/*
 *
 */
extern void paddle_draw( void );

/*
 *
 */
extern void paddle_die( void );

#endif