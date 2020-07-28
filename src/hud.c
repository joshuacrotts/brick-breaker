#include "../include/hud.h"

static SDL_Texture *       heartTexture;
static struct fade_color_t fadeColor;
static char *              title        = "BRICK BREAKER";
static char *              pregame_text = "PRESS SPACE TO START!";
static char *              created_by   = "Created by Joshua Crotts";
static char *              artwork_by   = "Artwork by Viola Crotts";
static char *              sfx_by       = "Sound and Music by Break It! Java Game";

static struct button_t *play_button;
static struct button_t *help_button;
static struct button_t *exit_button;

static void draw_lives( SDL_Color * );
static void draw_title( SDL_Color * );
static void draw_pregame_text( SDL_Color * );
static void draw_score( SDL_Color * );
static void draw_level_number( void );
static void spawn_star_particles( float, float, uint32_t, uint32_t );

void
init_HUD( void ) {
  heartTexture = Stds_LoadTexture( "res/img/life.png" );
  Stds_LoadMusic( "res/sfx/music/titlesong.ogg" );
  Stds_PlayMusic( true );

  SDL_Color c1;
  SDL_Color c2;

  c1.r = 0xff;
  c1.g = 0;
  c1.b = 0;

  c2.r            = 0;
  c2.g            = 0xff;
  c2.b            = 0;
  fadeColor.c1    = c1;
  fadeColor.c2    = c2;
  fadeColor.time  = 0.0f;
  fadeColor.alpha = 0.01f;
}

void
init_menu( void ) {
  SDL_Color play_color;
  play_color.r = 0xff;
  play_color.g = 0xff;
  play_color.b = 0xff;

  // ===== PLAY BUTTON ===== //
  play_button             = add_button_texture( app.SCREEN_WIDTH / 2 - 150, app.SCREEN_HEIGHT / 2,
                                    "res/img/ui/buttonStock1.png", "res/fonts/nes.ttf", 24,
                                    &play_color, "PLAY" );
  play_button->texture[1] = Stds_LoadTexture( "res/img/ui/buttonStock1h.png" );
  
  // ===== HELP BUTTON ===== //
  help_button = add_button_texture( app.SCREEN_WIDTH / 2 - 150, app.SCREEN_HEIGHT / 2 + 100,
                                    "res/img/ui/buttonStock1.png", "res/fonts/nes.ttf", 24,
                                    &play_color, "HELP" );
  help_button->texture[1] = Stds_LoadTexture( "res/img/ui/buttonStock1h.png" );

  // ===== EXIT BUTTON ===== //
  exit_button = add_button_texture( app.SCREEN_WIDTH / 2 - 150, app.SCREEN_HEIGHT / 2 + 200,
                                    "res/img/ui/buttonStock1.png", "res/fonts/nes.ttf", 24,
                                    &play_color, "QUIT" );
  exit_button->texture[1] = Stds_LoadTexture( "res/img/ui/buttonStock1h.png" );

  app.button_tail->next = play_button;
  app.button_tail       = play_button;

  app.button_tail->next = help_button;
  app.button_tail       = help_button;

  app.button_tail->next = exit_button;
  app.button_tail       = exit_button;
}

void
update_HUD( void ) {
  if ( stage.state == MENU ) {
    menu_update();
    update_buttons();
  } else {
    spawn_star_particles( Stds_RandomFloat( 400.0f, 2000.0f ), Stds_RandomFloat( 900.0f, 1100.0f ),
                          20, ID_P_STAR_MASK );
  }
}

void
menu_update( void ) {
  if ( is_mouse_over_button( play_button ) ) {
    play_button->texture_id = 1;
  } else {
    play_button->texture_id = 0;
  }

  if ( is_mouse_over_button( help_button ) ) {
    help_button->texture_id = 1;
  } else {
    help_button->texture_id = 0;
  }

  if ( is_mouse_over_button( exit_button ) ) {
    exit_button->texture_id = 1;
  } else {
    exit_button->texture_id = 0;
  }

  if ( is_button_clicked( play_button, SDL_BUTTON_LEFT ) ) {
    stage.state = GAME;
    Stds_PlayMusic( false );
    load_level_music( stage.level_id );
  } else if ( is_button_clicked( help_button, SDL_BUTTON_LEFT ) ) {
    Stds_Print( "HELP!" );
  } else if ( is_button_clicked( exit_button, SDL_BUTTON_LEFT ) ) {
    exit( EXIT_SUCCESS );
  }
}

void
draw_HUD( void ) {
  SDL_Color c = Stds_CombineFadeColor( &fadeColor );
  c.a         = 0xff;
  Stds_DrawRectStroke( 0, 0, app.SCREEN_WIDTH, app.SCREEN_HEIGHT, INSETS, &c, false );

  if ( stage.state == MENU ) {
    draw_buttons();
    menu_draw( &c );
  }

  if ( stage.state == GAME ) {
    draw_title( &c );
    draw_lives( &c );
    draw_score( &c );
  }

  if ( app.game_state == PREGAME && stage.state == GAME ) {
    draw_level_number();
    draw_pregame_text( &c );
  }
}

void
menu_draw( SDL_Color *c ) {
  c->a = 0xff;
  int fw, fh;
  Stds_GetStringSize( title, "res/fonts/nes.ttf", 24, &fw, &fh );
  Stds_DrawText( ( app.SCREEN_WIDTH >> 1 ) - ( fw >> 1 ), 200, "res/fonts/nes.ttf", 24, c, title );

  Stds_GetStringSize( created_by, "res/fonts/nes.ttf", 12, &fw, &fh );
  Stds_DrawText( ( app.SCREEN_WIDTH >> 1 ) - ( fw >> 1 ), app.SCREEN_HEIGHT - fh * 6,
                 "res/fonts/nes.ttf", 12, c, created_by );

  Stds_GetStringSize( artwork_by, "res/fonts/nes.ttf", 12, &fw, &fh );
  Stds_DrawText( ( app.SCREEN_WIDTH >> 1 ) - ( fw >> 1 ), app.SCREEN_HEIGHT - fh * 4,
                 "res/fonts/nes.ttf", 12, c, artwork_by );

  Stds_GetStringSize( sfx_by, "res/fonts/nes.ttf", 12, &fw, &fh );
  Stds_DrawText( ( app.SCREEN_WIDTH >> 1 ) - ( fw >> 1 ), app.SCREEN_HEIGHT - fh * 2,
                 "res/fonts/nes.ttf", 12, c, sfx_by );
}

void
draw_paused( void ) {
  SDL_Rect r;
  r.x = 0;
  r.y = 0;
  r.w = app.SCREEN_WIDTH;
  r.h = app.SCREEN_HEIGHT;

  SDL_Color c     = {0, 0, 0, 128};
  SDL_Color white = {0xff, 0xff, 0xff, 0xff};

  Stds_DrawRect( &r, &c, true, false );
  int fw, fh;
  Stds_GetStringSize( "PAUSED", "res/fonts/nes.ttf", 24, &fw, &fh );
  Stds_DrawText( app.SCREEN_WIDTH / 2 - fw / 2, app.SCREEN_HEIGHT / 2, "res/fonts/nes.ttf", 24,
                 &white, "PAUSED" );
}

/*
 * Draws the hearts representing the user's
 * lives. This may need to be non-static for accessibility
 * purposes (i.e. to change # of lives).
 */
static void
draw_lives( SDL_Color *c ) {
  int fw, fh;
  int tw, th;
  int initial_offset = 20;
  int offset         = 5;

  Stds_DrawText( initial_offset, initial_offset, "res/fonts/nes.ttf", 12, c, "LIVES: " );

  SDL_QueryTexture( heartTexture, NULL, NULL, &tw, &th );
  Stds_GetStringSize( "LIVES: ", "res/fonts/nes.ttf", 12, &fw, &fh );

  int v_offset = initial_offset + fh + offset;

  for ( int i = 0, x = initial_offset; i < paddle->life; i++, x += ( tw + offset ) ) {
    Stds_DrawTexture( heartTexture, x, v_offset, tw, th, 0, SDL_FLIP_NONE, NULL, false );
  }
}

/*
 *
 */
static void
draw_title( SDL_Color *c ) {
  int fw, fh;
  Stds_GetStringSize( title, "res/fonts/nes.ttf", 12, &fw, &fh );
  Stds_DrawText( ( app.SCREEN_WIDTH >> 1 ) - ( fw >> 1 ), 20, "res/fonts/nes.ttf", 12, c, title );
}

/*
 *
 */
static void
draw_pregame_text( SDL_Color *c ) {
  int fw, fh;
  Stds_GetStringSize( pregame_text, "res/fonts/nes.ttf", 24, &fw, &fh );
  Stds_DrawText( ( app.SCREEN_WIDTH / 2 ) - ( fw / 2 ),
                 ( app.SCREEN_HEIGHT >> 1 ) + ( app.SCREEN_HEIGHT / 4 ), "res/fonts/nes.ttf", 24,
                 c, pregame_text );
}

/*
 *
 */
static void
draw_score( SDL_Color *c ) {
  int fw, fh;
  int offset = 20;
  Stds_GetStringSize( "Score:", "res/fonts/nes.ttf", 12, &fw, &fh );
  int       v_offset = offset + fh + 5;
  SDL_Color white    = {0xff, 0xff, 0xff, 0xff};
  // Draw score label.
  Stds_DrawText( app.SCREEN_WIDTH - fw - offset, offset, "res/fonts/nes.ttf", 12, c, "Score:" );

  // Draw numeric score.
  Stds_DrawText( app.SCREEN_WIDTH - fw - offset, v_offset, "res/fonts/nes.ttf", 12, &white, "%d",
                 stage.score );
}

/*
 *
 */
static void
draw_level_number() {
  int          fw, fh;
  const int8_t MAX_DIGITS = 3;

  char level_data[MAX_BUFFER_SIZE];
  char number_buffer[MAX_DIGITS];

  SDL_Color white = {0xff, 0xff, 0xff, 0xff};

  sprintf( number_buffer, "%d", stage.level_id );
  strcpy( level_data, "< LEVEL " );
  char *level_string = strcat( level_data, number_buffer );
  strcat( level_data, " >" );

  Stds_GetStringSize( level_data, "res/fonts/nes.ttf", 24, &fw, &fh );
  Stds_DrawText( ( app.SCREEN_WIDTH / 2 ) - ( fw / 2 ),
                 ( app.SCREEN_HEIGHT >> 1 ) + ( app.SCREEN_HEIGHT / 5 ), "res/fonts/nes.ttf", 24,
                 &white, level_data );
}

static void
spawn_star_particles( float x, float y, uint32_t n, uint32_t flags ) {
  for ( int i = 0; i < n; i++ ) {
    struct particle_t p;

    float dx = -10;
    float dy = -10;

    uint16_t w = Stds_RandomInt( 1, 3 );
    uint16_t h = w;
    uint8_t  r = 0xff;
    uint8_t  g = 0xff;
    uint8_t  b = 0xff;
    uint8_t  a = Stds_RandomInt( 5, 15 );

    p = add_particle( x, y, dx, dy, 0, 0, w, h, 0, r, g, b, a, 0, flags | ID_P_SQUARE_MASK );
    Stds_InsertParticle( ps, &p );
  }
}