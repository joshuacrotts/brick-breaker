#include "../include/ball.h"

#define BALL_DEATH_PARTICLES 20

static void check_bounds( entity_t * );
static void spawn_ball_particles( entity_t * );

entity_t *
add_ball( float x, float y, uint32_t flags ) {
  entity_t *b;
  b = malloc( sizeof( entity_t ) );
  memset( b, 0, sizeof( entity_t ) );

  b->x          = x;
  b->y          = y;
  b->texture[0] = load_texture( "res/img/ball_sprite_1.png" );
  SDL_QueryTexture( b->texture[0], NULL, NULL, &b->w, &b->h );

  // Continuously generate a speed that is reasonable.
  do {
    b->dx = random_float( -10.0f, 10.0f );
  } while ( b->dx < 7.0f && b->dx > -7.0f );

  do {
    b->dy = random_float( -10.0f, 10.0f );
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
  add_trail( b, 4, 60, false, SDL_FLIP_NONE );
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
  } else if ( b->x + b->w > SCREEN_WIDTH ) {
    b->x -= b->w;
    b->dx = -b->dx;
  } else if ( b->y < 0 ) {
    b->y  = 0;
    b->dy = -b->dy;
  } else if ( b->y + b->h > SCREEN_HEIGHT ) {
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

    p = add_particle( b->x + b->w / 2, b->y + b->h / 2, random_float( -5, 5 ),
                      random_float( -7, -5 ), 0, 0, 3, 3, 0, 0xff, 0, 0, 0xff, -3,
                      ID_P_SQUARE_MASK );
    currentLevel->entity_tail->next = p;
    currentLevel->entity_tail       = p;
  }
}