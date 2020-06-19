#include "../include/draw.h"

#define DEFAULT_FONT_COLOR 0xFF

static TTF_Font* getFont(char*, uint16_t);
static void loadFonts();
static void addFont(char*, uint16_t);

static char textBuffer[MAX_LINE_LENGTH];
static SDL_Surface* messageSurface;
static SDL_Texture* messageTexture;
static SDL_Rect messageRect;

void initFonts(void) {
  app.fontTail = &app.fontHead;
  if (TTF_Init() == -1) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize TTF_Init: %s.\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  loadFonts();
}

void drawText(float x, float y, uint8_t r, uint8_t g, uint8_t b, char* fontString, uint16_t fontSize, const char* text, ...) {
  messageRect.x = (uint16_t) x;
  messageRect.y = (uint16_t) y;

  va_list args;
  memset(&textBuffer, '\0', sizeof(textBuffer));

  va_start(args, text);
  vsprintf(textBuffer, text, args);
  va_end(args);

  SDL_Color textColor = {r, g, b};
  TTF_Font* font = getFont(fontString, fontSize);

  messageSurface = TTF_RenderText_Solid(font, textBuffer, textColor);
  TTF_SizeText(font, textBuffer, &messageRect.w, &messageRect.h);

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

  Font* f;
  f = app.fontHead.next;

  while (f != NULL) {
    f = app.fontHead.next;
    app.fontHead.next = f->next;
    free(f);
  }

  TTF_Quit();
}

void getStringSize(char* s, char* font, uint16_t size, int* w, int* h) {
  TTF_Font* f;
  f = getFont(font, size);

  if (f != NULL) {
    TTF_SizeText(f, s, w, h);
  } else {
    exit(EXIT_FAILURE);
  }
}

/*
 *
 */
static TTF_Font* getFont(char* fontStr, uint16_t fontSize) {
  Font* f;

  for (f = app.fontHead.next; f != NULL; f = f->next) {
    if (strcmp(f->name, fontStr) == 0 && f->size == fontSize) {
      return f->font;
    }
  }

  return NULL;
}

/*
 *
 */
static void loadFonts() {
  addFont("res/fonts/nes.ttf", 12);
  addFont("res/fonts/nes.ttf", 24);
}

/*
 *
 */
static void addFont(char* fontFile, uint16_t size) {
  Font* f;
  f = malloc(sizeof(Font));
  memset(f, 0, sizeof(Font));

  f->font = TTF_OpenFont(fontFile, size);
  strcpy(f->name, fontFile);
  f->size = size;

  app.fontTail->next = f;
  app.fontTail = f;
}