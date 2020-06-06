#include "text.h"

#define DEFAULT_FONT_SIZE 24
#define DEFAULT_FONT_COLOR 0xFF

static char textBuffer[MAX_LINE_LENGTH];
static SDL_Texture* fontTexture;

/*
 *
 */
void initFonts(void) {
  fontTexture = NULL;
}

/*
 *
 */
void drawText(int x, int y, int r, int g, int b, const char* text, ...) {
  SDL_Rect rect;
  va_list args;

  memset(&textBuffer, '\0', sizeof(textBuffer));

  va_start(args, text);
  vsprintf(textBuffer, text, args);
  va_end(args);

  int len = strlen(textBuffer);

  rect.w = GLYPH_WIDTH;
  rect.h = GLYPH_HEIGHT;
  rect.y = 0;

  SDL_SetTextureColorMod(fontTexture, r, g, b);

  for (int i = 0; i < len; i++) {
    int c = textBuffer[i];

    if (c >= ' ' && c <= 'Z') {
      rect.x = (c - ' ') * GLYPH_WIDTH;
      blitRect(fontTexture, &rect, x, y);
      x += GLYPH_WIDTH;
    }
  }
}

/*
 *
 */
void freeFonts() {

}
