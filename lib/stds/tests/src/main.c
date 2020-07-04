#include "../include/main.h"
#include "../include/player.h"

static background_t *bg;

static void init_scene( void );
static void cleanup_stage( void );
static void draw( void );
static void tick( void );
static void check_enemy_collision( void );

static void update_trails( void );
static void update_enemies( void );
static void update_parallax_backgrounds( void );

static void draw_trails( void );
static void draw_enemies( void );
static void draw_parallax_backgrounds( void );

static fade_color_t f;
static SDL_Rect     screen_edge;

// Barebones game. This is the minimum amount of code
// necessary to run a window.
int
main( int argc, char *argv[] ) {
  init_game( "Trail, Parallax Test, and Button Test", SCREEN_WIDTH, SCREEN_HEIGHT );
  init_app_structures();
  init_scene();
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
  stage.enemy_tail  = &stage.enemy_head;

  init_player();

  for ( int i = 0, x = 0; i < 30; i++, x += 64 ) {
    entity_t *e;
    e = add_enemy( x, 620 );

    stage.enemy_tail->next = e;
    stage.enemy_tail       = e;
  }

  uint8_t parallax_frames = 5;

  float parallax_scroll[5] = {0.10f, 0.15f, 0.20f, 0.25f, 0.30f};
  init_parallax_background( "tests/res/img/background_3/Layer", parallax_frames, 4.0f,
                            parallax_scroll, true );
  // bg = init_background( "tests/res/img/background_0.png" );

  SDL_Color c1;
  c1.r = 0xff;
  c1.g = 0xff;
  c1.b = 0;

  SDL_Color c2;
  c1.r = 0;
  c1.g = 0;
  c1.b = 0xff;

  f.c1    = c1;
  f.c2    = c2;
  f.time  = 0.0f;
  f.alpha = 0.01f;
}

/*
 *
 */
static void
tick( void ) {
  update_camera( player );
  update_parallax_backgrounds();
  update_trails();
  update_enemies();
  player_update();
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
update_parallax_backgrounds( void ) {
  parallax_background_t *p;
  for ( p = app.parallax_head.next; p != NULL; p = p->next ) {
    parallax_background_update( p );
  }
}

/*
 *
 */
static void
update_enemies( void ) {
  entity_t *e;

  for ( e = stage.enemy_head.next; e != NULL; e = e->next ) {
    enum CollisionSide s = check_aabb_collision( player, e );

    if ( s == SIDE_TOP || s == SIDE_BOTTOM ) {
      player->dy = 0;
    }

    if ( s == SIDE_LEFT || s == SIDE_RIGHT ) {
      player->dx = 0;
    }
  }
}

/*
 *
 */
static void
draw( void ) {
  draw_parallax_backgrounds();
  SDL_Color c = combine_fade_color( &f );
  draw_rect_stroke( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 8, c.r, c.g, c.b, 0xff );
  draw_trails();
  draw_enemies();
  player_draw();
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
draw_parallax_backgrounds( void ) {
  parallax_background_t *p;

  for ( p = app.parallax_head.next; p != NULL; p = p->next ) {
    parallax_background_draw( p );
  }
}

/*
 *
 */
static void
draw_enemies( void ) {
  entity_t *e;

  for ( e = stage.enemy_head.next; e != NULL; e = e->next ) {
    enemy_draw( e );
  }
}

/*
 *
 */
static void
cleanup_stage( void ) {
  free( player );
}