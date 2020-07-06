#ifndef GAME_DEFS_H
#define GAME_DEFS_H

#include "commons.h"

#define MOVE_MASK 0x20000000

#define MAX_DEBRIS_IMGS             3
#define INSETS                      8
#define BALL_SPEED                  10
#define ID_BALL_MASK                0x00000001
#define POWERUP_ACTIVE              0x00200000
#define POWERUP_INACTIVE            0x00400000
#define ID_DEFAULT_POWERUP_MASK     0x00100000
#define ID_DEFAULT_BRICK_MASK       0x00001000
#define ID_PLAYER_MASK              0x00002000
#define ID_PARTICLE_MASK            0x00004000
#define ID_P_SQUARE_MASK            0x00008000
#define ID_P_CIRCLE_MASK            0x00010000
#define ID_SCATTER_PARTICLE_MASK    0x00000020
#define ID_P_ANIMATED_PARTICLE_MASK 0x00000040
#define ID_P_BLOOD_CIRCLE_MASK      0x00000080
#define ID_P_BLOOD_SQUARE_MASK      0x00000100
#define ID_P_STAR_MASK              0x00000200
#define ID_BALL_BREAK_MASK          0x00000002

enum Powerup { MULTI_BALL, LARGE_PADDLE, EXTRA_LIFE, GOLD_COIN };

enum Brick {
  NULL_COLOR,  // 0
  RED,         // 1
  BLUE,        // 2
  BROWN,       // 3
  YELLOW,      // 4
  ORANGE,      // 5
  PURPLE,      // 6
  DARK_GREEN,  // 7
  LIGHT_GREEN, // 8
  LIGHT_BLUE,  // 9
  // THESE NUMBERS ARE NOT CORRECT.
};

#endif
