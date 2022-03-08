/*
 * Music and sfx are courtesy of BreakIt! Java game by ndering.
 *
 * https://github.com/ndering/Break-It
 */

#include "../include/main.h"

#define S_WIDTH 590
#define S_HEIGHT 960
#define L_WIDTH 0
#define L_HEIGHT 0

static void init_scene(void);
static void draw(void);
static void tick(void);
static void check_pregame(void);
static void check_paused(void);
static void check_transition(void);
static void cleanup_stage(void);
static void start_game(void);

static void update_entities(void);
static void update_debris(void);
static void update_trails(void);

static void draw_entities(void);
static void draw_debris(void);
static void draw_trails(void);

particle_system_t *ps;
stage_t          stage;
entity_t *       paddle;
background_t *   background;
level_t * currentLevel;
app_t app;

// Barebones game. This is the minimum amount of code
// necessary to run a window.
int main(int argc, char *argv[])
{
  init_game("Brick Breaker in C", S_WIDTH, S_HEIGHT, L_WIDTH, L_HEIGHT);
  init_app_structures();
  init_scene();
  init_menu();
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
static void
init_scene(void)
{
  app.delegate.tick = tick;
  app.delegate.draw = draw;
  app.game_state = PREGAME;

  memset(&stage, 0, sizeof(stage_t));
  stage.level_tail = &stage.level_head;
  stage.debris_tail = &stage.debris_head;
  stage.state = MENU;
  stage.level_id = 1;

  level_t *level = add_level(stage.level_id);
  stage.level_tail->next = level;
  stage.level_tail = level;
  currentLevel = stage.level_tail;
  background = init_background("res/img/background/space-1.png");

  init_paddle();
  init_HUD();

  ps = create_particle_system(51222);
}

/*
 *
 */
static void
tick(void)
{
  check_pregame();
  check_transition();
  check_paused();
  check_transition();

  if (app.game_state == PAUSED)
  {
    return;
  }

  background_update(background);
  update_HUD();

  if (stage.state == GAME)
  {
    particle_system_update(ps);
    update_entities();
    update_trails();
    update_debris();
    level_update();
  }

  if (app.game_state != TRANSITION)
  {
    paddle_update();
  }
}

/*
 *
 */
static void
draw(void)
{
  background_draw(background);
  if (stage.state == GAME)
  {
    particle_system_draw(ps);
    draw_entities();
    draw_trails();
    draw_debris();
    level_draw();
    paddle_draw();
  }

  if (app.game_state == TRANSITION)
  {
    transition_draw();
  }
  draw_HUD();

  if (app.game_state == PAUSED)
  {
    draw_paused();
  }
}

/*
 *
 */
static void
update_entities(void)
{
  entity_t *e;
  entity_t *prev;
  prev = &currentLevel->entity_head;

  for (e = currentLevel->entity_head.next; e != NULL; e = e->next)
  {
    if (e->tick)
    {
      e->tick(e);
    }

    if (e->flags & DEATH_MASK)
    {
      if (e == currentLevel->entity_tail)
      {
        currentLevel->entity_tail = prev;
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
static void
update_debris(void)
{
  debris_t *d;
  debris_t *prev;

  prev = &stage.debris_head;

  for (d = stage.debris_head.next; d != NULL; d = d->next)
  {
    debris_update(d);

    if (d->flags & DEATH_MASK)
    {
      if (d == stage.debris_tail)
      {
        stage.debris_tail = prev;
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
static void
update_trails(void)
{
  trail_t *t;
  trail_t *prev;

  prev = &app.trail_head;

  for (t = app.trail_head.next; t != NULL; t = t->next)
  {
    trail_update(t);

    if (t->flags & DEATH_MASK)
    {
      if (t == app.trail_tail)
      {
        app.trail_tail = prev;
      }

      prev->next = t->next;
      free(t);
      t = prev;
    }
    prev = t;
  }
}

/*
 *
 */
static void
draw_entities(void)
{
  entity_t *e;

  for (e = currentLevel->entity_head.next; e != NULL; e = e->next)
  {
    if (e->draw)
    {
      e->draw(e);
    }
  }
}

/*
 *
 */
static void
draw_debris(void)
{
  debris_t *d;

  for (d = stage.debris_head.next; d != NULL; d = d->next)
  {
    debris_draw(d);
  }
}

/*
 *
 */
static void
draw_trails(void)
{
  trail_t *t;

  for (t = app.trail_head.next; t != NULL; t = t->next)
  {
    trail_draw(t);
  }
}

/*
 *
 */
static void
check_paused(void)
{
  if (app.keyboard[SDL_SCANCODE_P] && stage.state == GAME)
  {
    play_sound(SND_PAUSE, CH_ANY);
    app.game_state = app.game_state == PAUSED ? RUNNING : PAUSED;
    app.keyboard[SDL_SCANCODE_P] = 0;
  }

  if (app.game_state == PAUSED)
  {
    Mix_PauseMusic();
  }
  else
  {
    Mix_ResumeMusic();
  }
}

/*
 *
 */
static void
check_transition(void)
{
  if (app.game_state == TRANSITION)
  {
    transition_update();
  }
}

/*
 *
 */
static void
check_pregame(void)
{
  // Initially, we just have the player moving the paddle around,
  // and no ball or powerups.
  if (app.keyboard[SDL_SCANCODE_SPACE] && app.game_state == PREGAME)
  {
    app.keyboard[SDL_SCANCODE_SPACE] = 0;
    entity_t *b =
        add_ball(random_float(app.SCREEN_WIDTH / 3, app.SCREEN_WIDTH / 2 + app.SCREEN_WIDTH / 4),
                 app.SCREEN_HEIGHT / 2, 0);
    currentLevel->ball_tail->next = b;
    currentLevel->ball_tail = b;
    app.game_state = RUNNING;
  }
}

/*
 *
 */
static void
cleanup_stage(void)
{
  level_t *l;
  animation_t *a;
  entity_t *en;
  entity_t *ball;
  entity_t *brick;

  // Iterate through the levels and free all allocated memory
  // to each level.
  for (l = stage.level_head.next; l != NULL; l = l->next)
  {
    while (l->ball_head.next)
    {
      ball = l->ball_head.next;
      l->ball_head.next = ball->next;
      free(ball);
    }

    while (l->brick_head.next)
    {
      brick = l->brick_head.next;
      l->brick_head.next = brick->next;
      free(brick);
    }

    while (l->entity_head.next)
    {
      en = l->entity_head.next;
      l->entity_head.next = en->next;
      free(en);
    }
  }

  while (stage.animation_head.next)
  {
    a = stage.animation_head.next;
    stage.animation_head.next = a->next;
    free(a);
  }

  free(currentLevel);
  paddle_die();
  background_die(background);
  free(ps->particles);
  free(ps);
}
