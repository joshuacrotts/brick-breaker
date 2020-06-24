#include "../include/transition.h"

#define MUSIC_FADE 3000

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
    life           = FPS * 10;
    alpha          = 0;
  }
}

void
transition_update( void ) {
  if ( alpha < 255 ) {
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
  draw_rect( &r, 0, 0, 0, alpha, true );
}
