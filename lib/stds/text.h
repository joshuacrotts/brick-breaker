#ifndef TEXT_H
#define TEXT_H

#include "stds.h"

extern App app;

/*
 *
 */
extern void initFonts(void);

/*
 *
 */
extern void freeFonts(void);

/*
 *
 */
extern void drawText(float, float, uint8_t, uint8_t, uint8_t, const char*, ...);

#endif
