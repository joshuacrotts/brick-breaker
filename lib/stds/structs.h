#ifndef STRUCTS_H
#define STRUCTS_H

#include "stds.h"

typedef struct Delegate Delegate;
typedef struct Entity Entity;
typedef struct Mouse Mouse;
typedef struct Entity Entity;
typedef struct App App;

struct Delegate {
  void (*tick)(void);
  void (*draw)(void);
};

struct Mouse {
  int x;
  int y;
  int button[MAX_MOUSE_BUTTONS];
  int wheel;
};

struct App{
  SDL_Renderer *renderer;
  SDL_Window *window;
  Mouse mouse;

  SDL_Point camera;
  Delegate delegate;
  int keyboard[MAX_KEYBOARD_KEYS];
};

// Update this as needed.
struct Entity {
  float x;
  float y;
  float dx;
  float dy;

  int w;
  int h;
  int health;
  int angle;
  int weaponType;
  int reload;
  int side;
  int radius;

  SDL_Color color;
  SDL_Texture* texture;
  Entity* next;

  void (*tick)(void);
  void (*touch)(Entity* other);
  void (*die)(void);
};

#endif
