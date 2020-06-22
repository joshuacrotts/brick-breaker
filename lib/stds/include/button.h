#ifndef GUI_H
#define GUI_H

#include "stds.h"
#include "draw.h"
#include "text.h"


/*
 *
 */
extern void
update_buttons(void);


/*
 *
 */
extern void
draw_buttons(void);


/* 
 *
 */
extern void 
add_button(float, float, uint32_t, uint32_t, bool, font_t*, SDL_Color*, char*);


/*
 *
 */
extern void 
add_button_texture(float, float, char*, font_t*, SDL_Color*, char*);


/*
 *
 */
void 
button_update(button_t*);


/*
 *
 */
void 
button_draw(button_t*);


/*
 *
 */
bool 
is_mouse_over_button(button_t*);


/*
 *
 */
bool 
is_button_clicked(button_t*, int32_t);

#endif