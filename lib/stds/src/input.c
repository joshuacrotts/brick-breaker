#include "../include/input.h"

static int16_t previous_frame_key = -1;

static void key_pressed(SDL_KeyboardEvent*);
static void key_released(SDL_KeyboardEvent*);
static void mouse_pressed(SDL_MouseButtonEvent*);
static void mouse_released(SDL_MouseButtonEvent*);


void 
process_input(void) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
    switch (event.type) {
      case SDL_QUIT:
        exit(EXIT_SUCCESS);
        break;
      case SDL_KEYDOWN:
        key_pressed(&event.key);
        break;
      case SDL_KEYUP:
        key_released(&event.key);
        break;
      case SDL_MOUSEBUTTONDOWN:
        mouse_pressed(&event.button);
        break;
      case SDL_MOUSEBUTTONUP:
        mouse_released(&event.button);
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
key_pressed(SDL_KeyboardEvent *event) {
  if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
    app.keyboard[event->keysym.scancode] = 1;
  }
}


/*
 *
 */
static void 
key_released(SDL_KeyboardEvent *event) {
  if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
    app.keyboard[event->keysym.scancode] = 0;
  }
}


/*
 *
 */
static void 
mouse_pressed(SDL_MouseButtonEvent *event) {
  app.mouse.button[event->button] = 1;
}


/*
 *
 */
static void 
mouse_released(SDL_MouseButtonEvent *event) {
  app.mouse.button[event->button] = 0;
}
