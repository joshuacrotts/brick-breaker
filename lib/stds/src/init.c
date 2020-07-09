//=============================================================================================//
// FILENAME :       init.c
//
// DESCRIPTION :
//        Defines the procedures and functions for the SDL context.
//
// PUBLIC FUNCTIONS :
//        void        init_game( const char *, uint32_t, uint32_t, uint32_t, uint32_t );
//        void        toggle_debug_mode( bool );
//
// PRIVATE/STATIC FUNCTIONS :
//        void        init_SDL( const char *, uint32_t, uint32_t, uint32_t, uint32_t );
//        void        init_audio_context( void );
//        void        cleanup( void );
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

static bool debug_mode = false;

static void init_SDL( const char *, uint32_t, uint32_t, uint32_t, uint32_t );
static void init_audio_context( void );
static void cleanup( void );

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
init_game( const char *window_name, uint32_t window_width, uint32_t window_height,
           uint32_t level_width, uint32_t level_height ) {
  init_SDL( window_name, window_width, window_height, level_width, level_height );
  init_sounds();
  init_fonts();

  app.original_title = window_name;

  // Assigns the callback function to clean up the
  // SDL context when closing the program.
  atexit( cleanup );
}

/**
 * Toggles debug mode either on or off. When on, debug messages
 * are printed to the console.
 *
 * @param bool true for debug mode on, false otherwise.
 *
 * @return void.
 */
void
toggle_debug_mode( bool db ) {
  debug_mode = db;
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
init_SDL( const char *window_name, uint32_t window_width, uint32_t window_height,
          uint32_t level_width, uint32_t level_height ) {
  int8_t renderer_flags;
  int8_t window_flags;
  renderer_flags = SDL_RENDERER_ACCELERATED;
  window_flags   = 0;

  if ( debug_mode ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Initialization of SDL started." );
  }

  memset( &app, 0, sizeof( app_t ) );
  app.SCREEN_WIDTH  = window_width;
  app.SCREEN_HEIGHT = window_height;
  app.LEVEL_WIDTH   = level_width;
  app.LEVEL_HEIGHT  = level_height;

  // Initialize SDL and exit if we fail.
  if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s.\n", SDL_GetError() );
    exit( EXIT_ERROR );
  }

  if ( debug_mode ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Initializing window." );
  }

  // Initialize the SDL window.
  app.window = SDL_CreateWindow( window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                 window_width, window_height, window_flags );
  if ( !app.window ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not open window. %s.\n", SDL_GetError() );
    exit( EXIT_ERROR );
  }

  SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "nearest" );

  if ( debug_mode ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Creating SDL renderer." );
  }

  // Create renderer with the default graphics context.
  app.renderer = SDL_CreateRenderer( app.window, -1, renderer_flags );
  if ( !app.renderer ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize renderer: %s.\n",
                 SDL_GetError() );
    exit( EXIT_ERROR );
  }

  if ( debug_mode ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Initialization Completed." );
  }

  //  Initialize SDL to accept both JPG and PNGs.
  IMG_Init( IMG_INIT_PNG | IMG_INIT_JPG );

  //  Remove cursor.
  SDL_ShowCursor( true );

  init_audio_context();
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
init_audio_context( void ) {
  if ( debug_mode ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Initializing audio context and SDL Mixer." );
  }

  if ( Mix_OpenAudio( 44100, AUDIO_S16SYS, 2, 1024 ) == -1 ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL Mixer.\n" );
    exit( EXIT_ERROR );
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
cleanup( void ) {
  if ( debug_mode ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Cleaning up." );
  }

  SDL_DestroyRenderer( app.renderer );
  SDL_DestroyWindow( app.window );

  // Free the memory of the linked lists defined by
  // the app struct.
  parallax_background_t *pbg;
  texture_t *            t;
  button_t *             b;
  trail_t *              tr;

  if ( debug_mode ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Freeing parallax backgrounds." );
  }

  /* Frees the parallax background linked list. */
  while ( app.parallax_head.next ) {
    pbg                    = app.parallax_head.next;
    app.parallax_head.next = pbg->next;
    free( pbg );
  }

  if ( debug_mode ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Freeing textures." );
  }

  /* Frees the texture linked list. */
  while ( app.texture_head.next ) {
    t                     = app.texture_head.next;
    app.texture_head.next = t->next;
    free( t );
  }

  if ( debug_mode ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Freeing trails." );
  }

  /* Frees the trail linked list. */
  while ( app.trail_head.next ) {
    tr                  = app.trail_head.next;
    app.trail_head.next = tr->next;
    free( tr );
  }

  if ( debug_mode ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Freeing buttons." );
  }

  /* Frees the button linked list. */
  while ( app.button_head.next ) {
    b                    = app.button_head.next;
    app.button_head.next = b->next;
    free( b );
  }

  free_fonts();
  SDL_Quit();

  if ( debug_mode ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Program quit." );
  }
}
