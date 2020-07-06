#include "../include/camera.h"

void
update_camera( entity_t *focus_point ) {
  if ( focus_point != NULL ) {
    app.camera.x = ( ( int32_t ) focus_point->x + focus_point->w / 2 ) - ( app.SCREEN_WIDTH >> 1 );
    app.camera.y = ( ( int32_t ) focus_point->y + focus_point->h / 2 ) - ( app.SCREEN_HEIGHT >> 1 );
    app.camera.w = app.SCREEN_WIDTH;
    app.camera.h = app.SCREEN_HEIGHT;

    if ( app.camera.x < 0 ) {
      app.camera.x = 0;
    }

    if ( app.camera.y < 0 ) {
      app.camera.y = 0;
    }

    if ( app.camera.x > app.LEVEL_WIDTH - app.camera.w ) {
      app.camera.x = app.LEVEL_WIDTH - app.camera.w;
    }

    if ( app.camera.y > app.LEVEL_HEIGHT - app.camera.h ) {
      app.camera.y = app.LEVEL_HEIGHT - app.camera.h;
    }
  }
}
