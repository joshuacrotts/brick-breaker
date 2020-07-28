#include "../include/ball.h"

#define BALL_DEATH_PARTICLES 20

static void check_bounds( entity_t * );
static void spawn_ball_particles( entity_t * );

entity_t *
add_ball( f32 x, f32 y, uint32_t flags ) {
  entity_t *b;
  b = malloc( sizeof( entity_t ) );
  memset( b, 0, sizeof( entity_t ) );

  b->x          = x;
  b->y          = y;
  b->texture[0] = load_texture( "res/img/ball_sprite_1.png" );
  SDL_QueryTexture( b->texture[0], NULL, NULL, &b->w, &b->h );

  // Continuously generate a speed that is reasonable.
  do {
    b->dx = random_f32( -10.0f, 10.0f );
  } while ( b->dx < 7.0f && b->dx > -7.0f );

  do {
    b->dy = random_f32( -10.0f, 10.0f );
  } while ( b->dy < 7.0f && b->dy > -7.0f );

  b->id_flags |= ID_BALL_MASK;
  b->flags |= flags;
  currentLevel->ball_count++;
  return b;
}

void
ball_update( entity_t *b ) {
  b->x += b->dx;
  b->y += b->dy;
  //add_trail( b, 4, 60, false, SDL_FLIP_NONE );
  check_bounds( b );
}

void
ball_draw( entity_t *b ) {
  blit_texture( b->texture[0], b->x, b->y, false, false );
}

void
ball_die( entity_t *b ) {
  free( b );
}

/*
 *
 */
static void
check_bounds( entity_t *b ) {
  if ( b->x < 0 ) {
    b->x  = 0;
    b->dx = -b->dx;
  } else if ( b->x + b->w > app.SCREEN_WIDTH ) {
    b->x -= b->w;
    b->dx = -b->dx;
  } else if ( b->y < 0 ) {
    b->y  = 0;
    b->dy = -b->dy;
  } else if ( b->y + b->h > app.SCREEN_HEIGHT ) {
    currentLevel->ball_count--;
    spawn_ball_particles( b );
    b->flags |= DEATH_MASK;
  }
}

/*
 *
 */
static void
spawn_ball_particles( entity_t *b ) {
  entity_t *p;

  for ( int i = 0; i < BALL_DEATH_PARTICLES; i++ ) {
    particle_t p;
    p.x             = b->x + b->w / 2;
    p.y             = b->y + b->h / 2;
    p.dx            = random_f32( -5, 5 );
    p.dy            = random_f32( -7, 5 );
    p.delta_accel_x = p.delta_accel_y = 0;
    p.w = p.h = 3;
    p.color.r = 0xff;
    p.color.g = p.color.b = 0;
    p.color.a = 0xff;
    p.delta_alpha = -3.0f;
    p.id_flags |= ID_P_SQUARE_MASK;
  }
}