#include "hud.h"

void drawHUD(SDL_Color* c) {
    SDL_Rect bg;
    bg.x = INSETS;
    bg.y = INSETS;
    bg.w = SCREEN_WIDTH - (INSETS << 1);
    bg.h = 100;
    drawRect(&bg, 0, 0, 0, 0xC8, true);

    drawText(SCREEN_WIDTH / 3, 20, c->r, c->g, c->b, "BRICK BREAKER");
}