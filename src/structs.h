#ifndef STRUCTS_H
#define STRUCTS_H

#include "stds.h"

typedef struct Mouse Mouse;

typedef struct Delegate {
  void (*tick)(void);
  void (*draw)(void);
} Delegate;

typedef struct Mouse {
  int x;
  int y;
} Mouse;

typedef struct App{
  SDL_Renderer *renderer;
  SDL_Window *window;
  Mouse mouse;

  Delegate delegate;
  int keyboard[MAX_KEYBOARD_KEYS];
} App;

typedef struct Stage {

} Stage;

#endif
