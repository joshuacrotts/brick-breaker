#include "../include/powerup.h"

#define COIN_SCORE      500
#define LIFE_SCORE      1000
#define POWERUP_DESCENT 3
#define MAX_LIVES       4

struct entity_t *
add_powerup( float x, float y, uint32_t flags, int8_t identifier ) {
  struct entity_t *p;
  p = malloc( sizeof( struct entity_t ) );
  memset( p, 0, sizeof( struct entity_t ) );

  p->x = x;
  p->y = y;
  p->id_flags |= ID_DEFAULT_POWERUP_MASK;
  p->flags |= flags | POWERUP_INACTIVE;
  p->identifier = identifier;

  struct animation_t *a;

  switch ( identifier ) {
  case MULTI_BALL:
    a =  Stds_AddSpritesheet( "res/img/powerup/multi.png", 10, 0.05f, 0, 0, 1, 10 );
    break;
  case LARGE_PADDLE:
    a =  Stds_AddSpritesheet( "res/img/powerup/large.png", 10, 0.05f, 0, 0, 1, 10);
    break;
  case EXTRA_LIFE:
    a =  Stds_AddSpritesheet( "res/img/powerup/extra_life.png", 8, 0.09f, 0, 0, 1, 8 );
    break;
  case GOLD_COIN:
    a =  Stds_AddSpritesheet( "res/img/powerup/gold_coin.png", 16, 0.05f, 0, 0, 1, 16 );
    break;
  default:
    exit( EXIT_ERROR );
  }

  a->flags |= STDS_ANIMATION_ACTIVE_MASK;

  p->w         = a->sprite_width;
  p->h         = a->sprite_height;
  p->animation = a;

  return p;
}

void
powerup_update( struct entity_t *p ) {
  if ( p->flags & POWERUP_ACTIVE ) {
    if ( --p->life < 0 ) {
      if ( p->identifier == LARGE_PADDLE ) {
        powerup_large_deactivate( p );
      }
    }

    return;
  }

  if ( p->animation != NULL ) {
    p->animation->pos_x = p->x;
    p->animation->pos_y = p->y;
    Stds_AnimationUpdate( p->animation );
  }

  p->y += POWERUP_DESCENT;

  if ( p->y > app.SCREEN_HEIGHT ) {
    p->flags |= STDS_DEATH_MASK;
  }
}

void
powerup_draw( struct entity_t *p ) {
  if ( p->animation != NULL && ( ( p->flags & POWERUP_ACTIVE ) == 0 ) ) {
    Stds_AnimationDraw( p->animation );
  }
}

void
powerup_die( struct entity_t *p ) {
  if ( p->flags & STDS_DEATH_MASK ) {
    free( p );
  }
}

void
powerup_large_activate( struct entity_t *p ) {
  if ( paddle->scale_x >= 2.0f ) {
    return;
  }

  p->life = FPS * 10;
  p->flags |= POWERUP_ACTIVE;
  paddle->scale_x = 2.0f;
  paddle->w *= ( uint32_t ) paddle->scale_x;
}

void
powerup_large_deactivate( struct entity_t *p ) {
  paddle->scale_x = 1.0f;
  paddle->w /= 2;
  p->flags |= STDS_DEATH_MASK;
}

void
powerup_multi_activate( struct entity_t *p ) {
  struct entity_t *b1;
  struct entity_t *b2;
  b1 = add_ball( Stds_RandomFloat( 300, 600 ), app.SCREEN_HEIGHT / 2, 0 );
  b2 = add_ball( Stds_RandomFloat( 300, 600 ), app.SCREEN_HEIGHT / 2, 0 );

  currentLevel->ball_tail->next = b1;
  currentLevel->ball_tail       = b1;
  currentLevel->ball_tail->next = b2;
  currentLevel->ball_tail       = b2;

  p->flags |= STDS_DEATH_MASK;
}

void
powerup_coin_activate( struct entity_t *p ) {
  add_score_item( p->x, p->y, COIN_SCORE );
  Stds_PlaySounds( SND_COIN, CH_ANY );
  stage.score += COIN_SCORE;
  p->flags |= STDS_DEATH_MASK;
}

void
powerup_life_activate( struct entity_t *p ) {
  if ( paddle->life <= MAX_LIVES ) {
    paddle->life++;
  }
  add_score_item( p->x, p->y, LIFE_SCORE );
  Stds_PlaySounds( SND_EXTRA_LIFE, CH_ANY );
  stage.score += LIFE_SCORE;
  p->flags |= STDS_DEATH_MASK;
}