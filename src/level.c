#include "../include/level.h"

#define MAXC            16
#define CHAR_OFFSET     48
#define BRICK_ROW_COUNT 6
#define BRICK_COL_COUNT 6
#define BRICK_WIDTH     92
#define BRICK_HEIGHT    32

static Entity* spawn_powerup(Entity*);

static void update_balls(void);
static void update_powerups(void);
static void update_bricks(void);

static void draw_balls(void);
static void draw_powerups(void);
static void draw_bricks(void);

static void ball_hit_paddle(Entity*);
static void ball_hit_brick(Entity*);
static void powerup_hit_paddle(Entity*);

Level* add_level(const char* levelData) {
    Level* level;
    FILE* fptr;

    fptr = fopen(levelData, "r");

    if (fptr == NULL) {
      SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not read from file! %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
    }

    // Create the buffer for the level data 
    // where each line corresponds to one row
    // of bricks.
    char buffer[MAXC];

    level = malloc(sizeof(Level));
    memset(level, 0, sizeof(Level));

    level->ballTail = &level->ballHead;
    level->emitterTail = &level->emitterHead;
    level->entityTail = &level->entityHead;
    level->ballTail = &level->ballHead;
    level->brickTail = &level->brickHead;
    level->powerupTail = &level->powerupHead;

    uint8_t brick_data = 1;

    for (int y = 120; y < 120 + (BRICK_HEIGHT * BRICK_COL_COUNT); y += 32) {
      fgets(buffer, MAXC, fptr);
      for (int x = 20, bi = 0; x <= SCREEN_WIDTH - 80; x += 92, bi++) {
        Entity* b;
        int c = (buffer[bi] - '\0') - CHAR_OFFSET;

        // If the char is invalid, then quit iteration.
        if (c < 0) {
          break;
        }

        // Depending on the char value, add its corresponding
        // brick ID.
        switch (c) {
          case 0: break;
          case 1: b = add_brick(x, y, 0, RED);
                  break;
          case 2: b = add_brick(x, y, 0, BLUE);
                  break;
          case 3: b = add_brick(x, y, 0, LIGHT_GREEN);
                  break;
          case 4: b = add_brick(x, y, 0, YELLOW);
                  break;
          case 5: b = add_brick(x, y, 0, ORANGE);
                  break;
          case 6: b = add_brick(x, y, 0, PURPLE);
                  break;                  
          case 7: b = add_brick(x, y, 0, LIGHT_BLUE);
                break;
          case 8: b = add_brick(x, y, 0, DARK_GREEN);
                  break;
          case 9: b = add_brick(x, y, 0, BROWN);
                  break;                  
          default:
                  break;
        }
            
        level->brickTail->next = b;
        level->brickTail = b;
      }
    }
    
    fclose(fptr);
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
          if (brick->life > 0) {
            playSound(SND_BRICK_SHATTER, CH_BRICK);
          } else {
            Entity* p;
            p = spawn_powerup(brick);

            if (p != NULL) {
              currentLevel->powerupTail->next = p;
              currentLevel->powerupTail = p;
            }

            playSound(SND_BRICK_BREAK, CH_BRICK);
            stage.score += 100;
          }
          
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
                (int32_t) p->x, (int32_t) p->y, (int32_t) p->w, (int32_t) p->h) && p->flags & POWERUP_INACTIVE) {

    if (p->identifier == LARGE_PADDLE) {
      powerup_large_activate(p);
    } else if (p->identifier == MULTI_BALL) {
      powerup_multi_activate(p);
    } else if (p->identifier == GOLD_COIN) {
      powerup_coin_activate(p);
    } else if (p->identifier == EXTRA_LIFE) {
      powerup_life_activate(p);
    }
  }
}

/*
 *
 */
static Entity* spawn_powerup(Entity* parent) {
  Entity* p;

  float prob = randomFloat(1.0f, 1000.0f);

  if (prob < 50.0f) {
    p = add_powerup(parent->x, parent->y, 0, EXTRA_LIFE);
  } else if (prob < 100.0f) {
    p = add_powerup(parent->x, parent->y, 0, LARGE_PADDLE);
  } else if (prob < 150.0f) {
    p = add_powerup(parent->x, parent->y, 0, MULTI_BALL);
  } else if (prob < 500.0f) {
    p = add_powerup(parent->x, parent->y, 0, GOLD_COIN);
  } else {
    p = NULL;
  }

  return p;
}