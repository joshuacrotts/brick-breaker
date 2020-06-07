#include "game.h"

static void capFrameRate(long*, float*);

void loop() {
  long then;
  float remainder;

  then = SDL_GetTicks();
  remainder = 0;

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

  wait = 16 + *remainder;
  *remainder -= (int)*remainder;
  frameTime = SDL_GetTicks() - *then;
  wait -= frameTime;

  if (wait < 1) {
    wait = 1;
  }

  SDL_Delay(wait);

  *remainder += (0.667);

  *then = SDL_GetTicks();
}
