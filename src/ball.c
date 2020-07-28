#include "../include/ball.h"

#define BALL_DEATH_PARTICLES 20

static void check_bounds( struct entity_t * );
static void spawn_ball_particles( struct entity_t * );

struct entity_t *
add_ball( float x, float y, uint32_t flags ) {
  struct entity_t *b;
  b = malloc( sizeof( struct entity_t ) );
  memset( b, 0, sizeof( struct entity_t ) );

  b->x          = x;
  b->y          = y;
  b->texture[0] = Stds_LoadTexture( "res/img/ball_sprite_1.png" );
  SDL_QueryTexture( b->texture[0], NULL, NULL, &b->w, &b->h );

  // Continuously generate a speed that is reasonable.
  do {
    b->dx = Stds_RandomFloat( -10.0f, 10.0f );
  } while ( b->dx < 7.0f && b->dx > -7.0f );

  do {
    b->dy = Stds_RandomFloat( -10.0f, 10.0f );
  } while ( b->dy < 7.0f && b->dy > -7.0f );

  b->id_flags |= ID_BALL_MASK;
  b->flags |= flags;
  currentLevel->ball_count++;
  return b;
}

void
ball_update( struct entity_t *b ) {
  b->x += b->dx;
  b->y += b->dy;
  Stds_AddTextureTrail( b, 4, 60, SDL_FLIP_NONE, false );
  check_bounds( b );
}

void
ball_draw( struct entity_t *b ) {
  Stds_DrawTexture( b->texture[0], b->x, b->y, b->w, b->h, b->angle, SDL_FLIP_NONE, NULL, false );
}

void
ball_die( struct entity_t *b ) {
  free( b );
}

/*
 *
 */
static void
check_bounds( struct entity_t *b ) {
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
    b->flags |= STDS_DEATH_MASK;
  }
}

/*
 *
 */
static void
spawn_ball_particles( struct entity_t *b ) {
  struct entity_t *p;

  for ( int i = 0; i < BALL_DEATH_PARTICLES; i++ ) {
    struct particle_t p;
    p.x             = b->x + b->w / 2;
    p.y             = b->y + b->h / 2;
    p.dx            = Stds_RandomFloat( -5, 5 );
    p.dy            = Stds_RandomFloat( -7, 5 );
    p.delta_accel_x = p.delta_accel_y = 0;
    p.w = p.h = 3;
    p.color.r = 0xff;
    p.color.g = p.color.b = 0;
    p.color.a = 0xff;
    p.delta_alpha = -3.0f;
    p.id_flags |= ID_P_SQUARE_MASK;
  }
}