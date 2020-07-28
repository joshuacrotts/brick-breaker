//=============================================================================================//
// FILENAME :       grid.c
//
// DESCRIPTION :
//        Defines the functions associated with grids, and is able to treat
//        each 'box' as a button and deals with events like clicking.
//
// NOTES :
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.
//
// AUTHOR :   strah19        START DATE :    19 Jul 2020
//
//=============================================================================================//

#include "../include/grid.h"
#include "../include/animation.h"
#include "../include/draw.h"

static bool Stds_AssertGrid( const struct grid_t *grid );

/**
 * Created grid with no texture, no collision, etc. This is useful for grids that have to change
 * colors overtime, or just don't have an accompanying texture, or other special feature.
 *
 * @param float x top-left x pos of button.
 * @param float y top-left y pos of button.
 * @param int32_t square_width width of each square.
 * @param int32_t square_height height of each square.
 * @param uint32_t cols number of columns the grid will have.
 * @param uint32_t rows number of rows the grid will have.
 * @param SDL_Color line_color color of the lining of the grid.
 * @param SDL_Color fill_color color of the square's in the grid.
 *
 * @return grid_t pointer.
 */
struct grid_t *
Stds_CreateGrid( const float x, const float y, const int32_t square_width,
                 const int32_t square_height, const uint32_t cols, const uint32_t rows,
                 const SDL_Color *line_color, const SDL_Color *fill_color ) {
  struct grid_t *grid;
  grid = malloc( sizeof( struct grid_t ) );

  if ( grid == NULL ) {
    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION,
                  "Error: could not allocate memory for grid_t, %s.\n", SDL_GetError() );
    exit( EXIT_FAILURE );
  } else {
    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Created grid_t.\n" );
  }

  memset( grid, 0, sizeof( struct grid_t ) );
  grid->x              = x;
  grid->y              = y;
  grid->sx             = x;
  grid->sy             = y;
  grid->sw             = square_width;
  grid->sh             = square_height;
  grid->cols           = cols;
  grid->rows           = rows;
  grid->line_color     = *line_color;
  grid->fill_color     = *fill_color;
  grid->textures       = NULL;
  grid->texture_buffer = 0;
  grid->sprite_sheet   = NULL;
  grid->clip.x = grid->clip.y = grid->clip.w = grid->clip.h = 0;
  grid->sprite_sheet_cols                                   = 0;
  grid->sprite_sheet_rows                                   = 0;
  grid->animation                = Stds_VectorCreate( sizeof( struct animation_t * ) );
  grid->animation_buffer         = -1;
  grid->is_camera_offset_enabled = false;

  return grid;
}

/**
 * Draws lines for where the box's of the grid would be.
 *
 * @TODO: apply grid offset pos with camera.
 *
 * @param grid_t* pointer to grid_t.
 *
 * @return void.
 */
void
Stds_DrawLineGrid( struct grid_t *grid ) {
  if ( Stds_AssertGrid( grid ) ) {
    grid->x = grid->is_camera_offset_enabled ? grid->sx - app.camera.x : grid->sx;
    grid->y = grid->is_camera_offset_enabled ? grid->sy - app.camera.y : grid->sy;

    for ( uint32_t r = 0; r < grid->rows; r++ ) {
      Stds_DrawLine( grid->x, grid->y, grid->x + ( float ) ( grid->sw * grid->cols ), grid->y,
                     &grid->line_color );
      grid->y += ( float ) grid->sh;
    }

    grid->y = grid->is_camera_offset_enabled ? grid->sy - app.camera.y : grid->sy;

    for ( uint32_t c = 0; c < grid->cols; c++ ) {
      Stds_DrawLine( grid->x, grid->y, grid->x, grid->y + ( float ) ( grid->sh * grid->rows ),
                     &grid->line_color );
      grid->x += ( float ) grid->sw;
    }

    grid->x = grid->is_camera_offset_enabled ? grid->sx - app.camera.x : grid->sx;

    Stds_DrawLine( grid->x, grid->y + ( float ) ( grid->sh * grid->rows ),
                   grid->x + ( float ) ( grid->sw * grid->cols ),
                   grid->y + ( float ) ( grid->sh * grid->rows ), &grid->line_color );
    Stds_DrawLine( grid->x + ( float ) ( grid->sw * grid->cols ), grid->y,
                   grid->x + ( float ) ( grid->sw * grid->cols ),
                   grid->y + ( float ) ( grid->sh * grid->rows ), &grid->line_color );
  }
}

/**
 * Fills the area of the grid with rectangles.
 *
 * @param grid_t* pointer to grid_t.
 *
 * @return void.
 */
void
Stds_FillWholeGrid( struct grid_t *grid ) {
  if ( Stds_AssertGrid( grid ) ) {
    grid->x = grid->sx;
    grid->y = grid->sy;

    SDL_FRect fill_rect = {grid->x, grid->y, ( float ) grid->sw, ( float ) grid->sh};

    for ( uint32_t r = 0; r < grid->rows; r++ ) {
      for ( uint32_t c = 0; c < grid->cols; c++ ) {

        Stds_DrawRectF( &fill_rect, &grid->fill_color, true, 0 );

        fill_rect.x += ( float ) grid->sw;
      }
      fill_rect.y += ( float ) grid->sh;
      fill_rect.x = grid->sx;
    }
  }
}

/**
 * Cleans up the grid.
 *
 * @param grid_t* pointer to grid_t.
 *
 * @return void.
 */
void
Stds_FreeGrid( struct grid_t *grid ) {
  if ( grid->textures != NULL ) {
    for ( uint32_t textureIndex = 0; textureIndex < grid->texture_buffer; textureIndex++ ) {
      SDL_DestroyTexture( grid->textures[textureIndex] );
      SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Freeing texture %d.\n", textureIndex );
    }
    free( grid->textures );
  }

  if ( grid->sprite_sheet != NULL ) {
    SDL_DestroyTexture( grid->sprite_sheet );
    SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Freeing sprite_sheet.\n" );
  }

  Stds_VectorDestroy( grid->animation );

  memset( grid, 0, sizeof( struct grid_t ) ); /* Makes the grid be equal to NULL. */
  free( grid );
  SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Freed grid_t.\n" );
}

/**
 * Checks if mouse is over any of the squares.
 *
 * @param grid_t* pointer to grid_t.
 *
 * @return grid_pair_t struct that holds data for what square is being hovered.
 */
struct grid_pair_t
Stds_OnGridHover( struct grid_t *grid ) {
  struct grid_pair_t p;

  if ( Stds_AssertGrid( grid ) ) {
    grid->x = grid->sx;
    grid->y = grid->sy;

    SDL_Rect hover_rect = {( int32_t ) grid->x, ( int32_t ) grid->y, ( int32_t ) grid->sw,
                           ( int32_t ) grid->sh};

    /* Loops through each square. */
    for ( uint32_t r = 0; r < grid->rows; r++ ) {
      p.r = ( int32_t ) r;
      p.y = ( float ) hover_rect.y;
      for ( uint32_t c = 0; c < grid->cols; c++ ) {

        p.c = ( int32_t ) c;
        p.x = ( float ) hover_rect.x;

        if ( Stds_IsMouseOverRect( ( float ) app.mouse.x, ( float ) app.mouse.y, &hover_rect ) ) {
          return p;
        }
        hover_rect.x += ( int32_t ) grid->sw;
      }

      hover_rect.y += ( int32_t ) grid->sh;
      hover_rect.x = ( int32_t ) grid->sx;
    }
  }

  /* -1 means that the mouse did not hover over any of the squares. */
  p.c = -1;
  p.r = -1;

  return p;
}

/**
 * Checks if the mouse clicked over any of the squares.
 *
 * @param grid_t* pointer to grid_t.
 * @param int32_t the code for which mous ebutton is clicked.
 *
 * @return grid_pair_t struct that holds data for what square is being clicked.
 */
struct grid_pair_t
Stds_OnGridClicked( struct grid_t *grid, const int32_t mouseCode ) {
  struct grid_pair_t p;

  if ( Stds_AssertGrid( grid ) ) {
    grid->x = grid->sx;
    grid->y = grid->sy;

    SDL_Rect click_rect = {( int32_t ) grid->x, ( int32_t ) grid->y, ( int32_t ) grid->sw,
                           ( int32_t ) grid->sh};

    /* Loops through each square */
    for ( uint32_t r = 0; r < grid->rows; r++ ) {
      p.r = ( int32_t ) r;
      p.y = ( float ) click_rect.y;
      for ( uint32_t c = 0; c < grid->cols; c++ ) {

        p.c = ( int32_t ) c;
        p.x = ( float ) click_rect.x;

        if ( Stds_IsMouseOverRect( ( float ) app.mouse.x, ( float ) app.mouse.y, &click_rect ) &&
             app.mouse.button[mouseCode] ) {
          app.mouse.button[mouseCode] = 0;
          return p;
        }

        click_rect.x += ( int32_t ) grid->sw;
      }

      click_rect.y += ( int32_t ) grid->sh;
      click_rect.x = ( int32_t ) grid->sx;
    }
  }

  /* -1 means that the mouse did not hover over any of the squares */
  p.c = -1;
  p.r = -1;

  return p;
}

/**
 * Initializes enough space for the amount of textures wanted for the grid.
 *
 * @param grid_t* pointer to grid_t.
 * @param int32_t number of textures for the grid.
 *
 * @return void.
 */
void
Stds_InitializeGridTextures( struct grid_t *grid, const int32_t texture_buffer ) {
  bool once_call = false;
  if ( Stds_AssertGrid( grid ) && !once_call ) {
    grid->textures       = malloc( texture_buffer * sizeof( SDL_Texture * ) );
    grid->texture_buffer = texture_buffer;
    once_call            = true;
  }
}

/**
 * Adds a single texture to the grid for use.
 *
 * @param grid_t* pointer to grid_t.
 * @param const char* filePath to texture.
 *
 * @return uint32_t ? What does this return?
 */
int32_t
Stds_AddGridTexture( struct grid_t *grid, const char *filePath ) {
  if ( Stds_AssertGrid( grid ) ) {
    int32_t current_texture_num = -1;
    if ( current_texture_num < grid->texture_buffer - 1 ) {
      current_texture_num++;
      SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Added texture %d to grid with path %s\n",
                    current_texture_num, filePath );
      grid->textures[current_texture_num] = Stds_LoadTexture( filePath );
      return current_texture_num;
    } else {
      return -1;
    }
  }
  return -1;
}

/**
 * Renders the specified texture id onto the grid.
 *
 * @param grid_t* pointer to grid_t.
 * @param uint32_t which column texture will be put.
 * @param uint32_t which row texture will be put.
 * @param int32_t index in texture array.
 * @param SDL_RendererFlip will flip texture.
 * @param uint16_t the angle of the image.
 *
 * @return void.
 */
void
Stds_PutGridTexture( struct grid_t *grid, const uint32_t col, const uint32_t row,
                     const int32_t index, const SDL_RendererFlip flip, const uint16_t angle ) {
  if ( Stds_AssertGrid( grid ) ) {
    if ( index < grid->texture_buffer && index > -1 ) {
      SDL_FRect texture_position = {grid->x + ( float ) ( col * grid->sw ),
                                    grid->y + ( float ) ( row * grid->sh ), ( float ) grid->sw,
                                    ( float ) grid->sh};
      Stds_BlitTexture( grid->textures[index], NULL, texture_position.x, texture_position.y,
                        texture_position.w, texture_position.h, angle, flip, NULL,
                        grid->is_camera_offset_enabled );
    }
  }
}

/**
 * Adds a sprite sheet to the grid.
 *
 * @param grid_t* pointer to grid_t.
 * @param const char* filePath filePath to texture
 * @param uint32_t number of cols the sprite sheet will have.
 * @param uint32_t number of rows the sprite sheet will have.
 *
 * @return void.
 */
void
Stds_AddSpriteSheetToGrid( struct grid_t *grid, const char *filePath, const uint32_t cols,
                           const uint32_t rows ) {
  if ( Stds_AssertGrid( grid ) ) {
    bool once_call = false;
    if ( Stds_AssertGrid( grid ) && !once_call ) {
      SDL_LogDebug( SDL_LOG_CATEGORY_APPLICATION, "Added sprite_sheet to grid with path %s\n",
                    filePath );
      grid->sprite_sheet = Stds_LoadTexture( filePath );
      once_call          = true;
      SDL_QueryTexture( grid->sprite_sheet, NULL, NULL, &grid->clip.w, &grid->clip.h );

      grid->clip.w /= cols;
      grid->clip.h /= rows;

      grid->sprite_sheet_cols = cols;
      grid->sprite_sheet_rows = rows;
    }
  }
}

/**
 * Select which sprite you want to use.
 *
 * @param grid_t* pointer to grid_t.
 * @param uint32_t which column the sprite is to be used.
 * @param uint32_t which row the sprite is to be used.
 *
 * @return void.
 */
void
Stds_SelectSpriteForGrid( struct grid_t *grid, const uint32_t sheetCol, const uint32_t sheetRow ) {
  if ( Stds_AssertGrid( grid ) && sheetCol < grid->sprite_sheet_cols &&
       sheetRow < grid->sprite_sheet_rows ) {
    grid->clip.x = sheetCol * grid->clip.w;
    grid->clip.y = sheetRow * grid->clip.h;
  }
}

/**
 * Will render the specified sprite selected from Stds_SelectSpriteForGrid.
 *
 * @param grid_t* pointer to grid_t.
 * @param uint32_t which column to render the specified sprite onto the grid.
 * @param uint32_t which row to render the specified sprite onto the grid.
 * @param SDL_RendererFlip will flip texture.
 * @param uint16_t the angle of the image.
 *
 * @return void.
 */
void
Stds_DrawSelectedSpriteOnGrid( const struct grid_t *grid, const uint32_t gridCol,
                               const uint32_t gridRow, const SDL_RendererFlip flip,
                               const uint16_t angle ) {
  if ( Stds_AssertGrid( grid ) && gridCol < grid->cols && gridRow < grid->rows ) {
    SDL_FRect position = {grid->x + ( float ) ( gridCol * grid->sw ),
                          grid->y + ( float ) ( gridRow * grid->sh ), ( float ) grid->sw,
                          ( float ) grid->sh};
    Stds_BlitTexture( grid->sprite_sheet, &grid->clip, position.x, position.y, position.w,
                      position.h, angle, flip, NULL, grid->is_camera_offset_enabled );
  }
}

/**
 * Adds a animation_t to the vector of animations.
 * @param grid_t* pointer to grid_t.
 * @param animation_t* pointer to animation_t.
 *
 * @return int32_t.
 */
int32_t
Stds_AddAnimationToGrid( struct grid_t *grid, struct animation_t *animate ) {
  if ( animate == NULL ) {
    Stds_Print( "Error, could not add animation to the grid, it is NULL." );
    return -1;
  } else if ( Stds_AssertGrid( grid ) ) {
    grid->animation_buffer++;
    Stds_VectorAppend( grid->animation, animate );
    return grid->animation_buffer;
  }
  return -1;
}

/**
 * Renders the animation according to the vectors index.
 * @param grid_t* pointer to grid_t.
 * @param uint32_t what column to render the animation.
 * @param uint32_t what row to render the animation.
 * @param int32_t index of the vector storing the animations.
 * @param SDL_RendererFlip will flip texture.
 * @param uint16_t the angle of the image.
 *
 * @return void.
 */
void
Stds_RenderAnimationToGrid( const struct grid_t *grid, const uint32_t col, const uint32_t row,
                            const int32_t index, const SDL_RendererFlip flip,
                            const uint16_t angle ) {
  if ( Stds_AssertGrid( grid ) && grid->animation != NULL && col < grid->cols &&
       row < grid->rows ) {
    struct animation_t *editAnim = Stds_VectorGet( grid->animation, index );
    editAnim->pos_x              = grid->x + ( float ) ( col * grid->sw );
    editAnim->pos_y              = grid->y + ( float ) ( row * grid->sh );
    editAnim->dest_width         = grid->sw;
    editAnim->dest_height        = grid->sh;
    editAnim->flip               = flip;
    editAnim->angle              = angle;

    /* This MUST be false to account for both scrolling and fixed-viewports. */
    editAnim->is_camera_offset_enabled = false;
    Stds_AnimationUpdate( editAnim );
    Stds_AnimationDraw( editAnim );
  }
}

/**
 *
 */
void
Stds_AddCollisionToGrid( struct grid_t *grid, uint32_t col, uint32_t row ) {
  if ( Stds_AssertGrid( grid ) && col < grid->cols && row < grid->rows ) {
    /* TODO */
  }
}

/**
 * Ensures that the grid is not null.
 *
 * @param grid_t* pointer to grid_t.
 *
 * @return bool.
 */
static bool
Stds_AssertGrid( const struct grid_t *grid ) {
  return !( grid == NULL );
}