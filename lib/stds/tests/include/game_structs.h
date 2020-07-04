#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "../../include/stds.h"

typedef struct Stage stage_t;


struct Stage {
    trail_t trail_head, *trail_tail;
    entity_t enemy_head, *enemy_tail;
};

#endif