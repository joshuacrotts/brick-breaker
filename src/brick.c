#include "../include/brick.h"

static void  update_brick_status( struct entity_t * );
static char *get_string_enum( enum Brick );

struct entity_t *
add_brick( float x, float y, uint32_t flags, int8_t identifier ) {
  struct entity_t *b;

  b = malloc( sizeof( struct entity_t ) );
  memset( b, 0, sizeof( struct entity_t ) );

  b->x          = x;
  b->y          = y;
  b->life       = 4;
  b->identifier = identifier;

  b->id_flags |= ID_DEFAULT_BRICK_MASK;
  b->flags |= flags;

  char *str_identifier = get_string_enum( identifier );
  char  buffer[MAX_BUFFER_SIZE];

  // Firstly, load in the animation file.
  memset( buffer, 0, MAX_BUFFER_SIZE );
  strcat( buffer, "res/img/brick/" );
  strcat( buffer, str_identifier );
  strcat( buffer, "/" );
  strcat( buffer, str_identifier );
  strcat( buffer, "_animated.png" );

  b->animation = Stds_AddSpritesheet( buffer, 7, Stds_RandomFloat( 0.05f, 0.111f ), 0, 0, 1, 7 );
  memset( buffer, 0, MAX_BUFFER_SIZE );

  // Now, load in the default image file.
  memset( buffer, 0, MAX_BUFFER_SIZE );
  strcat( buffer, "res/img/brick/" );
  strcat( buffer, str_identifier );
  strcat( buffer, "/" );
  strcat( buffer, str_identifier );
  strcat( buffer, "_0.png" );
  b->texture[0] = Stds_LoadTexture( buffer );
  memset( buffer, 0, MAX_BUFFER_SIZE );
  const int8_t MAX_DIGIT = 3;
  // Next, load in the three files for the damage image.
  for ( int i = 1; i <= MAX_DEBRIS_IMGS; i++ ) {
    char int_buffer[MAX_DIGIT];
    sprintf( int_buffer, "%d", i );
    strcat( buffer, "res/img/brick/" );
    strcat( buffer, str_identifier );
    strcat( buffer, "/" );
    strcat( buffer, str_identifier );
    strcat( buffer, "_" );
    strcat( buffer, int_buffer );
    strcat( buffer, "_damaged.png" );
    b->texture[i] = Stds_LoadTexture( buffer );

    memset( buffer, 0, MAX_BUFFER_SIZE );
  }

  SDL_QueryTexture( b->texture[0], NULL, NULL, &b->w, &b->h );

  return b;
}

void
brick_update( struct entity_t *b ) {
  int32_t randInt = Stds_RandomInt( 1, 2000 );
  if ( !b->animation->is_cycle_once && randInt == 1 && b->life == 4 ) {
    b->animation->is_cycle_once = true;
    b->animation->flags |= STDS_ANIMATION_ACTIVE_MASK;
  }

  if ( b->animation->is_cycle_once ) {
    b->animation->pos_x = b->x;
    b->animation->pos_y = b->y;
    Stds_AnimationUpdate( b->animation );
  }

  update_brick_status( b );
}

void
brick_draw( struct entity_t *b ) {
  if ( b->animation->is_cycle_once && b->life == 4 ) {
    Stds_AnimationDraw( b->animation );
  } else {
    Stds_DrawTexture( b->texture[0], b->x, b->y, b->w, b->h, b->angle, SDL_FLIP_NONE, NULL, false );
  }
}

void
brick_die( struct entity_t *b ) {
  free( b );
}

/*
 *
 */
static void
update_brick_status( struct entity_t *b ) {
  switch ( b->life ) {
  case 4:
    return;
  case 3:
    b->texture[0] = b->texture[1];
    break;
  case 2:
    b->texture[0] = b->texture[2];
    break;
  case 1:
    b->texture[0] = b->texture[3];
    break;
  case 0:
    b->flags |= STDS_DEATH_MASK;
    break;
  }
}

static char *
get_string_enum( enum Brick b ) {
  switch ( b ) {
  case RED:
    return "red";
  case BLUE:
    return "blue";
  case YELLOW:
    return "yellow";
  case PURPLE:
    return "purple";
  case ORANGE:
    return "orange";
  case LIGHT_BLUE:
    return "light_blue";
  case LIGHT_GREEN:
    return "light_green";
  case DARK_GREEN:
    return "dark_green";
  case BROWN:
    return "brown";
  case NULL_COLOR:
    return "NULL";
  }
}
