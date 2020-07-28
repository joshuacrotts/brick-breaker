#ifndef DRAW_H
#define DRAW_H

#include "stds.h"

extern struct app_t app;

extern void Stds_PrepareScene( void );

extern void Stds_PresentScene( void );

extern void Stds_DrawTexture( SDL_Texture *texture, const float x, const float y, const float w,
                              const float h, const uint16_t angle, const SDL_RendererFlip flip,
                              const SDL_FPoint *rotate_point, const bool camera_offset );

extern void Stds_BlitTexture( SDL_Texture *texture, const SDL_Rect *src, const float x,
                              const float y, const float w, const float h, const uint16_t angle,
                              const SDL_RendererFlip flip, const SDL_FPoint *rotate_point,
                              const bool camera_offset );

extern void Stds_DrawRect( SDL_Rect *rect, const SDL_Color *c, const bool is_filled,
                           const bool camera_offset );

extern void Stds_DrawRectF( SDL_FRect *frect, const SDL_Color *c, const bool is_filled,
                            const bool camera_offset );

extern void Stds_DrawRectStroke( float x, float y, uint32_t w, uint32_t h,
                                 const uint32_t stroke_width, const SDL_Color *c,
                                 const bool camera_offset );

extern void Stds_DrawCircle( const struct circle_t *circle, const SDL_Color *c,
                             const bool is_filled );

extern void Stds_DrawLine( const float x1, const float y1, const float x2, const float y2,
                           const SDL_Color *c );

extern SDL_Texture *Stds_LoadTexture( const char *directory );

extern SDL_Color Stds_CombineFadeColor( struct fade_color_t *fade_color );

#endif // DRAW_H
