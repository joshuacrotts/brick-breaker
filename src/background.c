#include "background.h"

Background* background;

void init_background(void) {
  background = malloc(sizeof(Background));
  memset(background, 0, sizeof(Background));

  background->backgroundTexture = loadTexture("../res/img/panel1.jpg");
  background->x = 0;
  background->y = 0;

  uint32_t w;
  uint32_t h;

  SDL_QueryTexture(background->backgroundTexture, NULL, NULL, &w, &h);

  background->w = w;
  background->h = h;
  background->scaleX = 1.0;
  background->scaleY = 1.0;
}

void background_draw(void) {
  //blit(background->backgroundTexture, background->x, background->y, false);
  blitTextureScaled(background->backgroundTexture, background->x, background->y, background->scaleX, background->scaleY, 0);
}

void background_update(void) {
  background->x = 0 - app.camera.x;
  background->y = 0 - app.camera.y;
}

void background_die(void) {
  SDL_DestroyTexture(background->backgroundTexture);
  free(background);
}
