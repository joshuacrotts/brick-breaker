#ifndef STRUCTS_H
#define STRUCTS_H

#include "stds.h"

typedef        float              f32;

typedef struct Delegate           delegate_t;
typedef struct Entity             entity_t;
typedef struct Mouse              mouse_t;
typedef struct App                app_t;
typedef struct Animation          animation_t;
typedef struct Texture            texture_t;
typedef struct FadeColor          fade_color_t;
typedef struct Background         background_t;
typedef struct ParallaxBackground parallax_background_t;
typedef struct Font               font_t;
typedef struct Trail              trail_t;
typedef struct Circle             circle_t;
typedef struct Button             button_t;
typedef struct ParticleSystem     particle_system_t;
typedef struct Particle           particle_t;

/*
 *
 */
struct Circle {
    f32  center_x;
    f32  center_y;
    f32  radius;
};

/*
 *
 */
struct Button {
  const char *text;
  const char *font_path;
  bool        is_filled;

  uint8_t  texture_id;
  int32_t  text_x;
  int32_t  text_y;
  uint16_t font_size;
  f32    scale_x;
  f32    scale_y;

  SDL_Texture *texture[TEXTURE_BUFFER_SIZE];
  SDL_Color    color;
  SDL_Color    text_color;
  SDL_Rect     rect;

  button_t *next;
};

/*
 *
 */
struct Particle {
  f32    x;
  f32    y;
  f32    dx;
  f32    dy;
  f32    delta_accel_x;
  f32    delta_accel_y;
  f32    delta_alpha;
  int32_t w;
  int32_t h;
  uint32_t angle;
  int32_t  life;
  uint32_t id_flags;
  uint32_t flags;

  SDL_Color    color;
  SDL_Texture *current_texture;

  animation_t *animation;

  void ( *particle_update )( particle_t * );
  void ( *particle_draw )( particle_t * );
};

/*
 *
 */
struct ParticleSystem {
  int32_t alive_count;
  int32_t dead_index;
  int32_t max_particles;

  particle_t *particles;
};

/*
 *
 */
struct ParallaxBackground {
  f32   parallax_scroll_speed;
  f32   normal_scroll_speed;
  bool  infinite_scroll;

  background_t *         background;
  parallax_background_t *next;
};

/*
 *
 */
struct Trail {
  f32      x;
  f32      y;
  int16_t  alpha;
  int16_t  alpha_decay_rate;
  uint32_t flags;
  bool     is_texture;

  SDL_RendererFlip flip;
  SDL_Texture      *texture;

  trail_t *next;
};

/*
 *
 */
struct Animation {
  f32      pos_x;
  f32      pos_y;
  f32      frame_delay;
  f32      frame_timer;
  uint32_t splice_x;
  uint32_t splice_y;
  uint32_t id_flags;
  uint32_t flags;
  uint16_t angle;
  uint16_t start_x;
  uint16_t start_y;
  int32_t  w;
  int32_t  h;
  int32_t  sprite_sheet_width;
  int32_t  sprite_sheet_height;
  uint8_t  current_frame_id;
  size_t   number_of_frames;

  bool     cycle_once;

  SDL_RendererFlip flip;

  SDL_Texture * current_texture;
  SDL_Texture * default_texture;
  SDL_Texture **frames;
  SDL_Texture * sprite_sheet;

  animation_t *next;
};

/*
 *
 */
struct Background {
  f32 x;
  f32 y;
  f32 scroll_x;
  f32 scroll_y;
  f32 scale_x;
  f32 scale_y;

  int32_t w;
  int32_t h;

  SDL_Texture *background_texture;
};

/*
 *
 */
struct Texture {
  char name[MAX_FILE_NAME_LEN];

  SDL_Texture *texture;

  texture_t *next;
};

/*
 *
 */
struct Font {
  char     name[MAX_FILE_NAME_LEN];
  uint16_t size;

  TTF_Font *font;
  font_t *  next;
};

/*
 *
 */
struct Delegate {
  void ( *tick )( void );
  void ( *draw )( void );
};

/*
 *
 */
struct Mouse {
  int32_t x;
  int32_t y;
  uint8_t button[MAX_MOUSE_BUTTONS];
  uint8_t wheel;
};

/*
 *
 */
struct App {
  uint16_t keyboard[MAX_KEYBOARD_KEYS];

  uint32_t    SCREEN_WIDTH;
  uint32_t    SCREEN_HEIGHT;
  uint32_t    LEVEL_WIDTH;
  uint32_t    LEVEL_HEIGHT;
  const char *original_title;

  SDL_Renderer   *renderer;
  SDL_Window     *window;
  SDL_FRect      screen_bounds;
  SDL_FRect      camera;

  mouse_t               mouse;
  delegate_t            delegate;
  trail_t               trail_head, *trail_tail;
  texture_t             texture_head, *texture_tail;
  font_t                font_head, *font_tail;
  parallax_background_t parallax_head, *parallax_tail;
  button_t              button_head, *button_tail;

  enum GameState game_state;
};

/*
 *
 */
struct FadeColor {
  bool is_first_color;
  f32  alpha;
  f32  time;

  SDL_Color c1;
  SDL_Color c2;
};

/*
 *
 */
struct Entity {
  f32 x;
  f32 y;

  //  Miscellaneous positioning variable.
  f32 variability;

  // Scales the entity in either the x or y
  // direction. This should default to 1.
  f32 scale_x;
  f32 scale_y;

  //  Directional velocity (yes, I know it's redundant).
  f32 dx;
  f32 dy;

  //  Acceleration or deceleration factors.
  f32 delta_accel_x;
  f32 delta_accel_y;

  // Change rate of alpha value.
  f32 delta_alpha;

  // Size of entity if not defined by a rectangle. These
  // should either be set manually, or defined by a call
  // to SDL_QueryTexture(...), where you pass the addresses
  // of these variables.
  int32_t  w;
  int32_t  h;
  uint32_t flags;
  uint32_t id_flags;
  uint32_t reload;
  uint32_t identifier;

  uint16_t angle;
  uint16_t radius;

  // Can be used interchangably for different purposes.
  int32_t health;
  int32_t life;

  SDL_Color    color;
  SDL_Texture *texture[TEXTURE_BUFFER_SIZE];

  animation_t *animation;
  entity_t *   next;

  void ( *tick )( entity_t * );
  void ( *draw )( entity_t * );
  void ( *touch )( entity_t * );
  void ( *die )( entity_t * );
};

#endif // STRUCTS_H
