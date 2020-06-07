#include "main.h"

static void initScene(void);
static void draw(void);
static void tick(void);

// Barebones game. This is the minimum amount of code
// necessary to run a window.
int main(int argc, char* argv[]) {
  initGame("Standards C Library11", SCREEN_WIDTH, SCREEN_HEIGHT);
  initScene();
  loop();

  return 0;
}

/*
 * Initializes the delegation structure to use the
 * tick and draw methods for rendering and updating
 * the game. These methods must be defined because the
 * delegation structure uses them in the loop function.
 */
static void initScene(void) {
  app.delegate.tick = tick;
  app.delegate.draw = draw;
}

static void tick(void) {

}

static void draw(void) {

}
