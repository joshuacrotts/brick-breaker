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

  SDL_Rect screenBounds;
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

  //  Directional velocity (yes, I know it's redundant).
  float dx;
  float dy;

  //  Acceleration or deceleration factors.
  float deltaAccelX;
  float deltaAccelY;

  // Change rate of alpha value.
  float deltaAlpha;

  // Size of entity if not defined by a rectangle. These
  // should either be set manually, or defined by a call
  // to SDL_QueryTexture(...), where you pass the addresses
  // of these variables.
  uint32_t w;
  uint32_t h;
  uint32_t flags;
  uint32_t idFlags;
  uint32_t reload;

  uint16_t health;
  uint16_t angle;
  uint16_t radius;

  int32_t life;

  SDL_Color color;
  SDL_Texture* texture;
  Entity* next;

  void (*tick)(Entity* other);
  void (*draw)(Entity* other);
  void (*touch)(Entity* other);
  void (*die)(Entity* other);
};

#endif
