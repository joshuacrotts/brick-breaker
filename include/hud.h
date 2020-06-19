#ifndef HUD_H
#define HUD_H

#include "commons.h"
#include "emitter.h"
#include "../lib/stds/include/draw.h"
#include "../lib/stds/include/text.h"

extern App app;
extern Stage stage;
extern Entity* paddle;

/* 
 *
 */
extern void init_HUD(void);

/* 
 *
 */
extern void update_HUD(void);

/* 
 *
 */
extern void draw_HUD(void);

/* 
 *
 */
extern void draw_paused(void);

#endif