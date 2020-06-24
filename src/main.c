/*
 * Music and sfx are courtesy of BreakIt! Java game by ndering.
 *
 * https://github.com/ndering/Break-It
 */

#include "../include/main.h"

static void init_scene( void );
static void draw( void );
static void tick( void );
static void check_pregame( void );
static void check_paused( void );
static void check_transition( void );
static void cleanup_stage( void );
static void start_game( void );

static void create_emitter( int32_t, int32_t, uint32_t, uint32_t );
static void update_emitters( void );
static void update_entities( void );
static void update_debris( void );
static void update_trails( void );

static void draw_emitters( void );
static void draw_entities( void );
static void draw_debris( void );
static void draw_trails( void );

// Barebones game. This is the minimum amount of code
// necessary to run a window.
int
main( int argc, char *argv[] ) {
  init_game( "Brick Breaker in C", SCREEN_WIDTH, SCREEN_HEIGHT );
  init_app_structures();
  init_scene();
  init_menu();
  loop();

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
  app.delegate.tick = tick;
  app.delegate.draw = draw;
  app.game_state    = PREGAME;

  memset( &stage, 0, sizeof( stage_t ) );
  stage.levelTail   = &stage.levelHead;
  stage.debris_tail = &stage.debris_head;
  stage.state       = MENU;
  stage.level_id    = 1;

  level_t *level        = add_level( stage.level_id );
  stage.levelTail->next = level;
  stage.levelTail       = level;
  currentLevel          = stage.levelTail;
  background            = init_background( "res/img/background/space-1.png" );

  init_paddle();
  init_HUD();
}

/*
 *
 */
static void
tick( void ) {
  check_pregame();
  check_transition();
  check_paused();
  check_transition();

  if ( app.game_state == PAUSED ) {
    return;
  }

  background_update( background );
  update_HUD();

  if ( stage.state == GAME ) {
    update_emitters();
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
  background_draw( background );
  if ( stage.state == GAME ) {
    draw_emitters();
    draw_entities();
    draw_trails();
    draw_debris();
    level_draw();
    paddle_draw();
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
update_emitters( void ) {
  emitter_t *em;
  emitter_t *prev;

  prev = &currentLevel->emitter_head;

  for ( em = currentLevel->emitter_head.next; em != NULL; em = em->next ) {
    emitter_update( em );

    if ( em->flags & DEATH_MASK ) {
      if ( em == currentLevel->emitter_tail ) {
        currentLevel->emitter_tail = prev;
      }

      prev->next = em->next;
      free( em );
      em = prev;
    }
    prev = em;
  }
}

/*
 *
 */
static void
update_entities( void ) {
  entity_t *e;
  entity_t *prev;
  prev = &currentLevel->entity_head;

  for ( e = currentLevel->entity_head.next; e != NULL; e = e->next ) {
    if ( e->id_flags & ID_PARTICLE_MASK ) {
      particle_update( e );
    } else if ( e->tick ) {
      e->tick( e );
    }

    if ( e->flags & DEATH_MASK ) {
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

    if ( d->flags & DEATH_MASK ) {
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
  trail_t *t;
  trail_t *prev;

  prev = &app.trail_head;

  for ( t = app.trail_head.next; t != NULL; t = t->next ) {
    trail_update( t );

    if ( t->flags & DEATH_MASK ) {
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
draw_emitters( void ) {
  emitter_t *em;

  for ( em = currentLevel->emitter_head.next; em != NULL; em = em->next ) {
    emitter_draw( em );
  }
}

/*
 *
 */
static void
draw_entities( void ) {
  entity_t *e;

  for ( e = currentLevel->entity_head.next; e != NULL; e = e->next ) {
    if ( e->id_flags & ID_PARTICLE_MASK ) {
      particle_draw( e );
    } else if ( e->draw ) {
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
  trail_t *t;

  for ( t = app.trail_head.next; t != NULL; t = t->next ) {
    trail_draw( t );
  }
}

/*
 *
 */
static void
create_emitter( int32_t x, int32_t y, uint32_t maxParticles, uint32_t flags ) {
  emitter_t *em;

  em = add_emitter( x, y, maxParticles, flags );

  currentLevel->emitter_tail->next = em;
  currentLevel->emitter_tail       = em;
}

/*
 *
 */
static void
check_paused( void ) {
  if ( app.keyboard[SDL_SCANCODE_P] && stage.state == GAME ) {
    play_sound( SND_PAUSE, CH_ANY );
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
    entity_t *b = add_ball( random_float( SCREEN_WIDTH / 3, SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4 ),
                            SCREEN_HEIGHT / 2, 0 );
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
  level_t *    l;
  animation_t *a;
  emitter_t *  em;
  entity_t *   en;
  entity_t *   ball;
  entity_t *   brick;

  // Iterate through the levels and free all allocated memory
  // to each level.
  for ( l = stage.levelHead.next; l != NULL; l = l->next ) {
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

    while ( l->emitter_head.next ) {
      em                   = l->emitter_head.next;
      l->emitter_head.next = em->next;
      free( em );
    }

    while ( l->entity_head.next ) {
      en                  = l->entity_head.next;
      l->entity_head.next = en->next;
      free( en );
    }
  }

  while ( stage.animationHead.next ) {
    a                        = stage.animationHead.next;
    stage.animationHead.next = a->next;
    free( a );
  }

  free( currentLevel );
  paddle_die();
  background_die( background );
}