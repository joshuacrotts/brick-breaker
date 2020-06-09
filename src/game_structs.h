#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "commons.h"

typedef struct Stage Stage;
typedef struct Background Background;
typedef struct Emitter Emitter;

struct Background {
  int32_t x;
  int32_t y;
  uint32_t w;
  uint32_t h;

  float scaleX;
  float scaleY;

  SDL_Texture* backgroundTexture;
};

struct Emitter {
  Entity particleHead, *particleTail;
  int32_t x;
  int32_t y;
  uint32_t maxParticles;
  uint32_t idFlags;
  uint32_t flags;

  Emitter* next;
};

struct Stage {
  Animation animationHead, *animationTail;
  Emitter emitterHead, *emitterTail;
  Entity entityHead, *entityTail;
};

#endif
