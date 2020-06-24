#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "commons.h"
#include "game_defs.h"

typedef struct Stage   stage_t;
typedef struct Emitter emitter_t;
typedef struct Level   level_t;
typedef struct Debris  debris_t;
typedef enum BrickBreakerState {
  MENU,
  GAME,
} BrickBreakerState;

struct Emitter {
  int32_t  x;
  int32_t  y;
  uint32_t maxParticles;
  uint32_t id_flags;
  uint32_t flags;

  entity_t   particle_head, *particle_tail;
  emitter_t *next;
};

struct Level {
  size_t brick_count;
  size_t ball_count;

  entity_t  ball_head, *ball_tail;
  entity_t  brick_head, *brick_tail;
  entity_t  powerup_head, *powerup_tail;
  entity_t  entity_head, *entity_tail;
  emitter_t emitter_head, *emitter_tail;

  background_t background;

  level_t *next;
};

struct Debris {
  float        x;
  float        y;
  float        dx;
  float        dy;
  uint32_t     flags;
  SDL_Texture *texture;
  SDL_Rect     rect;
  debris_t *   next;
};

struct Stage {
  uint32_t score;
  uint16_t level_id;

  BrickBreakerState state;

  animation_t animationHead, *animationTail;
  level_t     levelHead, *levelTail;
  debris_t    debris_head, *debris_tail;
};

#endif
