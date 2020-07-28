#ifndef TRANSITION_H
#define TRANSITION_H
// activate the transition screen for 5ish seconds, block input, change screens and levels and music

#include "../lib/stds/include/draw.h"
#include "commons.h"
#include "level.h"

extern struct app_t app;

extern void activate_transition( bool );

extern void transition_update( void );

extern void transition_draw( void );

#endif