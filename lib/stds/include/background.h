#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "stds.h"
#include "../include/draw.h"

extern App app;

extern Background* init_background(char*);
extern void background_update(Background*);
extern void background_draw(Background*);
extern void background_die(Background*);

#endif
