#include "../include/hud.h"

static SDL_Texture *heartTexture;
static fade_color_t fadeColor;
static char *       title        = "BRICK BREAKER";
static char *       pregame_text = "PRESS SPACE TO START!";
static char *       created_by   = "Created by Joshua Crotts";
static char *       artwork_by   = "Artwork by Viola Crotts";
static char *       sfx_by       = "Sound and Music by Break It! Java Game";

static button_t *play_button;
static button_t *help_button;
static button_t *exit_button;

static void draw_lives( SDL_Color * );
static void draw_title( SDL_Color * );
static void draw_pregame_text( SDL_Color * );
static void draw_score( SDL_Color * );
static void draw_level_number( void );

void
init_HUD( void ) {
  heartTexture = load_texture( "res/img/life.png" );
  load_music( "res/sfx/music/titlesong.ogg" );
  play_music( true );

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
  play_button =
      add_button_texture( SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, "res/img/ui/buttonStock1.png",
                          "res/fonts/nes.ttf", 24, &play_color, "PLAY" );
  play_button->texture[1] = load_texture( "res/img/ui/buttonStock1h.png" );

  // ===== HELP BUTTON ===== //
  help_button             = add_button_texture( SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 100,
                                    "res/img/ui/buttonStock1.png", "res/fonts/nes.ttf", 24,
                                    &play_color, "HELP" );
  help_button->texture[1] = load_texture( "res/img/ui/buttonStock1h.png" );

  // ===== EXIT BUTTON ===== //
  exit_button             = add_button_texture( SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 200,
                                    "res/img/ui/buttonStock1.png", "res/fonts/nes.ttf", 24,
                                    &play_color, "QUIT" );
  exit_button->texture[1] = load_texture( "res/img/ui/buttonStock1h.png" );

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
    spawn_star_particles( NULL, random_int( 400, 2000 ), random_int( 900, 1100 ), 3,
                          ID_P_STAR_MASK );
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
    play_music( false );
    load_level_music( stage.level_id );
  } else if ( is_button_clicked( help_button, SDL_BUTTON_LEFT ) ) {
    print( "HELP!" );
  } else if ( is_button_clicked( exit_button, SDL_BUTTON_LEFT ) ) {
    exit( EXIT_SUCCESS );
  }
}

void
draw_HUD( void ) {
  SDL_Color c = combine_fade_color( &fadeColor );
  c.a = 0xff;
  draw_rect_stroke( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, INSETS, &c, false );

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
  int fw, fh;
  get_string_size( title, "res/fonts/nes.ttf", 24, &fw, &fh );
  draw_text( ( SCREEN_WIDTH >> 1 ) - ( fw >> 1 ), 200, c->r, c->g, c->b, "res/fonts/nes.ttf", 24,
             title );

  get_string_size( created_by, "res/fonts/nes.ttf", 12, &fw, &fh );
  draw_text( ( SCREEN_WIDTH >> 1 ) - ( fw >> 1 ), SCREEN_HEIGHT - fh * 6, c->r, c->g, c->b,
             "res/fonts/nes.ttf", 12, created_by );

  get_string_size( artwork_by, "res/fonts/nes.ttf", 12, &fw, &fh );
  draw_text( ( SCREEN_WIDTH >> 1 ) - ( fw >> 1 ), SCREEN_HEIGHT - fh * 4, c->r, c->g, c->b,
             "res/fonts/nes.ttf", 12, artwork_by );

  get_string_size( sfx_by, "res/fonts/nes.ttf", 12, &fw, &fh );
  draw_text( ( SCREEN_WIDTH >> 1 ) - ( fw >> 1 ), SCREEN_HEIGHT - fh * 2, c->r, c->g, c->b,
             "res/fonts/nes.ttf", 12, sfx_by );
}

void
draw_paused( void ) {
  SDL_Rect r;
  r.x = 0;
  r.y = 0;
  r.w = SCREEN_WIDTH;
  r.h = SCREEN_HEIGHT;

  SDL_Color c;
  c.r = c.g = c.b = 0;
  c.a = 128;

  draw_rect( &r, &c, true, false );
  int fw, fh;
  get_string_size( "PAUSED", "res/fonts/nes.ttf", 24, &fw, &fh );
  draw_text( SCREEN_WIDTH / 2 - fw / 2, SCREEN_HEIGHT / 2, 0xff, 0xff, 0xff, "res/fonts/nes.ttf",
             24, "PAUSED" );
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

  draw_text( initial_offset, initial_offset, c->r, c->g, c->b, "res/fonts/nes.ttf", 12, "LIVES: " );

  SDL_QueryTexture( heartTexture, NULL, NULL, &tw, &th );
  get_string_size( "LIVES: ", "res/fonts/nes.ttf", 12, &fw, &fh );

  int v_offset = initial_offset + fh + offset;

  for ( int i = 0, x = initial_offset; i < paddle->life; i++, x += ( tw + offset ) ) {
    blit_texture( heartTexture, x, v_offset, false, false );
  }
}

/*
 *
 */
static void
draw_title( SDL_Color *c ) {
  int fw, fh;
  get_string_size( title, "res/fonts/nes.ttf", 12, &fw, &fh );
  draw_text( ( SCREEN_WIDTH >> 1 ) - ( fw >> 1 ), 20, c->r, c->g, c->b, "res/fonts/nes.ttf", 12,
             title );
}

/*
 *
 */
static void
draw_pregame_text( SDL_Color *c ) {
  int fw, fh;
  get_string_size( pregame_text, "res/fonts/nes.ttf", 24, &fw, &fh );
  draw_text( ( SCREEN_WIDTH / 2 ) - ( fw / 2 ), ( SCREEN_HEIGHT >> 1 ) + ( SCREEN_HEIGHT / 4 ),
             c->r, c->g, c->b, "res/fonts/nes.ttf", 24, pregame_text );
}

/*
 *
 */
static void
draw_score( SDL_Color *c ) {
  int fw, fh;
  int offset = 20;
  get_string_size( "Score:", "res/fonts/nes.ttf", 12, &fw, &fh );
  int v_offset = offset + fh + 5;

  // Draw score label.
  draw_text( SCREEN_WIDTH - fw - offset, offset, c->r, c->g, c->b, "res/fonts/nes.ttf", 12,
             "Score:" );

  // Draw numeric score.
  draw_text( SCREEN_WIDTH - fw - offset, v_offset, 0xff, 0xff, 0xff, "res/fonts/nes.ttf", 12, "%d",
             stage.score );
}

/*
 *
 */
static void
draw_level_number() {
  int fw, fh;

  char level_data[MAX_BUFFER_SIZE];
  char number_buffer[3];

  itoa( stage.level_id, number_buffer, 10 );
  strcpy( level_data, "< LEVEL " );
  char *level_string = strcat( level_data, number_buffer );
  strcat( level_data, " >" );

  get_string_size( level_data, "res/fonts/nes.ttf", 24, &fw, &fh );
  draw_text( ( SCREEN_WIDTH / 2 ) - ( fw / 2 ), ( SCREEN_HEIGHT >> 1 ) + ( SCREEN_HEIGHT / 5 ),
             0xff, 0xff, 0xff, "res/fonts/nes.ttf", 24, level_data );
}