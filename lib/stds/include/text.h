#ifndef TEXT_H
#define TEXT_H

#include "stds.h"

extern app_t app;


/*
 * Initializes the TTF font library for use.
 */
extern void 
init_fonts(void);


/*
 * Loads fonts in from files.
 */
extern void 
load_fonts(void);


/*
 * Frees the fonts that are in use by the standards library.
 */
extern void 
free_fonts(void);


/* 
 * Draws a string of text specified by the const char *parameter, supplemented 
 * by whatever formatting arguments are necessary. 
 * 
 * @param float x coordinate (top-left) of string.
 * @param float y coordinate (top-left) of string.
 * @param uint8_t red color value (0-255).
 * @param uint8_t green color value (0-255).
 * @param uint8_t blue color value (0-255).
 * @param char *font name (use the file name itself with the extension).
 * @param uint16_t font size.
 * @param const char *string to draw.
 * @param ... formatting args.
 * 
 * To center a string, call get_string_size() or get_string_sizeFont (if using a non
 * standard font), and draw the string at SCREEN_WIDTH / 2 - fontWidth / 2.
 */
extern void 
draw_text(float, float, uint8_t, uint8_t, uint8_t, char*, uint16_t, char*, ...);


/*
 * Computes the size of the string with the default font were it to be drawn
 * to the screen in pixels. This is useful for positioning the string in the middle
 * of the screen if need-be.
 * 
 * @param char *string.
 * @param char *font name.
 * @param uint16_t font size.
 * @param pointer to integer (int) where the width of the string is stored.
 * @param pointer to integer (int) where the height of the string is stored.
 */
extern void 
get_string_size(char*, char*, uint16_t, int*, int*);

#endif
