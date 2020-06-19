#include "../include/hud.h"

static void draw_lives(SDL_Color*);
static void draw_title(SDL_Color*);
static void draw_pregame_text(SDL_Color*);

static SDL_Texture* heartTexture;
static FadeColor fadeColor;
static char* title = "BRICK BREAKER";
static char* pregame_text = "PRESS SPACE TO START!";

void init_HUD(void) {
    heartTexture = loadTexture("res/img/life.png");

    SDL_Color c1;
    SDL_Color c2;

    c1.r = 0xff;
    c1.g = 0;
    c1.b = 0;

    c2.r = 0;
    c2.g = 0xff;
    c2.b = 0;
    fadeColor.c1 = c1;
    fadeColor.c2 = c2;
    fadeColor.time = 0.0f;
    fadeColor.alpha = 0.01f;
}

void update_HUD(void) {
    spawn_star_particles(NULL, randomInt(400, 2000), randomInt(900, 1100), 3, ID_P_STAR_MASK);
}

void draw_HUD(void) {
    SDL_Color c = combineFadeColor(&fadeColor);
    drawRectStroke(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, INSETS, c.r, c.g, c.b, 0xff);
    draw_title(&c);
    draw_lives(&c);

    if (app.gameState == PREGAME) {
        draw_pregame_text(&c);
    }
}

void draw_paused(void) {
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = SCREEN_WIDTH;
    r.h= SCREEN_HEIGHT;
    drawRect(&r, 0, 0, 0, 128, true);
    int fw, fh;
    getStringSize("PAUSED", &fw, &fh);
    drawText(SCREEN_WIDTH / 2 - fw / 2, SCREEN_HEIGHT / 2, 0xff, 0xff, 0xff, "PAUSED");
}

/*
 * Draws the hearts representing the user's 
 * lives. This may need to be non-static for accessibility
 * purposes (i.e. to change # of lives).
 */
static void draw_lives(SDL_Color* c) {
    drawText(20, 20, c->r, c->g, c->b, "LIVES: ");
    for (int i = 0, x = 160; i < paddle->life; i++, x += 30) {
        blit(heartTexture, x, 20, false);
    }
}

/*
 *
 */
static void draw_title(SDL_Color* c) {
    int fw, fh;
    getStringSize(title, &fw, &fh);
    drawText((SCREEN_WIDTH >> 1) - (fw >> 1), 20, c->r, c->g, c->b, title);
}

/*
 *
 */
static void draw_pregame_text(SDL_Color* c) {
    int fw, fh;
    getStringSize(pregame_text, &fw, &fh);    
    drawText((SCREEN_WIDTH / 2) - (fw / 2), SCREEN_HEIGHT >> 1, c->r, c->g, c->b, pregame_text);
}