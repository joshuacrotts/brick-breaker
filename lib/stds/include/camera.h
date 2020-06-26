#ifndef CAMERA_H
#define CAMERA_H

#include "stds.h"

extern app_t app;

/*
 * Applies an offset from the supplied entity, and stores
 * the coordinates in the App struct. Typically, in an overhead
 * style game, this supplied entity will be a reference to the
 * player. All offsets are pre-applied to the draw functions. 
 * To keep something from being updated, just re-add the values
 * x + app.camera.x, y + app.camera.y.
 */
extern void update_camera(entity_t*);

#endif
