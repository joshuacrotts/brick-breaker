//=============================================================================================//
// FILENAME :       camera.c
//
// DESCRIPTION :
//        This file defines the function for updating a camera around a parent entity. Generally,
//        this should be the player. All offsets are pre-applied to the draw functions. To keep
//        something from being updated, just re-add the valuesx + app.camera.x, y + app.camera.y.
//
// NOTES :
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.
//
// AUTHOR :   Joshua Crotts        START DATE :    18 Jun 2020
//
//=============================================================================================//

#include "../include/camera.h"

/**
 * Applies an offset from the supplied entity, and stores
 * the coordinates in the App struct. Typically, in an overhead
 * style game, this supplied entity will be a reference to the
 * player. If you want to remove the offset from an entity,
 * just add the coordinates of the camera to your entity
 * x + app.camera.x and y + app.camera.y. Note that if you have
 * the option to modify the placement via a method in draw.c,
 * do it there instead.
 *
 * @param entity_t* pointer to parent entity.
 *
 * @return void.
 */
void
Stds_CameraUpdate( const struct entity_t *focus_point ) {
  if ( focus_point != NULL ) {
    app.camera.x = ( focus_point->x + focus_point->w / 2 ) - ( app.SCREEN_WIDTH >> 1 );
    app.camera.y = ( focus_point->y + focus_point->h / 2 ) - ( app.SCREEN_HEIGHT >> 1 );
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
