#include "../include/powerup.h"

#define COIN_SCORE      500
#define POWERUP_DESCENT 3
#define MAX_LIVES       4


entity_t* 
add_powerup(float x, float y, uint32_t flags, int8_t identifier) {
    entity_t *p;
    p = malloc(sizeof(entity_t));
    memset(p, 0, sizeof(entity_t));

    p->x = x;
    p->y = y;
    p->id_flags |= ID_DEFAULT_POWERUP_MASK;
    p->flags |= flags | POWERUP_INACTIVE;
    p->identifier = identifier;

    animation_t *a;

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


void 
powerup_update(entity_t *p) {
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


void 
powerup_draw(entity_t *p) {
    if (p->animation != NULL && p->flags & POWERUP_INACTIVE) {
        animation_draw(p);
    }
}


void 
powerup_die(entity_t *p) {
    if (p->flags & DEATH_MASK) {
        free(p);
    }
}


void 
powerup_large_activate(entity_t *p) {
    p->life = FPS * 10;
    p->flags |= POWERUP_ACTIVE;
    paddle->scale_x = 2.0f;
}


void 
powerup_large_deactivate(entity_t *p) {
    paddle->scale_x = 1.0f;
    p->flags |= DEATH_MASK;
}


void 
powerup_multi_activate(entity_t *p) {
    entity_t *b1;
    entity_t *b2;
    b1 = add_ball(random_float(300, 600), SCREEN_HEIGHT / 2, 0);
    b2 = add_ball(random_float(300, 600), SCREEN_HEIGHT / 2, 0);
    
    currentLevel->ball_tail->next = b1;
    currentLevel->ball_tail = b1;
    currentLevel->ball_tail->next = b2;
    currentLevel->ball_tail = b2;

    p->flags |= DEATH_MASK;
}


void 
powerup_coin_activate(entity_t *p) {
    stage.score += COIN_SCORE;
    play_sound(SND_COIN, CH_ANY);
    p->flags |= DEATH_MASK;
}


void 
powerup_life_activate(entity_t *p) {
    if (paddle->life <= MAX_LIVES) {
        paddle->life++;
    }

    p->flags |= DEATH_MASK;
}