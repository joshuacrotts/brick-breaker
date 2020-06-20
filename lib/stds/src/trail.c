#include "../include/trail.h"

void add_trail(Entity* parent, int16_t alpha_decay, int16_t initial_alpha) {
    Trail* t;
    t = malloc(sizeof(Trail));
    memset(t, 0, sizeof(Trail));

    t->x = parent->x;
    t->y = parent->y;
    t->texture = parent->texture[0];
    t->alpha = initial_alpha;
    t->alpha_decay_rate = alpha_decay;

    app.trailTail->next = t;
    app.trailTail = t;
}

void trail_update(Trail* t) {
    t->alpha -= t->alpha_decay_rate;
    if (t->alpha <= 0) {
        t->flags |= DEATH_MASK;
    }
}

void trail_draw(Trail* t) {
    //print("%d", t->alpha);
    SDL_SetTextureBlendMode(t->texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(t->texture, t->alpha);
    blit(t->texture, t->x, t->y, false);
    SDL_SetTextureBlendMode(t->texture, SDL_BLENDMODE_NONE);
}