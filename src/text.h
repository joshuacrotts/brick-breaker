#include "stds.h"

#define GLYPH_HEIGHT 28
#define GLYPH_WIDTH  18

extern void freeFonts(void);

extern void drawText(int, int, int, int, int, const char*, ...);

extern void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);
extern SDL_Texture *loadTexture(char *filename);
