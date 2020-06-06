#include "input.h"

static int previousFrameKey = -1;

/*
 * Starts the SDL event loop.
 */
void processInput(void) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        exit(EXIT_SUCCESS);
        break;
      case SDL_KEYDOWN:
        keyPressed(&event.key);
        break;
      case SDL_KEYUP:
        keyReleased(&event.key);
        break;
      default:
        break;
    }
  }
}

/*
 *
 */
static void keyPressed(SDL_KeyboardEvent* event) {
  if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
    app.keyboard[event->keysym.scancode] = 1;
  }
}

/*
 *
 */
static void keyReleased(SDL_KeyboardEvent* event) {
  if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
    app.keyboard[event->keysym.scancode] = 0;
  }
}
