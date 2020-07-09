#ifndef DRAW_H
#define DRAW_H

#include "stds.h"

extern app_t app;

extern void prepare_scene( void );

extern void present_scene( void );

extern void blit_rect( SDL_Texture *texture, SDL_Rect *src, float x, float y, bool camera_offset );

extern void blit_texture( SDL_Texture *texture, float x, float y, bool is_center,
                          bool camera_offset );

extern void blit_texture_rotated( SDL_Texture *texture, float x, float y, uint16_t angle,
                                  SDL_RendererFlip flip, bool camera_offset );
                                  
extern void blit_texture_color_scaled( SDL_Texture *texture, float x, float y, float scale_x,
                                       float scale_y, uint16_t angle, SDL_RendererFlip flip,
                                       SDL_Color *c, bool camera_offset );

extern void blit_texture_scaled( SDL_Texture *texture, float x, float y, float scale_x,
                                 float scale_y, uint16_t angle, SDL_RendererFlip flip,
                                 bool camera_offset );

extern void draw_rect( SDL_Rect *rect, SDL_Color *c, bool is_filled, bool camera_offset );

extern void draw_frect( SDL_FRect *frect, SDL_Color *c, bool is_filled, bool camera_offset );

extern void draw_rect_stroke( int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t thickness,
                              SDL_Color *c, bool camera_offset );

extern void draw_circle( int32_t center_x, int32_t center_y, uint32_t radius, SDL_Color *c );

extern void fill_circle( int32_t center_x, int32_t center_y, uint32_t radius, SDL_Color *c );

extern void draw_line( float x1, float y1, float x2, float y2, SDL_Color *c );

extern SDL_Texture *load_texture( const char *directory );

extern SDL_Color combine_fade_color( fade_color_t *fade_color );

#endif
