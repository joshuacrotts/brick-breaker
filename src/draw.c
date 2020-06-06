#include "draw.h"

void prepareScene() {
  SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
  SDL_RenderClear(app.renderer);
}

void presentScene() {
  SDL_RenderPresent(app.renderer);
}

void blit(SDL_Texture* texture, int x, int y, bool isCenter) {
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;

  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

  if (isCenter) {
    dest.x -= (dest.w >> 1);
    dest.y -= (dest.y >> 1);
  }

  SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitRect(SDL_Texture* texture, SDL_Rect* src, int x, int y) {
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = src->w;
  dest.h = src->h;
  SDL_RenderCopy(app.renderer, texture, src, &dest);
}

SDL_Texture* loadTexture(char* fileName) {
  SDL_Texture* texture;

  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s.\n", fileName);

  texture = IMG_LoadTexture(app.renderer, fileName);

  if (texture == NULL) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Failed to load image. %s.\n", fileName);
    exit(EXIT_FAILURE);
  }

  return texture;
}
