#include "ball.h"

static void checkBounds(Entity*);

Entity* add_ball(int32_t x, int32_t y) {
    Entity* b;

    b = malloc(sizeof(Entity));
    memset(b, 0, sizeof(Entity));

    b->x = 480;
    b->y = 240;
    b->w = 3;
    b->h = b->w;
    b->dx = randomFloat(-5.0f, 5.0f);
    b->dy = randomFloat(-5.0f, 5.0f);

    b->idFlags |= ID_BALL_MASK;

    return b;
}

void ball_update(Entity* b) {
    b->x += b->dx;
    b->y += b->dy;

    checkBounds(b);
}

void ball_draw(Entity* b) {
    SDL_Rect rect;
    rect.x = (int32_t) b->x;
    rect.y = (int32_t) b->y;
    rect.w = b->w;
    rect.h = b->h;

    drawRect(&rect, 0xff, 0xff, 0, 0xff, true);
}

void ball_die(Entity* b) {
    if (b->flags & DEATH_MASK) {
        free(b);
        return;
    }
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