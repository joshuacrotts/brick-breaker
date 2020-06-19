#include "../include/input.h"

static int16_t previousFrameKey = -1;

static void keyPressed(SDL_KeyboardEvent*);
static void keyReleased(SDL_KeyboardEvent*);
static void mousePressed(SDL_MouseButtonEvent*);
static void mouseReleased(SDL_MouseButtonEvent*);

void processInput(void) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
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
      case SDL_MOUSEBUTTONDOWN:
        mousePressed(&event.button);
        break;
      case SDL_MOUSEBUTTONUP:
        mouseReleased(&event.button);
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

/*
 *
 */
static void mousePressed(SDL_MouseButtonEvent* event) {
  app.mouse.button[event->button] = 1;
}

/*
 *
 */
static void mouseReleased(SDL_MouseButtonEvent* event) {
  app.mouse.button[event->button] = 0;
}
