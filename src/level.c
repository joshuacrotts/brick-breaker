#include "level.h"

static void draw_balls(void);
static void draw_powerups(void);
static void draw_bricks(void);
static void update_balls(void);
static void update_powerups(void);
static void update_bricks(void);

static void ball_hit_paddle(Entity*);
static void ball_hit_brick(Entity*);
static void powerup_hit_paddle(Entity*);

Level* add_level() {
    Level* level;

    level = malloc(sizeof(Level));
    memset(level, 0, sizeof(Level));

    level->ballTail = &level->ballHead;
    level->emitterTail = &level->emitterHead;
    level->entityTail = &level->entityHead;
    level->ballTail = &level->ballHead;
    level->brickTail = &level->brickHead;
    level->powerupTail = &level->powerupHead;

    for (int x = 20; x <= SCREEN_WIDTH - 80; x += 92) {
        for (int y = 120; y <= 300; y += 32) {
            Entity* b;

            switch (randomInt(0, 1)) {
              case 0: b = add_brick(x, y, 0, RED);
                      break;
              case 1: b = add_brick(x, y, 0, BLUE);
                      break;
            }
            
            level->brickTail->next = b;
            level->brickTail = b;
        }
    }

    return level;
}

void level_update() {
    update_balls();
    update_powerups();
    update_bricks();
}

void level_draw() {
    draw_balls();
    draw_powerups();
    draw_bricks();
}

void level_die() {
    Level* l; 

    for (l = stage.levelHead.next; l != NULL; l = l->next) {
        free(l);
    }

    if (currentLevel != NULL) {
        free(currentLevel);
        currentLevel = NULL;
    }
}

/*
 *
 */
static void update_balls(void) {
  Entity* b;
  Entity* prevBall;

  prevBall = &currentLevel->ballHead;

  for (b = currentLevel->ballHead.next; b != NULL; b = b->next) {
    if (b->idFlags & ID_BALL_MASK) {
      ball_hit_paddle(b);
      ball_hit_brick(b);
      ball_update(b);
    }

    if (b->flags & DEATH_MASK) {
      if (b == currentLevel->ballTail) {
          currentLevel->ballTail = prevBall;
      }

      prevBall->next = b->next;
      ball_die(b);
      b = prevBall;
    }

    prevBall = b;
  }
}

/*
 *
 */
static void update_powerups(void) {
  Entity* p;
  Entity* prev;

  prev = &currentLevel->powerupHead;

  for (p = currentLevel->powerupHead.next; p != NULL; p = p->next) {
    if (p->idFlags & ID_DEFAULT_POWERUP_MASK) {
      powerup_hit_paddle(p);
      powerup_update(p);
    }

    if (p->flags & DEATH_MASK) {
      if (p == currentLevel->powerupTail) {
        currentLevel->powerupTail = prev;
      }

      prev->next = p->next;
      powerup_die(p);
      p = prev;
    }
    prev = p;
  }
}

/*
 *
 */
static void update_bricks(void) {
    Entity* brick;
    Entity* prevBrick;

    prevBrick = &currentLevel->brickHead;

    for (brick = currentLevel->brickHead.next; brick != NULL; brick = brick->next) {
      brick_update(brick);
      
      if (brick->flags & DEATH_MASK) {
          if (brick == currentLevel->brickTail) {
              currentLevel->brickTail = prevBrick;
          }
          prevBrick->next = brick->next;
          brick_die(brick);
          brick = prevBrick;
      }
      prevBrick = brick;
    }
}

/*
 *
 */
static void draw_powerups(void) {
  Entity* p;

  for (p = currentLevel->powerupHead.next; p != NULL; p = p->next) {
    if (p->idFlags & ID_DEFAULT_POWERUP_MASK) {
      powerup_draw(p);
    }
  }
}

/*
 *
 */
static void draw_balls(void) {
  Entity* b;

  for (b = currentLevel->ballHead.next; b != NULL; b = b->next) {
    if (b->idFlags & ID_BALL_MASK) {
      ball_draw(b);
    }
  }
}

/*
 *
 */
static void draw_bricks(void) {
    Entity* b;

    for (b = currentLevel->brickHead.next; b != NULL; b = b->next) {
      brick_draw(b);
    }
}

/*
 *
 */
static void ball_hit_brick(Entity* ball) {
    Entity* brick;

    for (brick = currentLevel->brickHead.next; brick != NULL; brick = brick->next) {
      if (collision((int32_t) ball->x, (int32_t) ball->y, ball->w, ball->h,
                    (int32_t) brick->x, (int32_t) brick->y, brick->w, brick->h)) {
          brick->life--;
          ball->dy = -ball->dy;
          // Add debris here.
          add_debris(brick, 0);
          break;
      }
    }
}

/*
 *
 */
static void ball_hit_paddle(Entity* b) {

  if (collision((int32_t) paddle->x, (int32_t) paddle->y, (int32_t) paddle->w, (int32_t) paddle->h, 
                (int32_t) b->x, (int32_t) b->y, (int32_t) b->w, (int32_t) b->h)) {
    uint32_t SIZE = 16;                  
    double rel = (paddle->x + (paddle->w / 2)) - (b->x + (SIZE / 2));
    double norm = rel / (paddle->w / 2);
    double bounce = norm * (5 * PI / 12);
    
    b->dx = (float) (BALL_SPEED * -sin(bounce));
    b->dy = (float) (-BALL_SPEED * cos(bounce));
    return;
  }
}

/*
 *
 */
static void powerup_hit_paddle(Entity* p) {
  if (collision((int32_t) paddle->x, (int32_t) paddle->y, (int32_t) paddle->w, (int32_t) paddle->h, 
                (int32_t) p->x, (int32_t) p->y, (int32_t) p->w, (int32_t) p->h)) {
    
    powerup_activate(p);
  }
}