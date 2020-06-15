#include "hud.h"

static void drawLives(SDL_Color*);
static void drawTitle(SDL_Color*);
static SDL_Texture* heartTexture;

void init_HUD(void) {
    heartTexture = loadTexture("../res/img/life.png");
}

void draw_HUD(SDL_Color* c) {
    SDL_Rect bg;
    bg.x = INSETS;
    bg.y = INSETS;
    bg.w = SCREEN_WIDTH - (INSETS << 1);
    bg.h = 100;
    drawRect(&bg, 0, 0, 0, 0xC8, true);
    drawTitle(c);
    drawLives(c);
}

/*
 * Draws the hearts representing the user's 
 * lives. This may need to be non-static for accessibility
 * purposes (i.e. to change # of lives).
 */
static void drawLives(SDL_Color* c) {
    drawText(20, 20, c->r, c->g, c->b, "LIVES: ");
    for (int i = 0, x = 160; i < paddle->life; i++, x += 30) {
        blit(heartTexture, x, 20, false);
    }
}

/*
 *
 */
static void drawTitle(SDL_Color* c) {
    drawText(SCREEN_WIDTH / 3, 20, c->r, c->g, c->b, "BRICK BREAKER");
}