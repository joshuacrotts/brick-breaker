#include "camera.h"

void updateCamera(Entity* focusPoint) {
  if (focusPoint != NULL) {
    app.camera.x = ((int32_t) focusPoint->x) - (SCREEN_WIDTH >> 1);
    app.camera.y = ((int32_t) focusPoint->y) - (SCREEN_HEIGHT >> 1);

    app.screenBounds.x = app.camera.x - SCREEN_WIDTH >> 1;
    app.screenBounds.y = app.camera.y - SCREEN_HEIGHT >> 1;
    app.screenBounds.w = app.camera.x + SCREEN_WIDTH >> 1;
    app.screenBounds.h = app.camera.y + SCREEN_HEIGHT >> 1;

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "x: %d, y: %d, w: %d, h: %d\n, ", app.screenBounds.x, app.screenBounds.y, app.screenBounds.w, app.screenBounds.h);
  }
}
