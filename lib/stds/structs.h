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
  int32_t x;
  int32_t y;
  uint8_t button[MAX_MOUSE_BUTTONS];
  uint8_t wheel;
};

struct App{
  SDL_Renderer *renderer;
  SDL_Window *window;
  Mouse mouse;

  SDL_Point camera;
  Delegate delegate;
  uint16_t keyboard[MAX_KEYBOARD_KEYS];
};

// Update this as needed.
struct Entity {
  float x;
  float y;

  // Scales the entity in either the x or y
  // direction. This should default to 1.
  float scaleX;
  float scaleY;
  float dx;
  float dy;

  uint32_t w;
  uint32_t h;
  uint16_t health;
  uint16_t angle;
  uint16_t radius;
  uint16_t flags;
  uint32_t reload;

  SDL_Color color;
  SDL_Texture* texture;
  Entity* next;

  void (*tick)(void);
  void (*touch)(Entity* other);
  void (*die)(void);
};

#endif
