#include "../include/paddle.h"

#define H_VELOCITY   15.0f
#define DECELERATION 0.85f

static void key_input_update( void );
static void check_bounds( void );

void
init_paddle( void ) {
  paddle = malloc( sizeof( struct entity_t ) );
  memset( paddle, 0, sizeof( struct entity_t ) );

  paddle->life       = 3;
  paddle->texture[0] = Stds_LoadTexture( "res/img/paddle.png" );
  SDL_QueryTexture( paddle->texture[0], NULL, NULL, &paddle->w, &paddle->h );

  paddle->x       = app.SCREEN_WIDTH / 2 - paddle->w / 2;
  paddle->y       = app.SCREEN_HEIGHT - 40;
  paddle->scale_x = 1.0f;
  paddle->scale_y = 1.0f;
  paddle->id_flags |= ID_PLAYER_MASK;
}

void
paddle_update( void ) {
  paddle->x += paddle->dx;
  paddle->y += paddle->dy;

  paddle->w *= ( int32_t ) paddle->scale_x;
  paddle->h *= ( int32_t ) paddle->scale_y;

  check_bounds();
  key_input_update();
}

void
paddle_draw( void ) {
  Stds_DrawTexture( paddle->texture[0], paddle->x, paddle->y, paddle->w, paddle->h, paddle->angle,
                    SDL_FLIP_NONE, NULL, false );
}

void
paddle_die( void ) {
  free( paddle );
}

static void
check_bounds( void ) {
  if ( paddle->x < 0 ) {
    paddle->x = 0;
  } else if ( paddle->x + paddle->w > app.SCREEN_WIDTH ) {
    paddle->x = app.SCREEN_WIDTH - paddle->w;
  } else if ( paddle->y < 0 ) {
    paddle->y = 0;
  } else if ( paddle->y + paddle->h > app.SCREEN_HEIGHT ) {
    paddle->y = app.SCREEN_HEIGHT - paddle->h;
  }
}

static void
key_input_update( void ) {
  if ( app.game_state != PAUSED ) {
    paddle->dx *= DECELERATION;
    paddle->dy *= DECELERATION;

    if ( app.keyboard[SDL_SCANCODE_A] ) {
      paddle->dx = -H_VELOCITY;
    }

    if ( app.keyboard[SDL_SCANCODE_D] ) {
      paddle->dx = H_VELOCITY;
    }
  }
}