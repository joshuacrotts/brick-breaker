#ifndef CAMERA_H
#define CAMERA_H

#include "stds.h"

extern app_t app;

/*
 * Applies an offset from the supplied entity, and stores
 * the coordinates in the App struct. Typically, in an overhead
 * style game, this supplied entity will be a reference to the
 * player. Then, whenever you draw anything, just subtract the
 * coordinates from your other entities/objects in the world
 * (i.e. entity.x - app.camera.x and entity.y - app.camera.y).
 */
extern void update_camera(entity_t*);

#endif
