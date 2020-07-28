#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "commons.h"
#include "game_defs.h"

typedef struct Stage     stage_t;
typedef struct Level     level_t;
typedef struct Debris    debris_t;
typedef struct ScoreItem score_item_t;

typedef enum BrickBreakerState {
  MENU,
  GAME,
} BrickBreakerState;

struct ScoreItem {
  float    x;
  float    y;
  char     text[16];
  int32_t  score;
  int32_t  life;
  uint32_t flags;

  score_item_t *next;
};

struct Level {
  size_t  brick_count;
  size_t  ball_count;
  int32_t last_break_timer;

  struct entity_t     ball_head, *ball_tail;
  struct entity_t     brick_head, *brick_tail;
  struct entity_t     powerup_head, *powerup_tail;
  struct entity_t     entity_head, *entity_tail;
  score_item_t score_item_head, *score_item_tail;

  struct background_t background;

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

  struct animation_t animation_head, *animation_tail;
  level_t     level_head, *level_tail;
  debris_t    debris_head, *debris_tail;
};

#endif
