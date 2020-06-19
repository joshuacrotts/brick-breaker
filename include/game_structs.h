#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "commons.h"

typedef struct Stage Stage;
typedef struct Emitter Emitter;
typedef struct Level Level;
typedef struct Debris Debris;

struct Emitter {
  Entity particleHead, *particleTail;
  int32_t x;
  int32_t y;
  uint32_t maxParticles;
  uint32_t idFlags;
  uint32_t flags;

  Emitter* next;
};

struct Level {
  Entity ballHead, *ballTail;
  Entity brickHead, *brickTail;
  Entity powerupHead, *powerupTail;
  Entity entityHead, *entityTail;
  Emitter emitterHead, *emitterTail;

  Background background;

  Level* next;
};

struct Debris {
  float x;
  float y;
  float dx;
  float dy;
  uint32_t flags;
  SDL_Texture* texture;
  SDL_Rect rect;
  Debris* next;
};

struct Stage {
  Animation animationHead, *animationTail;
  Level levelHead, *levelTail;
  Debris debrisHead, *debrisTail;

  uint32_t score;
};

#endif
