#include "paddle.h"

static void keyInputUpdate(void);
static void checkBounds(void);

void init_paddle() {
    paddle = malloc(sizeof(Entity));
    memset(paddle, 0, sizeof(Entity));

    paddle->x = 20;
    paddle->y = SCREEN_HEIGHT - 20;
    paddle->w = 620;
    paddle->h = 10;
    paddle->idFlags |= ID_PLAYER_MASK;
}

void paddle_update(void) {
    paddle->x += paddle->dx;
    paddle->y += paddle->dy;

    checkBounds();
    keyInputUpdate();
}

void paddle_draw(void) {
    SDL_Rect rect;
    rect.x = (int32_t) paddle->x;
    rect.y = (int32_t) paddle->y;
    rect.w = paddle->w;
    rect.h = paddle->h;

    drawRect(&rect, 0xff, 0, 0, 0xff, true);
}

void paddle_die(void) {
    if (paddle->flags & DEATH_MASK) {
        free(paddle);
        return;
    }
}

static void checkBounds(void) {
    if (paddle->x < 0) {
        paddle->x = 0;
    } else if (paddle->x + paddle->w > SCREEN_WIDTH) {
        paddle->x = SCREEN_WIDTH - paddle->w;
    } else if (paddle->y < 0) {
        paddle->y = 0;
    } else if (paddle->y + paddle->h > SCREEN_HEIGHT) {
        paddle->y = SCREEN_HEIGHT - paddle->h;
    }
}

static void keyInputUpdate(void) {
    paddle->dx *= 0.95f;
    paddle->dy *= 0.95f;

    if (app.keyboard[SDL_SCANCODE_A]) {
        paddle->dx = -5.0f;
    }

    if (app.keyboard[SDL_SCANCODE_D]) {
        paddle->dx = 5.0f;
    }
}