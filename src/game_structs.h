#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "commons.h"

typedef struct Stage Stage;
typedef struct Background Background;

struct Background {
  int32_t x;
  int32_t y;
  uint32_t w;
  uint32_t h;

  float scaleX;
  float scaleY;

  SDL_Texture* backgroundTexture;
};

struct Stage {
  Entity particleHead, *particleTail;
  Animation animationHead, *animationTail;
};

#endif
