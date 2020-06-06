#include "main.h"

int main(int argc, char *argv[]) {
  initGame("Standards in C", SCREEN_WIDTH, SCREEN_HEIGHT);
  initStage();

  loop();

  return 0;
}
