#include "../include/level.h"

#define MAXC            16
#define CHAR_OFFSET     48
#define BRICK_ROW_COUNT 10
#define BRICK_COL_COUNT 6
#define BRICK_WIDTH     92
#define BRICK_HEIGHT    32

static entity_t *spawn_powerup( entity_t * );

static void update_balls( void );
static void update_powerups( void );
static void update_bricks( void );
static void update_score_items( void );

static void draw_balls( void );
static void draw_powerups( void );
static void draw_bricks( void );
static void draw_score_items( void );

static void ball_hit_paddle( entity_t * );
static void ball_hit_brick( entity_t * );
static void powerup_hit_paddle( entity_t * );

level_t *
add_level( uint16_t level_id ) {
  level_t *    level;
  FILE *       fptr;
  const int8_t MAX_DIGITS = 3;

  char  level_data[MAX_BUFFER_SIZE];
  char  number_buffer[MAX_DIGITS];
  char *file_extsn = ".txt";

  sprintf( number_buffer, "%d", level_id );
  strcpy( level_data, "res/level_data/level_" );
  char *file_name     = strcat( level_data, number_buffer );
  char *file_name_ext = strcat( level_data, file_extsn );

  fptr = fopen( level_data, "r" );

  if ( fptr == NULL ) {
    SDL_LogError( SDL_LOG_CATEGORY_ERROR, "Could not read from file! %s\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  // Create the buffer for the level data
  // where each line corresponds to one row
  // of bricks.
  char buffer[MAXC];

  level = malloc( sizeof( level_t ) );
  memset( level, 0, sizeof( level_t ) );

  level->ball_tail       = &level->ball_head;
  level->entity_tail     = &level->entity_head;
  level->ball_tail       = &level->ball_head;
  level->brick_tail      = &level->brick_head;
  level->powerup_tail    = &level->powerup_head;
  level->score_item_tail = &level->score_item_head;
  level->brick_count     = 0;

  uint8_t brick_data = 1;

  for ( int y = 120; y < 120 + ( BRICK_HEIGHT * BRICK_ROW_COUNT ); y += 32 ) {
    fgets( buffer, MAXC, fptr );
    for ( int x = 20, bi = 0; x <= app.SCREEN_WIDTH - 80; x += 92, bi++ ) {
      entity_t *b;
      int       c = ( buffer[bi] - '\0' ) - CHAR_OFFSET;

      // If the char is invalid, then quit iteration.
      if ( c < 0 ) {
        break;
      }

      // Depending on the char value, add its corresponding
      // brick ID.
      if ( c != 0 ) {
        b = add_brick( x, y, 0, c );

        level->brick_tail->next = b;
        level->brick_tail       = b;
        level->brick_count++;
      }
    }
  }

  fclose( fptr );
  return level;
}

void
level_update() {
  if ( app.game_state != TRANSITION ) {
    update_balls();
    update_powerups();
    update_score_items();
  }
  update_bricks();
}

void
level_draw() {
  draw_balls();
  draw_powerups();
  draw_score_items();
  draw_bricks();
}

void
set_next_level( void ) {
  level_t *l = add_level( stage.level_id );
  load_level_music( stage.level_id );
  stage.level_tail->next = l;
  stage.level_tail       = l;
  currentLevel           = l;
}

void
level_die() {
  level_t *l;

  for ( l = stage.level_head.next; l != NULL; l = l->next ) {
    free( l );
  }

  if ( currentLevel != NULL ) {
    free( currentLevel );
    currentLevel = NULL;
  }
}

void
remove_balls( void ) {
  entity_t *b = &currentLevel->ball_head;

  while ( b != NULL ) {
    entity_t *tmp = b->next;
    b             = NULL;
    free( b );
    b = tmp;
  }
}

void
load_level_music( uint16_t level ) {
  const int8_t MAX_DIGITS = 3;

  char  level_data[MAX_BUFFER_SIZE];
  char  number_buffer[MAX_DIGITS];
  char *file_extsn = ".ogg";

  sprintf( number_buffer, "%d", level );
  strcpy( level_data, "res/sfx/music/level_" );
  char *file_name     = strcat( level_data, number_buffer );
  char *file_name_ext = strcat( level_data, file_extsn );
  load_music( level_data );
  print( "%s", level_data );
  play_music( true );
}

/*
 *
 */
static void
update_balls( void ) {

  if ( currentLevel->ball_count == 0 && app.game_state == RUNNING ) {
    paddle->life--;
    activate_transition( true );
  }

  entity_t *b;
  entity_t *prevBall;

  prevBall = &currentLevel->ball_head;

  for ( b = currentLevel->ball_head.next; b != NULL; b = b->next ) {
    if ( b->id_flags & ID_BALL_MASK ) {
      ball_hit_paddle( b );
      ball_hit_brick( b );
      ball_update( b );
    }

    if ( b->flags & DEATH_MASK ) {
      if ( b == currentLevel->ball_tail ) {
        currentLevel->ball_tail = prevBall;
      }

      prevBall->next = b->next;
      ball_die( b );
      b = prevBall;
    }

    prevBall = b;
  }
}

/*
 *
 */
static void
update_powerups( void ) {
  entity_t *p;
  entity_t *prev;

  prev = &currentLevel->powerup_head;

  for ( p = currentLevel->powerup_head.next; p != NULL; p = p->next ) {
    if ( p->id_flags & ID_DEFAULT_POWERUP_MASK ) {
      powerup_hit_paddle( p );
      powerup_update( p );
    }

    if ( p->flags & DEATH_MASK ) {
      if ( p == currentLevel->powerup_tail ) {
        currentLevel->powerup_tail = prev;
      }

      prev->next = p->next;
      powerup_die( p );
      p = prev;
    }
    prev = p;
  }
}

/*
 *
 */
static void
update_bricks( void ) {
  entity_t *brick;
  entity_t *prevBrick;

  prevBrick = &currentLevel->brick_head;

  for ( brick = currentLevel->brick_head.next; brick != NULL; brick = brick->next ) {
    brick_update( brick );

    if ( brick->flags & DEATH_MASK ) {
      if ( brick == currentLevel->brick_tail ) {
        currentLevel->brick_tail = prevBrick;
      }
      prevBrick->next = brick->next;
      brick_die( brick );
      brick = prevBrick;
    }
    prevBrick = brick;
  }
}

/*
 *
 */
static void
update_score_items( void ) {
  score_item_t *s;
  score_item_t *prev;

  prev = &currentLevel->score_item_head;

  for ( s = currentLevel->score_item_head.next; s != NULL; s = s->next ) {
    score_item_update( s );

    if ( s->flags & DEATH_MASK ) {
      if ( s == currentLevel->score_item_tail ) {
        currentLevel->score_item_tail = prev;
      }

      prev->next = s->next;
      free( s );
      s = prev;
    }
    prev = s;
  }
}

/*
 *
 */
static void
draw_powerups( void ) {
  entity_t *p;

  for ( p = currentLevel->powerup_head.next; p != NULL; p = p->next ) {
    if ( p->id_flags & ID_DEFAULT_POWERUP_MASK ) {
      powerup_draw( p );
    }
  }
}

/*
 *
 */
static void
draw_score_items( void ) {
  score_item_t *s;

  for ( s = currentLevel->score_item_head.next; s != NULL; s = s->next ) {
    score_item_draw( s );
  }
}

/*
 *
 */
static void
draw_balls( void ) {
  entity_t *b;

  for ( b = currentLevel->ball_head.next; b != NULL; b = b->next ) {
    if ( b->id_flags & ID_BALL_MASK ) {
      ball_draw( b );
    }
  }
}

/*
 *
 */
static void
draw_bricks( void ) {
  entity_t *b;

  for ( b = currentLevel->brick_head.next; b != NULL; b = b->next ) {
    brick_draw( b );
  }
}

/*
 *
 */
static void
ball_hit_brick( entity_t *ball ) {
  entity_t *brick;

  for ( brick = currentLevel->brick_head.next; brick != NULL; brick = brick->next ) {
    if ( check_intersection( ( int32_t ) ball->x, ( int32_t ) ball->y, ball->w, ball->h,
                             ( int32_t ) brick->x, ( int32_t ) brick->y, brick->w, brick->h ) ) {
      brick->life--;
      if ( brick->life > 0 ) {
        play_sound( SND_BRICK_SHATTER, CH_BRICK );
      } else {
        entity_t *p;
        p = spawn_powerup( brick );

        if ( p != NULL ) {
          currentLevel->powerup_tail->next = p;
          currentLevel->powerup_tail       = p;
        }

        currentLevel->brick_count--;
        currentLevel->last_break_timer++;

        play_sound( SND_BRICK_BREAK, CH_BRICK );
        add_score_item( brick->x + brick->w / 4, brick->y + brick->h / 4, 0 );

        if ( currentLevel->brick_count == 0 ) {
          activate_transition( false );
        }
      }

      ball->dy = -ball->dy;
      // Add debris here.
      add_debris( brick, 0 );
      break;
    }
  }
}

/*
 *
 */
static void
ball_hit_paddle( entity_t *b ) {

  if ( check_intersection( ( int32_t ) paddle->x, ( int32_t ) paddle->y, ( int32_t ) paddle->w,
                           ( int32_t ) paddle->h, ( int32_t ) b->x, ( int32_t ) b->y,
                           ( int32_t ) b->w, ( int32_t ) b->h ) ) {
    uint32_t SIZE   = 16;
    double   rel    = ( paddle->x + ( paddle->w / 2 ) ) - ( b->x + ( SIZE / 2 ) );
    double   norm   = rel / ( paddle->w / 2 );
    double   bounce = norm * ( 5 * PI / 12 );

    b->dx = ( float ) ( BALL_SPEED * -sin( bounce ) );
    b->dy = ( float ) ( -BALL_SPEED * cos( bounce ) );
    return;
  }
}

/*
 *
 */
static void
powerup_hit_paddle( entity_t *p ) {
  if ( check_intersection( ( int32_t ) paddle->x, ( int32_t ) paddle->y, ( int32_t ) paddle->w,
                           ( int32_t ) paddle->h, ( int32_t ) p->x, ( int32_t ) p->y,
                           ( int32_t ) p->w, ( int32_t ) p->h ) &&
       p->flags & POWERUP_INACTIVE ) {

    if ( p->identifier == LARGE_PADDLE ) {
      powerup_large_activate( p );
    } else if ( p->identifier == MULTI_BALL ) {
      powerup_multi_activate( p );
    } else if ( p->identifier == GOLD_COIN ) {
      powerup_coin_activate( p );
    } else if ( p->identifier == EXTRA_LIFE ) {
      powerup_life_activate( p );
    }
  }
}

/*
 * This needs to be severely updated.
 */
static entity_t *
spawn_powerup( entity_t *parent ) {
  entity_t *p;

  float prob = random_float( 1.0f, 1000.0f );

  if ( prob < 50.0f ) {
    p = add_powerup( parent->x, parent->y, 0, EXTRA_LIFE );
  } else if ( prob < 100.0f ) {
    p = add_powerup( parent->x, parent->y, 0, LARGE_PADDLE );
  } else if ( prob < 150.0f ) {
    p = add_powerup( parent->x, parent->y, 0, MULTI_BALL );
  } else if ( prob < 500.0f ) {
    p = add_powerup( parent->x, parent->y, 0, GOLD_COIN );
  } else {
    p = NULL;
  }

  return p;
}