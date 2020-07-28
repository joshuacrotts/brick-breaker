#ifndef STRUCTS_H
#define STRUCTS_H

#include "stds.h"

/*
 *
 */
struct circle_t {
  float center_x;
  float center_y;
  float radius;
};

/*
 *
 */
struct button_t {
  const char *text;
  const char *font_path;
  bool        is_filled;

  uint8_t  texture_id;
  int32_t  text_x;
  int32_t  text_y;
  uint16_t font_size;
  float    scale_x;
  float    scale_y;

  SDL_Texture *texture[TEXTURE_BUFFER_SIZE];
  SDL_Color    color;
  SDL_Color    text_color;
  SDL_Rect     rect;

  struct button_t *next;
};

/*
 *
 */
struct particle_t {
  float    x;
  float    y;
  float    dx;
  float    dy;
  float    delta_accel_x;
  float    delta_accel_y;
  float    delta_alpha;
  int32_t  w;
  int32_t  h;
  uint32_t angle;
  int32_t  life;
  uint32_t id_flags;
  uint32_t flags;

  SDL_Color    color;
  SDL_Texture *current_texture;

  struct animation_t *animation;

  void ( *particle_update )( struct particle_t * );
  void ( *particle_draw )( struct particle_t * );
};

/**
 *
 */
struct grid_t {
  float x;
  float y;

  float sx;
  float sy;

  int32_t sw;
  int32_t sh;

  uint32_t cols;
  uint32_t rows;

  SDL_Color line_color;
  SDL_Color fill_color;

  /* Members for having textures */
  SDL_Texture **textures;
  int32_t       texture_buffer;

  /* Members for having a spriteSheet */
  SDL_Texture *sprite_sheet;
  SDL_Rect     clip;
  uint32_t     sprite_sheet_cols;
  uint32_t     sprite_sheet_rows;

  struct stds_vector_t *animation;
  int32_t               animation_buffer;

  /* This bool will determine if we scroll the grid
     (and its children sprites) with the camera. If false,
     the grid will always stay in the frame of the player.
     If true, it scrolls it. */
  bool is_camera_offset_enabled;
};

/*
 *
 */
struct particle_system_t {
  int32_t alive_count;
  int32_t dead_index;
  int32_t max_particles;

  struct particle_t *particles;
};

/*
 *
 */
struct parallax_background_t {
  float parallax_scroll_speed;
  float normal_scroll_speed;
  bool  infinite_scroll;

  struct background_t *         background;
  struct parallax_background_t *next;
};

/*
 *
 */
struct trail_t {
  float x;
  float y;

  /* For rectangular trails. */
  int32_t w;
  int32_t h;

  /* For circle trails. */
  int32_t r;

  int16_t  alpha;
  int16_t  alpha_decay_rate;
  uint32_t angle;
  uint32_t flags;

  SDL_RendererFlip flip;
  SDL_Color        color;
  SDL_Texture *    texture;

  struct trail_t *next;
};

/*
 *
 */
struct animation_t {
  float    pos_x;
  float    pos_y;
  float    scale_x;
  float    scale_y;
  float    frame_delay;
  float    frame_timer;
  uint32_t splice_x;
  uint32_t splice_y;
  uint32_t id_flags;
  uint32_t flags;
  uint16_t angle;
  uint16_t start_x;
  uint16_t start_y;
  int32_t  sprite_width;
  int32_t  sprite_height;
  int32_t  dest_width;
  int32_t  dest_height;
  int32_t  sprite_sheet_width;
  int32_t  sprite_sheet_height;
  uint8_t  current_frame_id;
  uint8_t  current_frame_row_id;
  uint8_t  current_frame_col_id;
  size_t   number_of_frames;
  size_t   rows_count;
  size_t   cols_count;

  bool is_camera_offset_enabled;
  bool is_cycle_once;

  SDL_RendererFlip flip;

  SDL_Texture * current_texture;
  SDL_Texture * default_texture;
  SDL_Texture **frames;
  SDL_Texture * sprite_sheet;

  struct animation_t *next;
};

/*
 *
 */
struct background_t {
  float   x;
  float   y;
  float   scroll_x;
  float   scroll_y;
  float   scale_x;
  float   scale_y;
  int32_t w;
  int32_t h;

  SDL_Texture *background_texture;
};

/*
 *
 */
struct texture_t {
  char name[MAX_FILE_NAME_LEN];

  SDL_Texture *texture;

  struct texture_t *next;
};

/*
 *
 */
struct font_t {
  char     name[MAX_FILE_NAME_LEN];
  uint16_t size;

  TTF_Font *font;

  struct font_t *next;
};

/*
 *
 */
struct delegate_t {
  void ( *update )( void );
  void ( *draw )( void );
};

/*
 *
 */
struct mouse_t {
  int32_t x;
  int32_t y;
  uint8_t button[MAX_MOUSE_BUTTONS];
  uint8_t wheel;
  bool    is_moving;
};

/*
 *
 */
struct app_t {
  uint16_t keyboard[MAX_KEYBOARD_KEYS];

  uint32_t SCREEN_WIDTH;
  uint32_t SCREEN_HEIGHT;
  uint32_t LEVEL_WIDTH;
  uint32_t LEVEL_HEIGHT;

  bool        is_debug_mode;
  bool        is_running;
  const char *original_title;

  SDL_Renderer *renderer;
  SDL_Window *  window;
  SDL_FRect     screen_bounds;
  SDL_FRect     camera;

  struct mouse_t               mouse;
  struct delegate_t            delegate;
  struct trail_t               trail_head, *trail_tail;
  struct texture_t             texture_head, *texture_tail;
  struct font_t                font_head, *font_tail;
  struct parallax_background_t parallax_head, *parallax_tail;
  struct button_t              button_head, *button_tail;

  enum GameState game_state;
};

/*
 *
 */
struct fade_color_t {
  bool  is_first_color;
  float alpha;
  float time;

  SDL_Color c1;
  SDL_Color c2;
};

/*
 *
 */
struct entity_t {
  float x;
  float y;

  /* Miscellaneous positioning variable. */
  float variability;

  /* Scales the entity in either the x or y
     direction. This should default to 1. */
  float scale_x;
  float scale_y;

  /* Directional velocity (yes, I know it's redundant). */
  float dx;
  float dy;

  /* Acceleration or deceleration factors. */
  float delta_accel_x;
  float delta_accel_y;

  /* Change rate of alpha value. */
  float delta_alpha;

  /* Size of entity if not defined by a rectangle. These
     should either be set manually, or defined by a call
     to SDL_QueryTexture(...), where you pass the addresses
     of these variables. */
  int32_t  w;
  int32_t  h;
  uint32_t flags;
  uint32_t id_flags;
  int32_t  reload;
  uint32_t identifier;

  uint16_t angle;
  uint16_t radius;

  /* Can be used interchangably for different purposes. */
  int32_t health;
  int32_t life;

  SDL_Color    color;
  SDL_Texture *texture[TEXTURE_BUFFER_SIZE];

  struct animation_t *animation;
  struct entity_t *   next;

  void ( *update )( struct entity_t * );
  void ( *draw )( struct entity_t * );
  void ( *touch )( struct entity_t * );
  void ( *die )( struct entity_t * );
};

#endif // STRUCTS_H
