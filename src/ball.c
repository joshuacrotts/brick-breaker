#include "ball.h"

static void checkBounds(Entity*);

Entity* add_ball(float x, float y, uint32_t flags) {
    Entity* b;

    b = malloc(sizeof(Entity));
    memset(b, 0, sizeof(Entity));

    b->x = x;
    b->y = y;
    b->texture = loadTexture("../res/img/ball_sprite_0.png");
    SDL_QueryTexture(b->texture, NULL, NULL, &b->w, &b->h);

    b->dx = randomFloat(-5.0f, 5.0f);
    b->dy = randomFloat(-5.0f, 5.0f);

    b->idFlags |= ID_BALL_MASK;
    b->flags |= flags;

    return b;
}

void ball_update(Entity* b) {
    b->x += b->dx;
    b->y += b->dy;

    checkBounds(b);
}

void ball_draw(Entity* b) {
    blit(b->texture, b->x, b->y, false);
}

void ball_die(Entity* b) {
    free(b);
}

static void checkBounds(Entity* b) {
    if (b->x < 0) {
        b->dx = -b->dx;
    } else if (b->x + b->w > SCREEN_WIDTH) {
        b->dx = -b->dx;
    } else if (b->y < 0) {
        b->dy = -b->dy;
    } else if (b->y + b->h > SCREEN_HEIGHT) {
        b->flags |= DEATH_MASK;
    }
}