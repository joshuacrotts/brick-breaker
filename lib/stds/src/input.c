//=============================================================================================//
// FILENAME :       input.c
//
// DESCRIPTION :
//        This file defines input handling. As of now, it only supports mouse and keyboard input.
//        Controller support may come at a future date.
//
// PUBLIC FUNCTIONS :
//        void          process_input ( void );
//
//  PRIVATE/STATIC FUNCTIONS:
//        void          key_pressed( SDL_KeyboardEvent * );
//        void          key_released( SDL_KeyboardEvent * );
//        void          mouse_pressed( SDL_MouseButtonEvent * );
//        void          mouse_released( SDL_MouseButtonEvent * );
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

static void key_pressed( SDL_KeyboardEvent * );
static void key_released( SDL_KeyboardEvent * );
static void mouse_pressed( SDL_MouseButtonEvent * );
static void mouse_released( SDL_MouseButtonEvent * );

/*
 * Starts the SDL event loop.
 * 
 * @param void.
 * 
 * @return void.
 */
void
process_input( void ) {
  SDL_Event event;

  while ( SDL_PollEvent( &event ) ) {
    SDL_GetMouseState( &app.mouse.x, &app.mouse.y );
    switch ( event.type ) {
    case SDL_QUIT:
      exit( EXIT_SUCCESS );
      break;
    case SDL_KEYDOWN:
      key_pressed( &event.key );
      break;
    case SDL_KEYUP:
      key_released( &event.key );
      break;
    case SDL_MOUSEBUTTONDOWN:
      mouse_pressed( &event.button );
      break;
    case SDL_MOUSEBUTTONUP:
      mouse_released( &event.button );
      break;
    case SDL_MOUSEWHEEL:
      app.mouse.wheel = event.wheel.y;
      break;
    default:
      break;
    }
  }
}

/*
 *
 */
static void
key_pressed( SDL_KeyboardEvent *event ) {
  if ( event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS ) {
    app.keyboard[event->keysym.scancode] = 1;
  }
}

/*
 *
 */
static void
key_released( SDL_KeyboardEvent *event ) {
  if ( event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS ) {
    app.keyboard[event->keysym.scancode] = 0;
  }
}

/*
 *
 */
static void
mouse_pressed( SDL_MouseButtonEvent *event ) {
  app.mouse.button[event->button] = 1;
}

/*
 *
 */
static void
mouse_released( SDL_MouseButtonEvent *event ) {
  app.mouse.button[event->button] = 0;
}
