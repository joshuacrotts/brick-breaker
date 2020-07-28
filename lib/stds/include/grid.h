#ifndef GRID_H
#define GRID_H

#include "stds.h"

extern struct app_t app;

/* Will be the return type for all button related functions (what row and what col). */
struct grid_pair_t {
  int32_t c;
  int32_t r;

  float x;
  float y;
};

extern struct grid_t *Stds_CreateGrid( const float x, const float y, const int32_t square_width,
                                       const int32_t square_height, const uint32_t cols,
                                       const uint32_t rows, const SDL_Color *lineColor,
                                       const SDL_Color *fillColor );

extern struct grid_pair_t Stds_OnGridHover( struct grid_t *grid );

extern struct grid_pair_t Stds_OnGridClicked( struct grid_t *grid, const int32_t mouseCode );

extern int32_t Stds_AddAnimationToGrid( struct grid_t *grid, struct animation_t *animate );

extern int32_t Stds_AddGridTexture( struct grid_t *grid, const char *filePath );

extern void Stds_DrawLineGrid( struct grid_t *grid );

extern void Stds_FillWholeGrid( struct grid_t *grid );

extern void Stds_FreeGrid( struct grid_t *grid );

extern void Stds_InitializeGridTextures( struct grid_t *grid, const int32_t textureBuffer );

extern void Stds_PutGridTexture( struct grid_t *grid, const uint32_t col, const uint32_t row,
                                 const int32_t index, const SDL_RendererFlip flip,
                                 const uint16_t angle );

extern void Stds_AddSpriteSheetToGrid( struct grid_t *grid, const char *filePath,
                                       const uint32_t cols, const uint32_t rows );

extern void Stds_SelectSpriteForGrid( struct grid_t *grid, const uint32_t sheetCol,
                                      uint32_t const sheetRow );

extern void Stds_DrawSelectedSpriteOnGrid( const struct grid_t *grid, const uint32_t gridCol,
                                           const uint32_t gridRow, const SDL_RendererFlip flip,
                                           const uint16_t angle );

extern void Stds_RenderAnimationToGrid( const struct grid_t *grid, const uint32_t col,
                                        const uint32_t row, const int32_t index,
                                        const SDL_RendererFlip flip, const uint16_t angle );

extern void Stds_AddCollisionToGrid( struct grid_t *grid, const uint32_t col, const uint32_t row );

#endif // GRID_H