//=============================================================================================//
// FILENAME :       init.c
//
// DESCRIPTION :
//        Defines the procedures and functions for the SDL context.
//
// NOTES :
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.
//
// AUTHOR :   Joshua Crotts        START DATE :    17 Jun 2020
//
//=============================================================================================//

#include "../include/init.h"

struct app_t app;

static void Stds_InitSDL( const char *, const uint32_t ww, const uint32_t wh, const uint32_t lw,
                          const uint32_t lh );
static void Stds_InitAudioContext( void );
static void Stds_Cleanup( void );

/**
 * Calls the remainder of the initialization functions, and
 * sets up the game loop structure.
 *
 * @param const char *window title.
 * @param uint32_t window width.
 * @param uint32_t window height.
 * @param uint32_t level or width that the camera cannot exceed.
 * @param uint32_t level or height that the camera cannot exceed.
 *
 * @return void.
 */
void
Stds_InitGame( const char *window_name, const uint32_t window_width, const uint32_t window_height,
               const uint32_t level_width, const uint32_t level_height ) {
  Stds_InitSDL( window_name, window_width, window_height, level_width, level_height );
  Stds_InitSounds();
  Stds_InitFonts();

  app.original_title = window_name;
  app.is_running     = true;

  /* Assigns the callback function to clean up the
    SDL context when closing the program. */
  atexit( Stds_Cleanup );
}

/**
 * Toggles debug mode either on or off. When on, debug messages
 * are Stds_Printed to the console.
 *
 * @param bool true for debug mode on, false otherwise.
 *
 * @return void.
 */
void
Stds_ToggleDebugMode( bool db ) {
  app.is_debug_mode = db;
  if ( app.is_debug_mode ) {
    SDL_LogSetPriority( SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG );
  } else {
    SDL_LogSetPriority( SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO );
  }
}

/**
 * Initializes the SDL context, renderer, and window.
 *
 * @param const char * window name.
 * @param uint32_t window_width.
 * @param uint32_t window height.
 * @param uint32_t width of level (how far the camera is scrolled).
 * @param uint32_t height of level (how far the camera is scrolled).
 *
 * @return void.
 */
static void
Stds_InitSDL( const char *window_name, const uint32_t window_width, const uint32_t window_height,
              const uint32_t level_width, const uint32_t level_height ) {
  int8_t renderer_flags;
  int8_t window_flags;
  renderer_flags = SDL_RENDERER_ACCELERATED;
  window_flags   = 0;

  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Initialization of SDL started." );

  memset( &app, 0, sizeof( struct app_t ) );
  app.SCREEN_WIDTH  = window_width;
  app.SCREEN_HEIGHT = window_height;
  app.LEVEL_WIDTH   = level_width;
  app.LEVEL_HEIGHT  = level_height;

  /* Initialize SDL and exit if we fail. */
  if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
    Stds_Print( "Could not initialize SDL: %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Initializing window." );

  /* Initialize the SDL window. */
  app.window = SDL_CreateWindow( window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                 window_width, window_height, window_flags );
  if ( !app.window ) {
    Stds_Print( "Could not open window. %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "nearest" );

  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Creating SDL renderer." );

  /* Create renderer with the default graphics context. */
  app.renderer = SDL_CreateRenderer( app.window, -1, renderer_flags );
  if ( !app.renderer ) {
    Stds_Print( "Failed to initialize renderer: %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Initialization Completed." );

  /* Initialize SDL to accept both JPG and PNGs. */
  IMG_Init( IMG_INIT_PNG | IMG_INIT_JPG );

  /*  Remove cursor. */
  SDL_ShowCursor( true );

  Stds_InitAudioContext();
  Stds_SetRandomSeed();
}

/**
 * Closes the SDL mixer/audio and subsystem components. This function
 * should not be called by the user; rather it is called by the input.c
 * file when a close event is encountered.
 *
 * @param void.
 *
 * @return void.
 */
void
Stds_Quit( void ) {
  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Freeing SDL Mixer context." );
  Mix_Quit();
  Mix_CloseAudio();

  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Quitting SDL." );
  SDL_QuitSubSystem( SDL_INIT_EVERYTHING );
  SDL_Quit();
}

/**
 * Initializes the SDL audio context, and allocates the necessary
 * memory for the number of channels allowed by Standards.
 *
 * @param void.
 *
 * @return void.
 */
static void
Stds_InitAudioContext( void ) {
  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Initializing audio context and SDL Mixer." );

  if ( Mix_OpenAudio( 44100, AUDIO_S16SYS, 2, 1024 ) == -1 ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL Mixer.\n" );
    exit( EXIT_FAILURE );
  }

  Mix_AllocateChannels( MAX_SND_CHANNELS );
}

/**
 * Cleans up the SDL context and game upon closing the application.
 *
 * @param void.
 *
 * @return void.
 */
static void
Stds_Cleanup( void ) {
  app.is_running = false;

  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Cleaning up." );
  SDL_DestroyRenderer( app.renderer );
  SDL_DestroyWindow( app.window );

  /* Free the memory of the linked lists defined by
     the app struct. */
  struct parallax_background_t *pbg;
  struct texture_t *            t;
  struct button_t *             b;
  struct trail_t *              tr;

  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Freeing parallax backgrounds." );
  /* Frees the parallax background linked list. */
  while ( app.parallax_head.next ) {
    pbg                    = app.parallax_head.next;
    app.parallax_head.next = pbg->next;
    Stds_BackgroundDie( pbg->background );
    free( pbg );
  }

  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Freeing textures." );
  /* Frees the texture linked list. */
  while ( app.texture_head.next ) {
    t                     = app.texture_head.next;
    app.texture_head.next = t->next;
    free( t );
  }

  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Freeing trails." );
  /* Frees the trail linked list. */
  while ( app.trail_head.next ) {
    tr                  = app.trail_head.next;
    app.trail_head.next = tr->next;
    free( tr );
  }

  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Freeing buttons." );
  /* Frees the button linked list. */
  while ( app.button_head.next ) {
    b                    = app.button_head.next;
    app.button_head.next = b->next;
    free( b );
  }

  Stds_FreeFonts();
}
