#include "paddle.h"

static void key_input_update(void);
static void check_bounds(void);

void init_paddle(void) {
    paddle = malloc(sizeof(Entity));
    memset(paddle, 0, sizeof(Entity));

    paddle->life = 3;
    paddle->x = 20;
    paddle->y = SCREEN_HEIGHT - 40;
    paddle->texture[0] = loadTexture("../res/img/paddle.png");
    SDL_QueryTexture(paddle->texture[0], NULL, NULL, &paddle->w, &paddle->h);

    paddle->idFlags |= ID_PLAYER_MASK;
}

void paddle_update(void) {
    paddle->x += paddle->dx;
    paddle->y += paddle->dy;

    check_bounds();
    key_input_update();
}

void paddle_draw(void) {
    blit(paddle->texture[0], paddle->x, paddle->y, false);
}

void paddle_die(void) {
    free(paddle);
}

static void check_bounds(void) {
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

static void key_input_update(void) {
    if (app.gameState != PAUSED) {
        paddle->dx *= 0.95f;
        paddle->dy *= 0.95f;

        if (app.keyboard[SDL_SCANCODE_A]) {
            paddle->dx = -10.0f;
        }

        if (app.keyboard[SDL_SCANCODE_D]) {
            paddle->dx = 10.0f;
        }
    }
}