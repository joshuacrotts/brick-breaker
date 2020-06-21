#include "../include/background.h"


background_t* 
init_background(char *file) {
  background_t *background;
  
  background = malloc(sizeof(background_t));

  if (background == NULL) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for background_t. %s.\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  memset(background, 0, sizeof(background_t));

  background->x = 0;
  background->y = 0;

  uint32_t w;
  uint32_t h;

  background->background_texture = load_texture(file);
  SDL_QueryTexture(background->background_texture, NULL, NULL, &w, &h);

  background->w = w;
  background->h = h;
  background->scale_x = 1.0;
  background->scale_y = 1.0;

  return background;
}


void 
background_update(background_t *background) {
  background->x = 0 - app.camera.x;
  background->y = 0 - app.camera.y;
}


void 
background_draw(background_t *background) {
  blit_texture_scaled(background->background_texture, background->x, background->y, background->scale_x, background->scale_y, 0);
}


void 
background_die(background_t *background) {
  SDL_DestroyTexture(background->background_texture);
  free(background);
}
