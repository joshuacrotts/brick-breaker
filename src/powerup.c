#include "../include/powerup.h"

#define COIN_SCORE 500
#define POWERUP_DESCENT 3

Entity* add_powerup(float x, float y, uint32_t flags, int8_t identifier) {
    Entity* p;
    p = malloc(sizeof(Entity));
    memset(p, 0, sizeof(Entity));

    p->x = x;
    p->y = y;
    p->idFlags |= ID_DEFAULT_POWERUP_MASK;
    p->flags |= flags | POWERUP_INACTIVE;
    p->identifier = identifier;

    Animation* a;

    switch(identifier) {
        case MULTI_BALL:
            a = add_spritesheet("res/img/powerup/multi.png", 10, 0.05f, 0, 0);
            break;
        case LARGE_PADDLE:
            a = add_spritesheet("res/img/powerup/large.png", 10, 0.05f, 0, 0);
            break;
        case EXTRA_LIFE:
            a = add_spritesheet("res/img/powerup/extra_life.png", 8, 0.09f, 0, 0);
            break;
        case GOLD_COIN:
            a = add_spritesheet("res/img/powerup/gold_coin.png", 16, 0.05f, 0, 0);
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
    if (p->flags & POWERUP_ACTIVE) {
        if (--p->life < 0) {
            if (p->identifier == LARGE_PADDLE) {
                powerup_large_deactivate(p);
                return;
            }
        }
    }

    if (p->animation != NULL) {
        animation_update(p);
    }

    p->y += POWERUP_DESCENT;

    if (p->y > SCREEN_HEIGHT) {
        p->flags |= DEATH_MASK;
    }
}

void powerup_draw(Entity* p) {
    if (p->animation != NULL && p->flags & POWERUP_INACTIVE) {
        animation_draw(p);
    }
}

void powerup_die(Entity* p) {
    if (p->flags & DEATH_MASK) {
        free(p);
    }
}

void powerup_large_activate(Entity* p) {
    p->life = FPS * 10;
    p->flags |= POWERUP_ACTIVE;
    paddle->scaleX = 2.0f;
}

void powerup_large_deactivate(Entity* p) {
    paddle->scaleX = 1.0f;
    p->flags |= DEATH_MASK;
}

void powerup_multi_activate(Entity* p) {
    Entity* b1;
    Entity* b2;
    b1 = add_ball(randomFloat(300, 600), SCREEN_HEIGHT / 2, 0);
    b2 = add_ball(randomFloat(300, 600), SCREEN_HEIGHT / 2, 0);
    
    currentLevel->ballTail->next = b1;
    currentLevel->ballTail = b1;
    currentLevel->ballTail->next = b2;
    currentLevel->ballTail = b2;

    p->flags |= DEATH_MASK;
}

void powerup_coin_activate(Entity* p) {
    stage.score += COIN_SCORE;
    playSound(SND_COIN, CH_ANY);
    p->flags |= DEATH_MASK;
}

void powerup_life_activate(Entity* p) {
    if (paddle->life <= 4) {
        paddle->life++;
    }

    p->flags |= DEATH_MASK;
}