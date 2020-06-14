#include "background.h"

static FadeColor fadeColor;

void init_background(void) {
  background = malloc(sizeof(Background));
  memset(background, 0, sizeof(Background));

  background->backgroundTexture = loadTexture("../res/img/background/space-1.png");
  background->x = 0;
  background->y = 0;

  uint32_t w;
  uint32_t h;

  SDL_QueryTexture(background->backgroundTexture, NULL, NULL, &w, &h);

  background->w = w;
  background->h = h;
  background->scaleX = 1.0;
  background->scaleY = 1.0;

  SDL_Color c1;
  SDL_Color c2;

  c1.r = 0xff;
  c1.g = 0;
  c1.b = 0;

  c2.r = 0;
  c2.g = 0xff;
  c2.b = 0;
  fadeColor.c1 = c1;
  fadeColor.c2 = c2;
  fadeColor.time = 0.0f;
  fadeColor.alpha = 0.01f;
}

void background_draw(void) {
  blitTextureScaled(background->backgroundTexture, background->x, background->y, background->scaleX, background->scaleY, 0);
  
  SDL_Color c = combineFadeColor(&fadeColor);
  drawRectStroke(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, INSETS, c.r, c.g, c.b, 0xff);
  drawHUD(&c);
}

void background_update(void) {
  background->x = 0 - app.camera.x;
  background->y = 0 - app.camera.y;
}

void background_die(void) {
  SDL_DestroyTexture(background->backgroundTexture);
  free(background);
}
