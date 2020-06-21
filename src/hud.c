#include "../include/hud.h"

static SDL_Texture* heartTexture;
static fade_color_t fadeColor;
static char* title = "BRICK BREAKER";
static char* pregame_text = "PRESS SPACE TO START!";

static void draw_lives(SDL_Color*);
static void draw_title(SDL_Color*);
static void draw_pregame_text(SDL_Color*);
static void draw_score(SDL_Color*);


void 
init_HUD(void) {
    heartTexture = load_texture("res/img/life.png");

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


void 
update_HUD(void) {
    spawn_star_particles(NULL, random_int(400, 2000), random_int(900, 1100), 3, ID_P_STAR_MASK);
}


void 
draw_HUD(void) {
    SDL_Color c = combine_fade_color(&fadeColor);
    draw_rect_stroke(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, INSETS, c.r, c.g, c.b, 0xff);
    draw_title(&c);
    draw_lives(&c);
    draw_score(&c);

    if (app.game_state == PREGAME) {
        draw_pregame_text(&c);
    }
}


void 
draw_paused(void) {
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = SCREEN_WIDTH;
    r.h= SCREEN_HEIGHT;

    draw_rect(&r, 0, 0, 0, 128, true);
    int fw, fh;
    get_string_size("PAUSED", "res/fonts/nes.ttf", 24, &fw, &fh);
    draw_text(SCREEN_WIDTH / 2 - fw / 2, SCREEN_HEIGHT / 2, 0xff, 0xff, 0xff, "res/fonts/nes.ttf", 24, "PAUSED");
}



/*
 * Draws the hearts representing the user's 
 * lives. This may need to be non-static for accessibility
 * purposes (i.e. to change # of lives).
 */
static void 
draw_lives(SDL_Color* c) {
    int fw, fh;
    int tw, th;
    int initial_offset = 20;
    int offset = 5;

    draw_text(initial_offset, initial_offset, c->r, c->g, c->b, "res/fonts/nes.ttf", 12, "LIVES: ");

    SDL_QueryTexture(heartTexture, NULL, NULL, &tw, &th);
    get_string_size("LIVES: ", "res/fonts/nes.ttf", 12, &fw, &fh);

    int v_offset = initial_offset + fh + offset;

    for (int i = 0, x = initial_offset; i < paddle->life; i++, x += (tw + offset)) {
        blit_texture(heartTexture, x, v_offset, false);
    }
}



/*
 *
 */
static void 
draw_title(SDL_Color* c) {
    int fw, fh;
    get_string_size(title, "res/fonts/nes.ttf", 12, &fw, &fh);
    draw_text((SCREEN_WIDTH >> 1) - (fw >> 1), 20, c->r, c->g, c->b, "res/fonts/nes.ttf", 12, title);
}


/*
 *
 */
static void 
draw_pregame_text(SDL_Color* c) {
    int fw, fh;
    get_string_size(pregame_text, "res/fonts/nes.ttf", 24, &fw, &fh);    
    draw_text((SCREEN_WIDTH / 2) - (fw / 2), (SCREEN_HEIGHT >> 1) + (SCREEN_HEIGHT / 4), c->r, c->g, c->b, "res/fonts/nes.ttf", 24, pregame_text);
}


/*
 *
 */
static void 
draw_score(SDL_Color* c) {
    int fw, fh;
    int offset = 20;
    get_string_size("Score:", "res/fonts/nes.ttf", 12, &fw, &fh);
    int v_offset = offset + fh + 5;

    // Draw score label.
    draw_text(SCREEN_WIDTH - fw - offset, offset, c->r, c->g, c->b, "res/fonts/nes.ttf", 12, "Score:");

    // Draw numeric score.
    draw_text(SCREEN_WIDTH - fw - offset, v_offset, 0xff, 0xff, 0xff, "res/fonts/nes.ttf", 12, "%d", stage.score);
}