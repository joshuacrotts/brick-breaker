#ifndef TEXT_H
#define TEXT_H

#include "stds.h"

extern App app;

/*
 * Initializes the TTF font library for use.
 */
extern void initFonts(void);

/*
 * Frees the fonts that are in use by the standards library.
 */
extern void freeFonts(void);

/* 
 * Draws a string of text specified by the const char* parameter, supplemented 
 * by whatever formatting arguments are necessary. 
 * 
 * @param float x coordinate (top-left) of string.
 * @param float y coordinate (top-left) of string.
 * @param uint8_t red color value (0-255).
 * @param uint8_t green color value (0-255).
 * @param uint8_t blue color value (0-255).
 * @param const char* string to draw.
 * @param ... formatting args.
 * 
 * To center a string, call getStringSize() or getStringSizeFont (if using a non
 * standard font), and draw the string at SCREEN_WIDTH / 2 - fontWidth / 2.
 */
extern void drawText(float, float, uint8_t, uint8_t, uint8_t, const char*, ...);

/*
 * Computes the size of the string with the default font were it to be drawn
 * to the screen in pixels. This is useful for positioning the string in the middle
 * of the screen if need-be.
 * 
 * @param char* string.
 * @param pointer to integer (int) where the width of the string is stored.
 * @param pointer to integer (int) where the height of the string is stored.
 */
extern void getStringSize(char*, int*, int*);

/*
 * Computes the size of the string with the supplied font were it to be drawn
 * to the screen in pixels. This is useful for positioning the string in the middle
 * of the screen if need-be.
 * 
 * @param char* string.
 * @param TTF_Font* font used for determining the size.
 * @param pointer to integer (int) where the width of the string is stored.
 * @param pointer to integer (int) where the height of the string is stored.
 */
extern void getStringSizeFont(char*, TTF_Font*, int*, int*);

#endif
