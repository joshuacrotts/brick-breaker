#include "powerup.h"

Entity* add_powerup(float x, float y, uint32_t flags, int8_t identifier) {
    Entity* p;
    p = malloc(sizeof(Entity));
    memset(p, 0, sizeof(Entity));

    p->x = x;
    p->y = y;
    p->idFlags |= ID_DEFAULT_POWERUP_MASK;
    p->flags |= flags | POWERUP_INACTIVE;

    Animation* a;

    switch(identifier) {
        case MULTI_BALL:
            a = add_spritesheet("../res/img/powerup/multi.png", 10, 0.05f, 0, 0);
            break;
        default:
            exit(EXIT_ERROR);            
    }
    a->flags |= ANIMATION_ACTIVE_MASK;

    p->w = a->w;
    p->h = a->h;
    p->animation = a;

    return p;
}

void powerup_update(Entity* p) {
    if (p->animation != NULL) {
        animation_update(p);
    }

    p->y += 3;

    if (p->y > SCREEN_HEIGHT) {
        p->flags |= DEATH_MASK;
    }
}

void powerup_draw(Entity* p) {
    if (p->animation != NULL) {
        animation_draw(p);
    }
}

void powerup_activate(Entity* p) {
    //...
    p->flags |= DEATH_MASK;
    return;
}

void powerup_die(Entity* p) {
    if (p->flags & DEATH_MASK) {
        free(p);
    }
}