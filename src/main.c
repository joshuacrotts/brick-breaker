/*
 * Music and sfx are courtesy of BreakIt! Java game by ndering.
 *
 * https://github.com/ndering/Break-It
 */

#include "../include/main.h"

#define S_WIDTH  590
#define S_HEIGHT 960
#define L_WIDTH  0
#define L_HEIGHT 0

static void init_scene( void );
static void draw( void );
static void update( void );
static void check_pregame( void );
static void check_paused( void );
static void check_transition( void );
static void cleanup_stage( void );
static void start_game( void );

static void update_entities( void );
static void update_debris( void );
static void update_trails( void );

static void draw_entities( void );
static void draw_debris( void );
static void draw_trails( void );

// Barebones game. This is the minimum amount of code
// necessary to run a window.
int
main( int argc, char *argv[] ) {
  Stds_InitGame( "Brick Breaker in C", S_WIDTH, S_HEIGHT, L_WIDTH, L_HEIGHT );
  Stds_InitAppStructures();

  init_scene();
  init_menu();

  Stds_GameLoop();

  atexit( cleanup_stage );
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
init_scene( void ) {
  app.delegate.update = update;
  app.delegate.draw   = draw;
  app.game_state      = PREGAME;

  memset( &stage, 0, sizeof( stage_t ) );
  stage.level_tail  = &stage.level_head;
  stage.debris_tail = &stage.debris_head;
  stage.state       = MENU;
  stage.level_id    = 1;

  level_t *level         = add_level( stage.level_id );
  stage.level_tail->next = level;
  stage.level_tail       = level;
  currentLevel           = stage.level_tail;
  background             = Stds_AddBackground( "res/img/background/space-1.png" );

  init_paddle();
  init_HUD();

  ps = Stds_CreateParticleSystem( 1024 );
}

/*
 *
 */
static void
update( void ) {
  check_pregame();
  check_transition();
  check_paused();
  check_transition();

  if ( app.game_state == PAUSED ) {
    return;
  }

  Stds_BackgroundUpdate( background );
  update_HUD();

  if ( stage.state == GAME ) {
    Stds_ParticleSystemUpdate( ps );
    update_entities();
    update_trails();
    update_debris();
    level_update();
  }

  if ( app.game_state != TRANSITION ) {
    paddle_update();
  }
}

/*
 *
 */
static void
draw( void ) {
  Stds_BackgroundDraw( background );
  if ( stage.state == GAME ) {
    draw_entities();
    draw_trails();
    draw_debris();
    level_draw();
    paddle_draw();
    Stds_ParticleSystemDraw( ps );

  }

  if ( app.game_state == TRANSITION ) {
    transition_draw();
  }

  draw_HUD();

  if ( app.game_state == PAUSED ) {
    draw_paused();
  }
}

/*
 *
 */
static void
update_entities( void ) {
  struct entity_t *e;
  struct entity_t *prev;
  prev = &currentLevel->entity_head;

  for ( e = currentLevel->entity_head.next; e != NULL; e = e->next ) {
    if ( e->update ) {
      e->update( e );
    }

    if ( e->flags & STDS_DEATH_MASK ) {
      if ( e == currentLevel->entity_tail ) {
        currentLevel->entity_tail = prev;
      }

      prev->next = e->next;
      free( e );
      e = prev;
    }
    prev = e;
  }
}

/*
 *
 */
static void
update_debris( void ) {
  debris_t *d;
  debris_t *prev;

  prev = &stage.debris_head;

  for ( d = stage.debris_head.next; d != NULL; d = d->next ) {
    debris_update( d );

    if ( d->flags & STDS_DEATH_MASK ) {
      if ( d == stage.debris_tail ) {
        stage.debris_tail = prev;
      }

      prev->next = d->next;
      debris_die( d );
      d = prev;
    }
    prev = d;
  }
}

/*
 *
 */
static void
update_trails( void ) {
  struct trail_t *t;
  struct trail_t *prev;

  prev = &app.trail_head;

  for ( t = app.trail_head.next; t != NULL; t = t->next ) {
    Stds_TrailUpdate( t );

    if ( t->flags & STDS_DEATH_MASK ) {
      if ( t == app.trail_tail ) {
        app.trail_tail = prev;
      }

      prev->next = t->next;
      free( t );
      t = prev;
    }
    prev = t;
  }
}

/*
 *
 */
static void
draw_entities( void ) {
  struct entity_t *e;

  for ( e = currentLevel->entity_head.next; e != NULL; e = e->next ) {
    if ( e->draw ) {
      e->draw( e );
    }
  }
}

/*
 *
 */
static void
draw_debris( void ) {
  debris_t *d;

  for ( d = stage.debris_head.next; d != NULL; d = d->next ) {
    debris_draw( d );
  }
}

/*
 *
 */
static void
draw_trails( void ) {
  struct trail_t *t;

  for ( t = app.trail_head.next; t != NULL; t = t->next ) {
    Stds_TrailDraw( t );
  }
}

/*
 *
 */
static void
check_paused( void ) {
  if ( app.keyboard[SDL_SCANCODE_P] && stage.state == GAME ) {
    Stds_PlaySounds( SND_PAUSE, CH_ANY );
    app.game_state               = app.game_state == PAUSED ? RUNNING : PAUSED;
    app.keyboard[SDL_SCANCODE_P] = 0;
  }

  if ( app.game_state == PAUSED ) {
    Mix_PauseMusic();
  } else {
    Mix_ResumeMusic();
  }
}

/*
 *
 */
static void
check_transition( void ) {
  if ( app.game_state == TRANSITION ) {
    transition_update();
  }
}

/*
 *
 */
static void
check_pregame( void ) {
  // Initially, we just have the player moving the paddle around,
  // and no ball or powerups.
  if ( app.keyboard[SDL_SCANCODE_SPACE] && app.game_state == PREGAME ) {
    app.keyboard[SDL_SCANCODE_SPACE] = 0;
    struct entity_t *b               = add_ball(
        Stds_RandomFloat( app.SCREEN_WIDTH / 3, app.SCREEN_WIDTH / 2 + app.SCREEN_WIDTH / 4 ),
        app.SCREEN_HEIGHT / 2, 0 );
    currentLevel->ball_tail->next = b;
    currentLevel->ball_tail       = b;
    app.game_state                = RUNNING;
  }
}

/*
 *
 */
static void
cleanup_stage( void ) {
  level_t *           l;
  struct animation_t *a;
  struct entity_t *   en;
  struct entity_t *   ball;
  struct entity_t *   brick;

  // Iterate through the levels and free all allocated memory
  // to each level.
  for ( l = stage.level_head.next; l != NULL; l = l->next ) {
    while ( l->ball_head.next ) {
      ball              = l->ball_head.next;
      l->ball_head.next = ball->next;
      free( ball );
    }

    while ( l->brick_head.next ) {
      brick              = l->brick_head.next;
      l->brick_head.next = brick->next;
      free( brick );
    }

    while ( l->entity_head.next ) {
      en                  = l->entity_head.next;
      l->entity_head.next = en->next;
      free( en );
    }
  }

  while ( stage.animation_head.next ) {
    a                         = stage.animation_head.next;
    stage.animation_head.next = a->next;
    free( a );
  }

  free( currentLevel );
  paddle_die();
  Stds_BackgroundDie( background );
}