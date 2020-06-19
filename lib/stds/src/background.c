#include "../include/background.h"

Background* init_background(char* file) {
  Background* background;
  
  background = malloc(sizeof(Background));
  memset(background, 0, sizeof(Background));

  background->x = 0;
  background->y = 0;

  uint32_t w;
  uint32_t h;

  background->backgroundTexture = loadTexture(file);
  SDL_QueryTexture(background->backgroundTexture, NULL, NULL, &w, &h);

  background->w = w;
  background->h = h;
  background->scaleX = 1.0;
  background->scaleY = 1.0;

  return background;
}

void background_update(Background* background) {
  background->x = 0 - app.camera.x;
  background->y = 0 - app.camera.y;
}

void background_draw(Background* background) {
  blitTextureScaled(background->backgroundTexture, background->x, background->y, background->scaleX, background->scaleY, 0);
}

void background_die(Background* background) {
  SDL_DestroyTexture(background->backgroundTexture);
  free(background);
}
