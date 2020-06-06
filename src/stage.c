#include "stage.h"

static void tick(void);
static void draw(void);

/*
 *
 */
void initStage(void) {
  app.delegate.tick = tick;
  app.delegate.draw = draw;

  memset(&stage, 0, sizeof(Stage));
}

/*
 *
 */
static void tick(void) {

}

/*
 *
 */
static void draw(void) {

}
