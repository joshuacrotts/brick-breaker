#include "SDL2/SDL.h"
#define MAX_KEYBOARD_KEYS   350

typedef struct Delegate {
  void (*tick)(void);
  void (*draw)(void);
} Delegate;

typedef struct App{
  SDL_Renderer *renderer;
  SDL_Window *window;

  Delegate delegate;
  int keyboard[MAX_KEYBOARD_KEYS];

} App;

typedef struct Stage {

} Stage;
