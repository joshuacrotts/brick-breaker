#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "commons.h"

typedef struct Stage Stage;

struct Stage {
  Entity particleHead, *particleTail;
};

#endif
