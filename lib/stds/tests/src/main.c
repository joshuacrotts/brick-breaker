#include "../include/main.h"
#include "../include/player.h"

#define S_WIDTH  700
#define S_HEIGHT 700
#define L_WIDTH  3000
#define L_HEIGHT S_HEIGHT

static background_t *bg;

static void init_scene( void );
static void cleanup_stage( void );
static void draw( void );
static void tick( void );
static void check_enemy_collision( void );
static void add_particles( int32_t, int32_t, size_t );

static void update_trails( void );
static void update_enemies( void );
static void update_parallax_backgrounds( void );

static void draw_trails( void );
static void draw_enemies( void );
static void draw_parallax_backgrounds( void );

static fade_color_t       f;
static SDL_Rect           screen_edge;
static particle_system_t *ps;

/*
 * Barebones game. This is the minimum amount of code
 * necessary to run a window. To redefine the level/screen
 * dimensions, just #undef SCREEN_WIDTH/HEIGHT or LEVEL_WIDTH/HEIGHT
 * and redefine them immediately below it.
 */
int
main( int argc, char *argv[] ) {

  init_game( "Trail, Parallax Test, and Button Test", S_WIDTH, S_HEIGHT, L_WIDTH, L_HEIGHT );
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

  for ( int i = 0, x = 0; i < 30; i++, x += 48 ) {
    entity_t *e;
    e = add_enemy( x, app.LEVEL_HEIGHT - 20 );

    stage.enemy_tail->next = e;
    stage.enemy_tail       = e;
  }

  uint8_t parallax_frames = 11;

  float parallax_scroll[11] = {0.10f, 0.15f, 0.20f, 0.25f, 0.30f, 0.35f,
                               0.40f, 0.45f, 0.50f, 0.55f, 0.60f};
  init_parallax_background( "tests/res/img/background_4/layer_0", parallax_frames, 1.0f,
                            parallax_scroll, false );

  SDL_Color c1 = {0xff, 0xff, 0, 0xff};
  SDL_Color c2 = {0, 0, 0xff, 0xff};

  f.c1    = c1;
  f.c2    = c2;
  f.time  = 0.0f;
  f.alpha = 0.01f;

  ps = create_particle_system( 512 );
}

/*
 *
 */
static void
tick( void ) {
  if ( app.mouse.button[SDL_BUTTON_LEFT] ) {
    add_particles( app.mouse.x, app.mouse.y, 32 );
  }

  update_camera( player );
  particle_system_update( ps );
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
  particle_system_draw( ps );
  SDL_Color c = combine_fade_color( &f );
  draw_rect_stroke( 0, 0, app.SCREEN_WIDTH, app.SCREEN_HEIGHT, 8, &c, 0xff );
  draw_trails();
  draw_enemies();
  player_draw();
}

/**
 *
 */
static void
draw_trails( void ) {
  trail_t *t;

  for ( t = app.trail_head.next; t != NULL; t = t->next ) {
    trail_draw( t );
  }
}

/**
 *
 */
static void
draw_parallax_backgrounds( void ) {
  parallax_background_t *p;

  for ( p = app.parallax_head.next; p != NULL; p = p->next ) {
    parallax_background_draw( p );
  }
}

/**
 *
 */
static void
draw_enemies( void ) {
  entity_t *e;

  for ( e = stage.enemy_head.next; e != NULL; e = e->next ) {
    enemy_draw( e );
  }
}

/**
 *
 */
static void
cleanup_stage( void ) {
  free( player );
}

/**
 *
 */
static void
add_particles( int32_t x, int32_t y, size_t n ) {
  for ( int i = 0; i < n; i++ ) {
    particle_t p;
    p.x               = x;
    p.y               = y;
    p.life            = random_int( 100, 300 );
    p.dx              = random_float( -5, 5 );
    p.dy              = random_float( -5, 5 );
    p.w               = random_int( 1, 5 );
    p.h               = p.w;
    p.particle_update = red_particle_update;
    p.particle_draw   = red_particle_draw;
    p.color.r         = 0xff;
    p.color.a         = 0xff;
    p.color.g         = 0;
    p.color.b         = 0;
    insert_particle( ps, &p );
  }
}