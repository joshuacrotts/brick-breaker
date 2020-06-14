#include "brick.h"

static void update_brick_status(Entity*);

Entity* add_brick(float x, float y, uint32_t flags, int8_t identifier) {
    Entity* b;
    b = malloc(sizeof(Entity));
    memset(b, 0, sizeof(Entity));
    
    b->x = x;
    b->y = y;
    b->idFlags |= ID_DEFAULT_BRICK_MASK;
    b->flags |= flags;
    b->life = 4;
    b->identifier = identifier;

    switch(identifier) {
        case RED:
            b->texture = loadTexture("../res/img/brick/red/red_0.png");
            b->texture2 = loadTexture("../res/img/brick/red/red_1.png");
            b->texture3 = loadTexture("../res/img/brick/red/red_2.png");
            b->texture4 = loadTexture("../res/img/brick/red/red_3.png");
            break;
        default:
            exit(EXIT_FAILURE);
    }
    
    SDL_QueryTexture(b->texture, NULL, NULL, &b->w, &b->h);

    return b;
}

void brick_update(Entity* b) {
    update_brick_status(b);
}

void brick_draw(Entity* b) {
    blit(b->texture, b->x, b->y, false);
}

void brick_die(Entity* b) {
    free(b);
}

/*
 *
 */
static void update_brick_status(Entity* b) {
    switch(b->life) {
        case 4: return;
        case 3: b->texture = b->texture2;
                break;
        case 2: b->texture = b->texture3;
                break;
        case 1: b->texture = b->texture4;
                break;
        case 0: b->flags |= DEATH_MASK;
                break;
    }
}