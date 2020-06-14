#ifndef GAME_DEFS_H
#define GAME_DEFS_H

#include "commons.h"

#define DEATH_MASK                       0x10000000
#define MOVE_MASK                        0x20000000

#define BALL_SPEED                               10
#define ID_BALL_MASK                     0x00000030
#define POWERUP_ACTIVE                   0x00000102
#define POWERUP_INACTIVE                 0x00000101
#define ID_DEFAULT_POWERUP_MASK          0x00000100
#define ID_DEFAULT_BRICK_MASK            0x00000002
#define ID_PLAYER_MASK                   0x00000001
#define ID_PARTICLE_MASK                 0x00000010
#define ID_SCATTER_PARTICLE_MASK         0x00000020
#define ID_P_ANIMATED_PARTICLE_MASK      0x00000030
#define ID_P_BLOOD_CIRCLE_MASK           0x00000041
#define ID_P_BLOOD_SQUARE_MASK           0x00000042

enum Powerup {
    MULTI_BALL
};

enum Brick {
    RED
};

#endif
