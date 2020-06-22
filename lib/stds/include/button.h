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
 * Adds a button with no texture. This is useful for buttons that have to change colors overtime, or just 
 * don't have an accompanying texture. Make sure to change the color with button->color = ...
 * 
 * @param float x top-left x pos of button.
 * @param float y top-left y pos of button.
 * @param uint32_t w width of button.
 * @param uint32_t h height of button.
 * @param bool true if the button should be filled with color, false otherwise.
 * @param char* string to font path used for the text.
 * @param uint16_t size of font.
 * @param SDL_Color* color to draw font.
 * @param char* text to draw.
 * 
 * @return button_t pointer.
 */
extern button_t*
add_button(float, float, uint32_t, uint32_t, bool, char*, uint16_t, SDL_Color*, char*);


/* 
 * Adds a button with a texture. 
 * 
 * @param float x top-left x pos of button.
 * @param float y top-left y pos of button.
 * @param char* string to texture for button.
 * @param char* string to font path used for the text.
 * @param uint16_t size of font.
 * @param SDL_Color* color to draw font.
 * @param char* text to draw.
 * 
 * @return button_t pointer.
 */
extern button_t* 
add_button_texture(float, float, char*, char*, uint16_t, SDL_Color*, char*);


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