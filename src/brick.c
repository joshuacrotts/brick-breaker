#include "brick.h"

Entity* add_brick(float x, float y, uint32_t flags) {
    Entity* b;
    b = malloc(sizeof(Entity));
    memset(b, 0, sizeof(Entity));
    
    b->x = x;
    b->y = y;
    //TODO: ADD TEXTURE
    b->idFlags |= ID_DEFAULT_BRICK_MASK;
    b->flags |= flags;

    return b;
}

void brick_update(Entity* b) {

}

void brick_draw(Entity* b) {

}

void brick_die(Entity* b) {

}