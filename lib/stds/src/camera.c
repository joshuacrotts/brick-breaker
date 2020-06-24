#include "../include/camera.h"

void
update_camera( entity_t *focus_point ) {
  if ( focus_point != NULL ) {
    app.camera.x = ( ( int32_t ) focus_point->x + focus_point->w / 2 ) - ( SCREEN_WIDTH >> 1 );
    app.camera.y = ( ( int32_t ) focus_point->y + focus_point->h / 2 ) - ( SCREEN_HEIGHT >> 1 );
    app.camera.w = SCREEN_WIDTH;
    app.camera.h = SCREEN_HEIGHT;

    if ( app.camera.x < 0 ) {
      app.camera.x = 0;
    }

    if ( app.camera.y < 0 ) {
      app.camera.y = 0;
    }

    if ( app.camera.x > LEVEL_WIDTH - app.camera.w ) {
      app.camera.x = LEVEL_WIDTH - app.camera.w;
    }

    if ( app.camera.y > LEVEL_HEIGHT - app.camera.h ) {
      app.camera.y = LEVEL_HEIGHT - app.camera.h;
    }
  }
}
