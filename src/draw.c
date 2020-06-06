#include "draw.h"


/*
 * Clears the screen with a black color.
 */
void prepareScene() {
  SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
  SDL_RenderClear(app.renderer);
}

/*
 * Presents the current scene from the application.
 */
void presentScene() {
  SDL_RenderPresent(app.renderer);
}

/*
 * Copies the graphics from the texture to a different
 * rectangle. This moves the sprite.
 */
void blit(SDL_Texture* texture, int x, int y) {
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;

  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

  SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

/*
 * Renders a partition of a texture, specified by src, at
 * coordinates (x, y).
 */
void blitRect(SDL_Texture* texture, SDL_Rect* src, int x, int y) {
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  dest.w = src->w;
  dest.h = src->h;
  SDL_RenderCopy(app.renderer, texture, src, &dest);
}

/*
 * Loads an image from the specified path. An error is
 * displayed if the file cannot be found or is not
 * loadable.
 */
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
