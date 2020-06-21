#ifndef HUD_H
#define HUD_H

#include "commons.h"
#include "emitter.h"
#include "../lib/stds/include/draw.h"
#include "../lib/stds/include/text.h"

extern app_t app;
extern stage_t stage;
extern entity_t* paddle;


/* 
 *
 */
extern void 
init_HUD(void);


/* 
 *
 */
extern void 
update_HUD(void);


/* 
 *
 */
extern void 
draw_HUD(void);


/* 
 *
 */
extern void 
draw_paused(void);

#endif