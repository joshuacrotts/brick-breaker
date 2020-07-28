//=============================================================================================//
// FILENAME :       game.c
//
// DESCRIPTION :
//        Initializes the game structures and pointers for the linked list
//        structures. The game loop is also initialized here.
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
// AUTHOR :   Joshua Crotts        START DATE :    18 Jun 2020
//
//=============================================================================================//

#include "../include/game.h"

static uint16_t current_fps;

static void     Stds_InitWindowFPS( void );
static void     Stds_CapFramerate( long *, float * );
static uint32_t Stds_UpdateWindowTitle( uint32_t, void * );

/**
 * Initializes the app linked list data structures.
 *
 * @param void.
 *
 * @return void.
 */
void
Stds_InitAppStructures( void ) {
  app.parallax_tail = &app.parallax_head;
  app.texture_tail  = &app.texture_head;
  app.button_tail   = &app.button_head;
  app.trail_tail    = &app.trail_head;
  app.font_tail     = &app.font_head;

  Stds_InitWindowFPS();
}

/**
 * Runs the game loop, processing input and SDL events as close
 * to the target framerate as possible.
 *
 * @param void.
 *
 * @return void.
 */
void
Stds_GameLoop( void ) {
  long  timer;
  long  then;
  float remainder;

  then = SDL_GetTicks();

  /* Main game loop. */
  while ( app.is_running ) {
    Stds_PrepareScene();
    Stds_ProcessInput();
    app.delegate.update();
    app.delegate.draw();
    Stds_PresentScene();
    Stds_CapFramerate( &then, &remainder );
  }
}

/**
 * Enables the SDL timer to continuously draw the current frames
 * per second to the title bar. For some reason, MacOS doesn't play
 * nicely with this setup, so if we're on a Mac, this is disabled.
 *
 * @param void.
 *
 * @return void.
 */
static void
Stds_InitWindowFPS( void ) {
#ifndef __APPLE__
  SDL_AddTimer( WINDOW_UPDATE_TIMER, Stds_UpdateWindowTitle, &current_fps );
#endif
}

/**
 * Halts the framerate to approximately sixty frames
 * per second when possible.
 *
 * @param pointers to the times from the previous iteration,
 *        and remainder.
 *
 * @return void.
 */
static void
Stds_CapFramerate( long *then, float *remainder ) {
  long wait, frame_time;

  wait = ( int32_t )( FPS_TIME + *remainder );
  *remainder -= ( int32_t ) *remainder;
  frame_time = SDL_GetTicks() - *then;
  wait -= frame_time;

  if ( wait < 1 ) {
    wait = 1;
  }

  SDL_Delay( wait );

  current_fps = 1000 / wait;
  *remainder += ( 0.667f );
  *then = SDL_GetTicks();
}

/**
 * Callback function to the SDL_AddTimer function that changes
 * the SDL_Window title to a set value with the FPS concatenated
 * onto the end.
 *
 * @param timer interval, and arguments for concatenating. This
 *        should be the frames per second (integer).
 *
 * @return interval time for callback function.
 */
static uint32_t
Stds_UpdateWindowTitle( uint32_t interval, void *args ) {
  uint16_t fps = *( uint16_t * ) args;
  /* Create text window buffer. */
  char window_buffer[SMALL_TEXT_BUFFER];

  /* Copy the title to the buffer. */
  strcpy( window_buffer, app.original_title );

  /* Move temp var to buffer. Receive ptr. */
  strcat( window_buffer, " | FPS: " );

  /* Concatenate number to title variable. */
  char *title;
  title = Stds_StrCatIntArray( window_buffer, fps );
  SDL_SetWindowTitle( app.window, title );

  return interval;
}
