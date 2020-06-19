#include "../include/camera.h"

void updateCamera(Entity* focusPoint) {
  if (focusPoint != NULL) {
    app.camera.x = ((int32_t) focusPoint->x + focusPoint->w / 2) - (SCREEN_WIDTH >> 1);
    app.camera.y = ((int32_t) focusPoint->y + focusPoint->h / 2) - (SCREEN_HEIGHT >> 1);
    app.camera.w = SCREEN_WIDTH;
    app.camera.h = SCREEN_HEIGHT;

    if (app.camera.x < 0) {
      app.camera.x = 0;
    }

    if (app.camera.y < 0) {
      app.camera.y = 0;
    }
    
    if (app.camera.x > LEVEL_WIDTH - app.camera.w) {
      app.camera.x = LEVEL_WIDTH - app.camera.w;
    }

    if (app.camera.y > LEVEL_HEIGHT - app.camera.h) {
      app.camera.y = LEVEL_HEIGHT - app.camera.h;
    }
  }
}
