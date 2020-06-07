#include "camera.h"

void updateCamera(Entity* focusPoint) {
  if (focusPoint != NULL) {
    app.camera.x = focusPoint->x - (SCREEN_WIDTH >> 1);
    app.camera.y = focusPoint->y - (SCREEN_HEIGHT >> 1);
  }
}
