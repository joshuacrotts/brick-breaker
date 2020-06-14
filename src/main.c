#include "main.h"

static void init_scene(void);
static void draw(void);
static void tick(void);
static void cleanup_stage(void);

static void create_emitter(int32_t, int32_t, uint32_t, uint32_t);
static void update_emitters(void);
static void update_entities(void);
static void update_debris(void);

static void draw_emitters(void);
static void draw_entities(void);
static void draw_debris(void);

// Barebones game. This is the minimum amount of code
// necessary to run a window.
int main(int argc, char* argv[]) {
  initGame("Standards C Library", SCREEN_WIDTH, SCREEN_HEIGHT);
  init_scene();
  loop();

  atexit(cleanup_stage);
  return 0;
}

/*
 * Initializes the delegation structure to use the
 * tick and draw methods for rendering and updating
 * the game. These methods must be defined because the
 * delegation structure uses them in the loop function.
 *
 * Sprites and structs are also initalized here.
 */
static void init_scene(void) {
  app.delegate.tick = tick;
  app.delegate.draw = draw;

  memset(&stage, 0, sizeof(Stage));
  app.textureTail = &app.textureHead;
  stage.levelTail = &stage.levelHead;
  stage.debrisTail = &stage.debrisHead;

  Level* level = add_level();
  stage.levelTail->next = level;
  stage.levelTail = level;
  currentLevel = stage.levelTail;

  init_paddle();
  init_background();
}

/*
 *
 */
static void tick(void) {
  background_update();
  update_emitters();
  update_entities();
  update_debris();
  level_update();
  paddle_update();

  if (app.mouse.button[SDL_BUTTON_LEFT]) {
    Entity* b = add_ball(app.mouse.x, app.mouse.y, 0);
    Entity* p = add_powerup(app.mouse.x, app.mouse.y, 0, GOLD_COIN);

    currentLevel->ballTail->next = b;
    currentLevel->ballTail = b;

    currentLevel->powerupTail->next = p;
    currentLevel->powerupTail = p;
    app.mouse.button[SDL_BUTTON_LEFT] = 0;
  }
}

/*
 *
 */
static void draw(void) {
  background_draw();
  draw_emitters();
  draw_entities();
  draw_debris();
  level_draw();
  paddle_draw();
}

/*
 *
 */
static void update_emitters(void) {
  Emitter* em;
  Emitter* prev;

  prev = &currentLevel->emitterHead;

  for (em = currentLevel->emitterHead.next; em != NULL; em = em->next) {
    emitter_update(em);

    if (em->flags & DEATH_MASK) {
      if (em == currentLevel->emitterTail) {
        currentLevel->emitterTail = prev;
      }

      prev->next = em->next;
      free(em);
      em = prev;
    }
    prev = em;
  }
}

/*
 *
 */
static void update_entities(void) {
  Entity* e;
  Entity* prev;

  prev = &currentLevel->entityHead;

  for (e = currentLevel->entityHead.next; e != NULL; e = e->next) {
    if (e->idFlags & ID_PARTICLE_MASK) {
      particle_update(e);
    } 
    else if (e->tick) {
      e->tick(e);
    }

    if (e->flags & DEATH_MASK) {
      if (e == currentLevel->entityTail) {
          currentLevel->entityTail = prev;
      }

      prev->next = e->next;
      free(e);
      e = prev;
    }
    prev = e;
  }
}

/*
 *
 */
static void update_debris(void) {
  Debris* d;
  Debris* prev;

  prev = &stage.debrisHead;

  for (d = stage.debrisHead.next; d != NULL; d = d->next) {
    debris_update(d);
    
    if (d->flags & DEATH_MASK) {
      if (d == stage.debrisTail) {
        stage.debrisTail = prev;
      }

      prev->next = d->next;
      debris_die(d);
      d = prev;
    }
    prev = d;
  }
}

/*
 *
 */
static void draw_emitters(void) {
  Emitter* em;

  for (em = currentLevel->emitterHead.next; em != NULL; em = em->next) {
    emitter_draw(em);
  }
}

/*
 *
 */
static void draw_entities(void) {
  Entity* e;

  for (e = currentLevel->entityHead.next; e != NULL; e = e->next) {
    if (e->idFlags & ID_PARTICLE_MASK) {
      particle_draw(e);
    } 
    else if (e->draw) {
      e->draw(e);
    }
  }
}

/*
 *
 */
static void draw_debris(void) {
  Debris* d;

  for (d = stage.debrisHead.next; d != NULL; d = d->next) {
    debris_draw(d);
  }
}

/*
 *
 */
static void create_emitter(int32_t x, int32_t y, uint32_t maxParticles, uint32_t flags) {
  Emitter* em;

  em = add_emitter(x, y, maxParticles, flags);

  currentLevel->emitterTail->next = em;
  currentLevel->emitterTail = em;
}

/*
 *
 */
static void cleanup_stage(void) {
  Level* l;
  Animation* a;
  Emitter* em;
  Entity* en;
  Entity* ball;
  Entity* brick;

  // Iterate through the levels and free all allocated memory
  // to each level.
  for (l = stage.levelHead.next; l != NULL; l = l->next) {
    while (l->ballHead.next) {
      ball = l->ballHead.next;
      l->ballHead.next = ball->next;
      free(ball);
    }

    while (l->brickHead.next) {
      brick = l->brickHead.next;
      l->brickHead.next = brick->next;
      free(brick);
    }

    while (l->emitterHead.next) {
      em = l->emitterHead.next;
      l->emitterHead.next = em->next;
      free(em);
    }

    while (l->entityHead.next) {
      en = l->entityHead.next;
      l->entityHead.next = en->next;
      free(en);
    }
  }

  while (stage.animationHead.next) {
    a = stage.animationHead.next;
    stage.animationHead.next = a->next;
    free(a);
  }

  free(currentLevel);
  paddle_die();
  background_die();
}