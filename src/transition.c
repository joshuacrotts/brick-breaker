#include "../include/transition.h"

#define MUSIC_FADE           3000
#define TRANSITION_LIFE_MULT 10
#define MAX_ALPHA            255

static int16_t life;
static int16_t alpha;
static bool    is_restart;

static SDL_Rect r = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

void
activate_transition( bool restart ) {
  is_restart = restart;

  if ( app.game_state != TRANSITION ) {
    Mix_FadeOutMusic( MUSIC_FADE );
    app.game_state = TRANSITION;
    life           = FPS * TRANSITION_LIFE_MULT;
    alpha          = 0;
  }
}

void
transition_update( void ) {
  if ( alpha < MAX_ALPHA ) {
    alpha++;
  } else {
    remove_balls();
  }

  if ( --life <= 0 ) {
    app.game_state = PREGAME;

    if ( !is_restart ) {
      stage.level_id++;
    }
    set_next_level();
  }
}

void
transition_draw( void ) {
  SDL_Color c;
  c.r = c.g = c.b = 0;
  c.a             = alpha;
  draw_rect( &r, &c, true, false );
}
