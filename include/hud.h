#ifndef HUD_H
#define HUD_H

#include "../lib/stds/include/button.h"
#include "../lib/stds/include/draw.h"
#include "../lib/stds/include/text.h"
#include "commons.h"
#include "emitter.h"
#include "main.h"

extern app_t     app;
extern stage_t   stage;
extern entity_t *paddle;

/*
 *
 */
extern void init_HUD( void );

/*
 *
 */
extern void update_HUD( void );

/*
 *
 */
extern void draw_HUD( void );

/*
 *
 */
extern void draw_paused( void );

/*
 *
 */
extern void init_menu( void );

/*
 *
 */
extern void menu_update( void );

/*
 *
 */
extern void menu_draw( SDL_Color * );

#endif