#ifndef TEXT_H
#define TEXT_H

#include "stds.h"

#define GLYPH_HEIGHT 28
#define GLYPH_WIDTH  18

/*
 *
 */
extern void freeFonts(void);

/*
 *
 */
extern void drawText(int, int, int, int, int, const char*, ...);

#endif
