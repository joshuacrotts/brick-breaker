#include "main.h"

static void capFrameRate(long*, float*);

int main(int argc, char *argv[]) {
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Setup started.\n");
  memset(&app, 0, sizeof(App));

  long then;
  float remainder;

  initSDL();
  initSounds();
  initFonts();
  initStage();

  // Assigns the callback function to clean up the
  // SDL context when closing the program.
  atexit(cleanup);

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

  return 0;
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
