#include "game.h"

static uint16_t currentFPS;

static void capFrameRate(long*, float*);
uint32_t updateWindowTitle(uint32_t, void*);

void loop() {
  long timer;
  long then;
  float remainder;

  then = SDL_GetTicks();
  remainder = 0;

  SDL_AddTimer(WINDOW_UPDATE_TIMER, updateWindowTitle, &currentFPS);

  // Main game loop.
  while (true) {
    prepareScene();
    processInput();
    app.delegate.tick();
    app.delegate.draw();
    presentScene();
    capFrameRate(&then, &remainder);
  }
}

/*
 *
 */
static void capFrameRate(long* then, float* remainder) {
  long wait, frameTime;

  wait = (int32_t) (16 + *remainder);
  *remainder -= (int)*remainder;
  frameTime = SDL_GetTicks() - *then;
  wait -= frameTime;
  if (wait < 1) {
    wait = 1;
  }
  
  SDL_Delay(wait);

  currentFPS = 1000 / wait;
  *remainder += (0.667f);
  *then = SDL_GetTicks();
}

/*
 *
 */
uint32_t updateWindowTitle(uint32_t interval, void* args) {
  uint16_t fps = *(uint16_t*) args;
  // Create text window buffer.
  char windowBuffer[SMALL_TEXT_BUFFER];

  // Buffer for FPS string representation.
  char numBuffer[3];

  // Convert fps to string - store in numBuffer.
  itoa(fps, numBuffer, 10);

  // Create temp variable for title.
  char* title = "Standards C Library - FPS: ";

  // Move temp var to buffer. Receive ptr.
  strcpy(windowBuffer, title);

  // Concatenate number to title variable.
  strcat(windowBuffer, numBuffer);

  SDL_SetWindowTitle(app.window, windowBuffer);

  memset(numBuffer, '\0', sizeof(numBuffer));
  memset(windowBuffer, '\0', sizeof(windowBuffer));

  return interval;
}