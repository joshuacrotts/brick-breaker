#include "../include/player.h"

#define DECAY_RATE    4
#define INITIAL_ALPHA 90
#define DECELERATION  0.95f
#define JUMP_VEL      -8.0f
#define VELOCITY      5.0f
#define GRAVITY       0.3f

static bool         is_moving    = false;
static bool         is_attacking = false;
static animation_t *idle_animation;
static animation_t *walk_animation;
static animation_t *attack_animation;

static void key_input_listener( void );
static void check_bounds( void );

void
init_player() {
  player = malloc( sizeof( entity_t ) );

  if ( player == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for player_t. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( player, 0, sizeof( entity_t ) );

  player->x     = SCREEN_WIDTH / 2.0f;
  player->y     = SCREEN_HEIGHT / 2.0f;
  player->angle = 0;

  idle_animation   = add_animation( "tests/res/img/player/8bitidle/idle_", 2, 0.33f );
  walk_animation   = add_animation( "tests/res/img/player/8bitwalk/walk_", 4, 0.1f );
  attack_animation = add_animation( "tests/res/img/player/8bitattack/attack_", 7, 0.05f );
}

void
player_update( void ) {
  key_input_listener();

  if ( is_moving ) {
    player->animation = walk_animation;
  } else if ( is_attacking ) {
    player->animation = attack_animation;
    if ( attack_animation->cycle_once && attack_animation->current_frame_id == attack_animation->number_of_frames - 1) {
      is_attacking = false;
    }
  } else {
    player->animation = idle_animation;
  }

  //print("%d, %d, %d", is_attacking, is_moving, attack_animation->flags);

  SDL_QueryTexture( player->animation->frames[player->animation->current_frame_id], NULL, NULL,
                    &player->w, &player->h );

  player->dy += GRAVITY;

  player->x += player->dx;
  player->y += player->dy;

  player->animation->pos_x = player->x;
  player->animation->pos_y = player->y;

  check_bounds();
  animation_update( player->animation );

   if ( is_attacking ) {
     add_trail( player, DECAY_RATE, INITIAL_ALPHA, true, player->animation->flip );
   }
}

void
player_draw( void ) {
  animation_draw( player->animation );
}

/*
 *
 */
static void
key_input_listener( void ) {
  is_moving = app.keyboard[SDL_SCANCODE_A] | app.keyboard[SDL_SCANCODE_D];

  if ( app.keyboard[SDL_SCANCODE_W] ) {
    player->dy                   = JUMP_VEL;
    app.keyboard[SDL_SCANCODE_W] = 0;
  }

  if ( app.keyboard[SDL_SCANCODE_A] ) {
    player->dx              = -VELOCITY;
    player->animation->flip = SDL_FLIP_HORIZONTAL;
  }

  else if ( app.keyboard[SDL_SCANCODE_D] ) {
    player->dx              = VELOCITY;
    player->animation->flip = SDL_FLIP_NONE;
  }

  else if ( app.keyboard[SDL_SCANCODE_SPACE] ) {
    is_attacking = true;
    attack_animation->flip = player->animation->flip;
    attack_animation->cycle_once = true;
    attack_animation->flags |= ANIMATION_ACTIVE_MASK;
  }

  else {
    player->dx = 0;
  }
}

/*
 *
 */
static void
check_bounds( void ) {
  if ( player->x < 0 ) {
    player->x = 0;
  }

  if ( player->x + player->w > LEVEL_WIDTH ) {
    player->x = LEVEL_WIDTH - player->w;
  }

  if ( player->y < 0 ) {
    player->y = 0;
  }

  if ( player->y + player->h > LEVEL_HEIGHT ) {
    player->y = LEVEL_HEIGHT - player->h;
  }
}