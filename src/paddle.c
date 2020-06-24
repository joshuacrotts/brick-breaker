#include "../include/paddle.h"

#define H_VELOCITY   15.0f
#define DECELERATION 0.85f

static void key_input_update( void );
static void check_bounds( void );

void
init_paddle( void ) {
  paddle = malloc( sizeof( entity_t ) );
  memset( paddle, 0, sizeof( entity_t ) );

  paddle->life       = 3;
  paddle->texture[0] = load_texture( "res/img/paddle.png" );
  SDL_QueryTexture( paddle->texture[0], NULL, NULL, &paddle->w, &paddle->h );

  paddle->x       = SCREEN_WIDTH / 2 - paddle->w / 2;
  paddle->y       = SCREEN_HEIGHT - 40;
  paddle->scale_x = 1.0f;
  paddle->scale_y = 1.0f;
  paddle->id_flags |= ID_PLAYER_MASK;
}

void
paddle_update( void ) {
  paddle->x += paddle->dx;
  paddle->y += paddle->dy;

  check_bounds();
  key_input_update();
}

void
paddle_draw( void ) {
  blit_texture_scaled( paddle->texture[0], paddle->x, paddle->y, paddle->scale_x, paddle->scale_y,
                       paddle->angle );
}

void
paddle_die( void ) {
  free( paddle );
}

static void
check_bounds( void ) {
  if ( paddle->x < 0 ) {
    paddle->x = 0;
  } else if ( paddle->x + paddle->w > SCREEN_WIDTH ) {
    paddle->x = SCREEN_WIDTH - paddle->w;
  } else if ( paddle->y < 0 ) {
    paddle->y = 0;
  } else if ( paddle->y + paddle->h > SCREEN_HEIGHT ) {
    paddle->y = SCREEN_HEIGHT - paddle->h;
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