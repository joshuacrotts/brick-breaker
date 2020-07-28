//=============================================================================================//
// FILENAME :       input.c
//
// DESCRIPTION :
//        This file defines input handling. As of now, it only supports mouse and keyboard input.
//        Controller support may come at a future date.
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

#include "../include/input.h"

static int16_t previous_frame_key = -1;

static inline void Stds_UpdateMouseState( void );
static inline void Stds_KeyPressed( const SDL_KeyboardEvent * );
static inline void Stds_KeyReleased( const SDL_KeyboardEvent * );
static inline void Stds_MousePressed( const SDL_MouseButtonEvent * );
static inline void Stds_MouseReleased( const SDL_MouseButtonEvent * );
static inline void Stds_MouseMoved( const SDL_MouseMotionEvent * );

/**
 * Starts the SDL event loop.
 *
 * @param void.
 *
 * @return void.
 */
void
Stds_ProcessInput( void ) {
  SDL_Event event;

  while ( SDL_PollEvent( &event ) ) {
    Stds_UpdateMouseState();

    switch ( event.type ) {
    case SDL_QUIT:
      SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Quit event." );
      Stds_Quit();
      exit( EXIT_SUCCESS );
      break;
    case SDL_KEYDOWN:
      Stds_KeyPressed( &event.key );
      break;
    case SDL_KEYUP:
      Stds_KeyReleased( &event.key );
      break;
    case SDL_MOUSEBUTTONDOWN:
      Stds_MousePressed( &event.button );
      break;
    case SDL_MOUSEBUTTONUP:
      Stds_MouseReleased( &event.button );
      break;
    case SDL_MOUSEWHEEL:
      app.mouse.wheel = event.wheel.y;
      break;
    case SDL_MOUSEMOTION:
      Stds_MouseMoved( &event.motion );
    default:
      break;
    }
  }
}

/**
 *
 *
 * @param void.
 *
 * @return void.
 */
static inline void
Stds_UpdateMouseState( void ) {
  SDL_GetMouseState( &app.mouse.x, &app.mouse.y );
  app.mouse.is_moving = false;
}

/**
 *
 *
 * @param
 *
 * @return void.
 */
static inline void
Stds_KeyPressed( const SDL_KeyboardEvent *event ) {
  if ( event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS ) {
    app.keyboard[event->keysym.scancode] = 1;
  }
}

/**
 *
 *
 * @param
 *
 * @return void.
 */
static inline void
Stds_KeyReleased( const SDL_KeyboardEvent *event ) {
  if ( event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS ) {
    app.keyboard[event->keysym.scancode] = 0;
  }
}

/**
 *
 *
 * @param
 *
 * @return void.
 */
static inline void
Stds_MousePressed( const SDL_MouseButtonEvent *event ) {
  app.mouse.button[event->button] = 1;
}

/**
 *
 */
static inline void
Stds_MouseReleased( const SDL_MouseButtonEvent *event ) {
  app.mouse.button[event->button] = 0;
}

/**
 *
 */
static inline void
Stds_MouseMoved( const SDL_MouseMotionEvent *e ) {
  app.mouse.is_moving = true;
}