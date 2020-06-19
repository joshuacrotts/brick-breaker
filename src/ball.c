#include "../include/ball.h"

static void check_bounds(Entity*);

Entity* add_ball(float x, float y, uint32_t flags) {
    Entity* b;
    print("adding ball");
    b = malloc(sizeof(Entity));
    memset(b, 0, sizeof(Entity));

    b->x = x;
    b->y = y;
    b->texture[0] = loadTexture("res/img/ball_sprite_1.png");
    SDL_QueryTexture(b->texture[0], NULL, NULL, &b->w, &b->h);

    // Continuously generate a speed that is reasonable.
    do {
        b->dx = randomFloat(-10.0f, 10.0f);
    } while(b->dx < 7.0f && b->dx > -7.0f);

    do {
        b->dy = randomFloat(-10.0f, 10.0f);
    } while(b->dy < 7.0f && b->dy > -7.0f);

    b->idFlags |= ID_BALL_MASK;
    b->flags |= flags;

    return b;
}

void ball_update(Entity* b) {
    b->x += b->dx;
    b->y += b->dy;

    check_bounds(b);
}

void ball_draw(Entity* b) {
    blit(b->texture[0], b->x, b->y, false);
}

void ball_die(Entity* b) {
    free(b);
}

static void check_bounds(Entity* b) {
    if (b->x < 0) {
        b->x = 0;
        b->dx = -b->dx;
    } else if (b->x + b->w > SCREEN_WIDTH) {
        b->x -= b->w;
        b->dx = -b->dx;
    } else if (b->y < 0) {
        b->y = 0;
        b->dy = -b->dy;
    } else if (b->y + b->h > SCREEN_HEIGHT) {
        b->flags |= DEATH_MASK;
    }
}