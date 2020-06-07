#include "draw.h"

void prepareScene() {
  SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
  SDL_RenderClear(app.renderer);
}

void presentScene() {
  SDL_RenderPresent(app.renderer);
}

void blit(SDL_Texture* texture, float x, float y, bool isCenter) {
  SDL_Rect dest;

  dest.x = (int) x;
  dest.y = (int) y;

  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

  if (isCenter) {
    dest.x -= (dest.w >> 1);
    dest.y -= (dest.h >> 1);
  }

  SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitRect(SDL_Texture* texture, SDL_Rect* src, float x, float y) {
  SDL_Rect dest;
  dest.x = (int) x;
  dest.y = (int) y;

  dest.w = src->w;
  dest.h = src->h;
  SDL_RenderCopy(app.renderer, texture, src, &dest);
}

void blitRotated(SDL_Texture* texture, float x, float y, int angle) {
  SDL_Rect destRect;
  destRect.x = (int) x;
  destRect.y = (int) y;
  SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);

  destRect.x -= (destRect.w >> 1);
  destRect.y -= (destRect.h >> 1);

  SDL_RenderCopyEx(app.renderer, texture, NULL, &destRect, angle, NULL, SDL_FLIP_NONE);
}

void drawRect(SDL_Rect* rect, int r, int g, int b, int a, bool isFilled) {
  SDL_SetRenderDrawColor(app.renderer, r, g, b, a);

  if (isFilled) {
    SDL_RenderFillRect(app.renderer, rect);
  } else {
    SDL_RenderDrawRect(app.renderer, rect);
  }
}

void drawLine(float x1, float y1, float x2, float y2, int r, int g, int b, int a) {
  SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
  SDL_RenderDrawLine(app.renderer, x1, y1, x2, y2);
}

SDL_Texture* loadTexture(char* fileName) {
  SDL_Texture* texture;

  texture = IMG_LoadTexture(app.renderer, fileName);

  if (texture == NULL) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Failed to load image. %s.\n", fileName);
    exit(EXIT_FAILURE);
  }

  return texture;
}
