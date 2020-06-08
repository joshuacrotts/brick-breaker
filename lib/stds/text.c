#include "text.h"

#define DEFAULT_FONT_SIZE 24
#define DEFAULT_FONT_COLOR 0xFF

static char textBuffer[MAX_LINE_LENGTH];
static TTF_Font* arialFont;

static SDL_Surface* messageSurface;
static SDL_Texture* messageTexture;
static SDL_Rect messageRect;

void initFonts(void) {
  if (TTF_Init() == -1) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize TTF_Init: %s.\n", SDL_GetError());
    exit(EXIT_ERROR);
  }

  arialFont = TTF_OpenFont("../res/fonts/arial.ttf", DEFAULT_FONT_SIZE);

  if (arialFont == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load TTF font: %s.\n", SDL_GetError());
    exit(EXIT_ERROR);
  }
}

void drawText(float x, float y, uint8_t r, uint8_t g, uint8_t b, const char* text, ...) {
  messageRect.x = (uint16_t) x;
  messageRect.y = (uint16_t) y;

  va_list args;
  memset(&textBuffer, '\0', sizeof(textBuffer));

  va_start(args, text);
  vsprintf(textBuffer, text, args);
  va_end(args);

  SDL_Color textColor = {r, g, b};
  messageSurface = TTF_RenderText_Solid(arialFont, textBuffer, textColor);
  TTF_SizeText(arialFont, textBuffer, &messageRect.w, &messageRect.h);

  if (messageSurface == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to write message: %s.\n", SDL_GetError());
    exit(EXIT_ERROR);
  }

  messageTexture = SDL_CreateTextureFromSurface(app.renderer, messageSurface);
  SDL_RenderCopy(app.renderer, messageTexture, NULL, &messageRect);
}

void freeFonts() {
  SDL_DestroyTexture(messageTexture);
  SDL_FreeSurface(messageSurface);
  TTF_CloseFont(arialFont);
  TTF_Quit();
}
