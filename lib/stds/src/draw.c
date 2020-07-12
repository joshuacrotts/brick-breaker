//=============================================================================================//
// FILENAME :       draw.c
//
// DESCRIPTION :
//        This file defines the various procedures for drawing primitives (lines, rectangles, circles),
//        textures, blitting rectangles, and texture caching/loading.
//
// PUBLIC FUNCTIONS :
//        void          prepare_scene( void );
//        void          present_scene( void );
//        void          blit_rect( SDL_Texture *texture, SDL_Rect *src, f32 x, f32 y, bool camera_offset );
//        void          blit_texture( SDL_Texture *texture, f32 x, f32 y, bool is_center,
//                                    bool camera_offset );
//        void          blit_texture_rotated( SDL_Texture *texture, f32 x, f32 y, uint16_t angle,
//                                            SDL_RendererFlip flip, bool camera_offset );
//        void          blit_texture_resize( SDL_Texture *texture, f32 x, f32 y, int32_t w,
//                                           int32_t h, uint16_t angle, SDL_RendererFlip flip,
//                                           bool camera_offset );
//        void          blit_texture_color_scaled( SDL_Texture *texture, f32 x, f32 y, f32 scale_x,
//                                                 f32 scale_y, uint16_t angle, SDL_RendererFlip flip,
//                                                 SDL_Color *c, bool camera_offset );
//        void          blit_texture_scaled( SDL_Texture *texture, f32 x, f32 y, f32 scale_x,
//                                           f32 scale_y, uint16_t angle, SDL_RendererFlip flip,
//                                           bool camera_offset );
//        void          draw_rect( SDL_Rect *rect, SDL_Color *c, bool is_filled, bool camera_offset );
//        void          draw_frect( SDL_FRect *frect, SDL_Color *c, bool is_filled, bool camera_offset );
//        void          draw_rect_stroke( f32 x, f32 y, uint32_t w, uint32_t h, uint32_t thickness,
//                                        SDL_Color *c, bool camera_offset );
//        void          draw_circle( circle_t *circle, SDL_Color *c );
//        void          fill_circle( circle_t *circle, SDL_Color *c );
//        void          draw_line( f32 x1, f32 y1, f32 x2, f32 y2, SDL_Color *c );
//        SDL_Texture   *load_texture( const char *directory );
//        SDL_Color     combine_fade_color( fade_color_t *fade_color );
//
//  PRIVATE/STATIC FUNCTIONS:
//        SDL_Texture   *get_texture( const char * );
//        void          cache_texture( const char *, SDL_Texture * );
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
// AUTHOR :   Joshua Crotts        START DATE :    22 Jun 2020
//
//=============================================================================================//

#include "../include/draw.h"

static SDL_Texture *get_texture( const char * );
static void         cache_texture( const char *, SDL_Texture * );

/**
 * Clears the screen with a black color.
 *
 * @param void.
 *
 * @return void.
 */
void
prepare_scene() {
  SDL_SetRenderDrawColor( app.renderer, 0, 0, 0, 0 );
  SDL_RenderClear( app.renderer );
}

/**
 * Presents the current scene from the application.
 *
 * @param void.
 *
 * @return void.
 */
void
present_scene() {
  SDL_RenderPresent( app.renderer );
}

/**
 * Copies the graphics from the texture to a different
 * rectangle. You can specify what portion of the src
 * SDL_Texture* to render by the size attributes of the
 * SDL_Rect* pointer.
 *
 * @param SDL_Texture * pointer to texture.
 * @param f32 x coordinate.
 * @param f32 y coordinate,
 * @param bool either centers the texture or not (based on dimensions).
 * @param bool either applies the camera offset or not.
 *
 * @return void.
 */
void
blit_texture( SDL_Texture *texture, f32 x, f32 y, bool is_center, bool camera_offset ) {
  SDL_FRect dest;

  dest.x = camera_offset ? x - app.camera.x : x;
  dest.y = camera_offset ? y - app.camera.y : y;

  int32_t w, h;

  SDL_QueryTexture( texture, NULL, NULL, &w, &h );

  dest.w = ( f32 ) w;
  dest.h = ( f32 ) h;

  if ( is_center ) {
    dest.x -= ( dest.w / 2.0f );
    dest.y -= ( dest.h / 2.0f );
  }

  SDL_RenderCopyF( app.renderer, texture, NULL, &dest );
}

/**
 * Renders a texture, specified by src, at
 * coordinates (x, y). You may pass in both integers or
 * f32ing-point numbers to this function.
 *
 * @param SDL_Texture*
 * @param f32 x
 * @param f32 y
 * @param bool if the texture should be centered or not.
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
void
blit_rect( SDL_Texture *texture, SDL_Rect *src, f32 x, f32 y, bool camera_offset ) {
  SDL_FRect dest;
  dest.x = camera_offset ? x - app.camera.x : x;
  dest.y = camera_offset ? y - app.camera.y : y;

  dest.w = src->w;
  dest.h = src->h;
  SDL_RenderCopyF( app.renderer, texture, src, &dest );
}

/**
 * Draws a rotated SDL_Texture pointer at an x, y coordinate. The
 * rotation is applied about the center of the texture.
 *
 * @param SDL_Texture* pointer to texture object.
 * @param f32 x coordinate.
 * @param f32 y coordinate.
 * @param uint16_t angle of rotation in degrees (0 to 360).
 * @param SDL_RendererFlip flip status (SDL_FLIP_HORIZONTAL/VERTICAL).
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
void
blit_texture_rotated( SDL_Texture *texture, f32 x, f32 y, uint16_t angle, SDL_RendererFlip flip,
                      bool camera_offset ) {
  SDL_FRect dest;
  dest.x = camera_offset ? x - app.camera.x : x;
  dest.y = camera_offset ? y - app.camera.y : y;
  int32_t w, h;

  SDL_QueryTexture( texture, NULL, NULL, &w, &h );

  dest.w = ( f32 ) w;
  dest.h = ( f32 ) h;

  SDL_RenderCopyExF( app.renderer, texture, NULL, &dest, angle, NULL, flip );
}

/**
 * Blits a rotated SDL texture at an x and y coordinate with a given
 * size.
 *
 * @param SDL_Texture* pointer to texture object.
 * @param f32 x coordinate.
 * @param f32 y coordinate.
 * @param int32_t desired width of texture.
 * @param int32_t desired height of texture.
 * @param uint16_t angle of rotation (0 to 360).
 * @param SDL_RendererFlip flip status (SDL_FLIP_HORIZONTAL/VERTICAL)
 * @param bool applies camera offset or not.
 *
 * @return void.
 */
void
blit_texture_resize( SDL_Texture *texture, f32 x, f32 y, int32_t w, int32_t h,
                           uint16_t angle, SDL_RendererFlip flip, bool camera_offset ) {
  SDL_FRect dest_rect;

  dest_rect.x = camera_offset ? x - app.camera.x : x;
  dest_rect.y = camera_offset ? y - app.camera.y : y;
  dest_rect.w = w;
  dest_rect.h = h;

  SDL_RenderCopyExF( app.renderer, texture, NULL, &dest_rect, angle, NULL, flip );
}

/**
 * Blits a rotated SDL texture at an x and y coordinate with a given
 * scale. A color is also provided to alter the color of the texture.
 *
 * @param SDL_Texture* pointer to texture object.
 * @param f32 x coordinate.
 * @param f32 y coordinate.
 * @param scale_x scale factor on x-axis.
 * @param scale_y scale factor on y-axis.
 * @param uint16_t angle of rotation (0 to 360).
 * @param SDL_RendererFlip flip status (SDL_FLIP_HORIZONTAL/VERTICAL)
 * @param SDL_Color* color to apply.
 * @param bool applies camera offset or not.
 *
 * @return void.
 */
void
blit_texture_color_scaled( SDL_Texture *texture, f32 x, f32 y, f32 scale_x, f32 scale_y,
                           uint16_t angle, SDL_RendererFlip flip, SDL_Color *c,
                           bool camera_offset ) {
  int32_t texture_width  = 0;
  int32_t texture_height = 0;

  SDL_QueryTexture( texture, NULL, NULL, &texture_width, &texture_height );

  // Apply the scaling procedure to the image.
  SDL_FRect dest_rect;

  dest_rect.x = camera_offset ? x - app.camera.x : x;
  dest_rect.y = camera_offset ? y - app.camera.y : y;
  dest_rect.w = ( texture_width * scale_x );
  dest_rect.h = ( texture_height * scale_y );

  // If the color pointer is not null, draw a color.
  if ( c != NULL ) {
    SDL_SetTextureColorMod( texture, c->r, c->g, c->b );
    SDL_SetTextureAlphaMod( texture, c->a );
  }

  SDL_RenderCopyExF( app.renderer, texture, NULL, &dest_rect, angle, NULL, flip );
}

/**
 * Blits a rotated SDL texture at an x and y coordinate with a given
 * scale. Note that you will have to account for the scaling routine
 * yourself in your game (i.e. handling collisions if applicable).
 *
 * @param SDL_Texture*
 * @param f32 x
 * @param f32 y
 * @param f32 scale_x
 * @param f32 scale_y
 * @param uint16_t angle
 * @param SDL_RendererFlip flip status (SDL_FLIP_HORIZONTAL/VERTICAL)
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
void
blit_texture_scaled( SDL_Texture *texture, f32 x, f32 y, f32 scale_x, f32 scale_y,
                     uint16_t angle, SDL_RendererFlip flip, bool camera_offset ) {

  // Camera offsets are applied in color_scaled method.
  blit_texture_color_scaled( texture, x, y, scale_x, scale_y, angle, flip, NULL, camera_offset );
}

/**
 * Draws a rectangle with the supplied color to the screen. The
 * rectangle's properties should be filled (i.e x, y, w, and h).
 * If the last parameter is true, the shape will be filled.
 *
 * @param SDL_Rect*
 * @param SDL_Color color to fill.
 * @param bool is the rect filled or not.
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
void
draw_rect( SDL_Rect *rect, SDL_Color *c, bool is_filled, bool camera_offset ) {
  SDL_SetRenderDrawBlendMode( app.renderer, SDL_BLENDMODE_BLEND );
  SDL_SetRenderDrawColor( app.renderer, c->r, c->g, c->b, c->a );

  if ( camera_offset ) {
    rect->x -= ( int32_t ) app.camera.x;
    rect->y -= ( int32_t ) app.camera.y;
  }

  if ( is_filled ) {
    SDL_RenderFillRect( app.renderer, rect );
  } else {
    SDL_RenderDrawRect( app.renderer, rect );
  }
  SDL_SetRenderDrawBlendMode( app.renderer, SDL_BLENDMODE_NONE );
}

/**
 * Draws a f32ing-point rectangle with the supplied color. The
 * rectangle's properties should be filled (i.e x, y, w, and h).
 * If the last parameter is true, the shape will be filled.
 *
 * @param SDL_FRect*
 * @param SDL_Color color to fill.
 * @param bool is the rect filled or not.
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
void
draw_frect( SDL_FRect *frect, SDL_Color *c, bool is_filled, bool camera_offset ) {
  SDL_SetRenderDrawBlendMode( app.renderer, SDL_BLENDMODE_BLEND );
  SDL_SetRenderDrawColor( app.renderer, c->r, c->g, c->b, c->a );

  if ( camera_offset ) {
    frect->x -= app.camera.x;
    frect->y -= app.camera.y;
  }

  if ( is_filled ) {
    SDL_RenderFillRectF( app.renderer, frect );
  } else {
    SDL_RenderDrawRectF( app.renderer, frect );
  }

  SDL_SetRenderDrawBlendMode( app.renderer, SDL_BLENDMODE_NONE );
}

/**
 * Draws a rectangle with the specified stroke (pixel width) and color.
 * First four parameters are the x, y, width, and height of rectangle.
 * The next specifies how "thick" it should be. The last four values
 * specify the RGBA values.
 *
 * @param f32 x
 * @param f32 y
 * @param uint32_t w
 * @param uint32_t h
 * @param uint32_t stroke thickness
 * @param SDL_Color *c color.
 * @param bool applies the camera offset or not.
 *
 * @return void.
 */
void
draw_rect_stroke( f32 x, f32 y, uint32_t w, uint32_t h, uint32_t stroke, SDL_Color *c,
                  bool camera_offset ) {
  if ( stroke <= 0 ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                 "Error: stroke %d cannot be a negative or zero value!", stroke );
    exit( EXIT_FAILURE );
  } else {
    if ( camera_offset ) {
      x += app.camera.x;
      y += app.camera.y;
    }

    // Top-left to TR
    SDL_FRect r1 = {x, y, w, stroke};

    // TL to BL
    SDL_FRect r2 = {x, y, stroke, h};

    // BL to BR
    SDL_FRect r3 = {x, camera_offset ? h - stroke + app.camera.y : h - stroke, w, stroke};

    // TR to BR.
    SDL_FRect r4 = {camera_offset ? w - stroke + app.camera.x : w - stroke, y, stroke, h};

    draw_frect( &r1, c, true, camera_offset );
    draw_frect( &r2, c, true, camera_offset );
    draw_frect( &r3, c, true, camera_offset );
    draw_frect( &r4, c, true, camera_offset );
  }
}

/*
 * Draws a line with the specified color to the screen.
 *
 * @param
 * @param
 * @param
 * @param
 * @param
 *
 * @return void.
 */
void
draw_line( f32 x1, f32 y1, f32 x2, f32 y2, SDL_Color *c ) {
  SDL_SetRenderDrawColor( app.renderer, c->r, c->g, c->b, c->a );
  SDL_RenderDrawLineF( app.renderer, x1, y1, x2, y2 );
}

/**
 * Draws a circle. Simple as that. Takes in the circle's center coordinates,
 * the radius, and RGBA.
 *
 * @param struct circle_t * pointer to circle
 * @param SDL_Color *c color to draw.
 *
 * @return void.
 */
void
draw_circle( circle_t *circle, SDL_Color *c ) {
  const f32 diameter = ( circle->radius * 2 );

  f32 x     = ( circle->radius - 1 );
  f32 y     = 0;
  f32 tx    = 1;
  f32 ty    = 1;
  f32 error = ( tx - diameter );

  SDL_SetRenderDrawColor( app.renderer, c->r, c->g, c->b, c->a );
  while ( x >= y ) {
    //  Each of the following renders an octant of the circle
    SDL_RenderDrawPointF( app.renderer, circle->center_x + x, circle->center_y - y );
    SDL_RenderDrawPointF( app.renderer, circle->center_x + x, circle->center_y + y );
    SDL_RenderDrawPointF( app.renderer, circle->center_x - x, circle->center_y - y );
    SDL_RenderDrawPointF( app.renderer, circle->center_x - x, circle->center_y + y );
    SDL_RenderDrawPointF( app.renderer, circle->center_x + y, circle->center_y - x );
    SDL_RenderDrawPointF( app.renderer, circle->center_x + y, circle->center_y + x );
    SDL_RenderDrawPointF( app.renderer, circle->center_x - y, circle->center_y - x );
    SDL_RenderDrawPointF( app.renderer, circle->center_x - y, circle->center_y + x );

    if ( error <= 0 ) {
      ++y;
      error += ty;
      ty += 2;
    }

    if ( error > 0 ) {
      --x;
      tx += 2;
      error += ( tx - diameter );
    }
  }
}

/**
 * Fills a circle. Simple as that.
 *
 * @param struct circle_t * ponter to circle.
 * @param SDL_Color *c color to fill.
 *
 * @return void.
 */
void
fill_circle( circle_t *circle, SDL_Color *c ) {
  f32 offsetx, offsety, d;
  int status;

  offsetx = 0;
  offsety = circle->radius;
  d       = circle->radius - 1;
  status  = 0;
  SDL_SetRenderDrawColor( app.renderer, c->r, c->g, c->b, c->a );

  while ( offsety >= offsetx ) {
    f32 x = circle->center_x;
    f32 y = circle->center_y;

    status +=
        SDL_RenderDrawLineF( app.renderer, x - offsety, y + offsetx, x + offsety, y + offsetx );
    status +=
        SDL_RenderDrawLineF( app.renderer, x - offsetx, y + offsety, x + offsetx, y + offsety );
    status +=
        SDL_RenderDrawLineF( app.renderer, x - offsetx, y - offsety, x + offsetx, y - offsety );
    status +=
        SDL_RenderDrawLineF( app.renderer, x - offsety, y - offsetx, x + offsety, y - offsetx );

    if ( status < 0 ) {
      status = -1;
      break;
    }

    if ( d >= 2 * offsetx ) {
      d -= 2 * offsetx + 1;
      offsetx += 1;
    } else if ( d < 2 * ( circle->radius - offsety ) ) {
      d += 2 * offsety - 1;
      offsety -= 1;
    } else {
      d += 2 * ( offsety - offsetx - 1 );
      offsety -= 1;
      offsetx += 1;
    }
  }
}

/*
 * Completes one iteration of the color-merge procedure.
 * The speed is dependent on the fade_color_t struct passed.
 * 
 * @param 
 * 
 * @return SDL_Color copy of the new color struct.
 */
SDL_Color
combine_fade_color( fade_color_t *f ) {
  if ( f->time <= 1.0f && f->is_first_color ) {
    f->time = ( f32 ) ( f->time + f->alpha );
  } else {
    f->is_first_color = false;
  }

  if ( f->time >= 0.0f && !f->is_first_color ) {
    f->time = ( f32 ) ( f->time - f->alpha );
  } else {
    f->is_first_color = true;
  }

  int32_t r = ( int32_t ) ( f->time * f->c2.r + ( 1.0f - f->time ) * f->c1.r );
  int32_t g = ( int32_t ) ( f->time * f->c2.g + ( 1.0f - f->time ) * f->c1.g );
  int32_t b = ( int32_t ) ( f->time * f->c2.b + ( 1.0f - f->time ) * f->c1.b );

  SDL_Color c;
  clamp( &r, 0, 0xff );
  clamp( &g, 0, 0xff );
  clamp( &b, 0, 0xff );

  c.r = r;
  c.g = g;
  c.b = b;

  return c;
}

/*
 * Loads an image from the specified path. An error is
 * displayed if the file cannot be found or is not
 * loadable.
 *
 * @param
 *
 * @return SDL_Texture * pointer to the texture loaded from the buffer.
 */
SDL_Texture *
load_texture( const char *fileName ) {
  SDL_Texture *texture;

  texture = get_texture( fileName );

  if ( texture == NULL ) {
    texture = IMG_LoadTexture( app.renderer, fileName );
    if ( texture == NULL ) {
      SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION,
                   "Error: could not load image %s. Error Code: %s.\n", fileName, SDL_GetError() );
      exit( EXIT_FAILURE );
    }

    cache_texture( fileName, texture );
  }

  return texture;
}

/*
 * Searches through the SDL_Texture list to see if we have previously
 * loaded in this texture. If so, it is returned. Otherwise, NULL.
 *
 * @param file name of SDL_Texture.
 * @return SDL_Texture pointer - either NULL or object.
 */
static SDL_Texture *
get_texture( const char *file_name ) {
  texture_t *t;

  for ( t = app.texture_head.next; t != NULL; t = t->next ) {
    if ( strcmp( t->name, file_name ) == 0 ) {
      return t->texture;
    }
  }

  return NULL;
}

/*
 * If a SDL_Texture has not been previously loaded in, we add it to
 * the cache here. The cache is a linked-list of SDL_Texture pointers
 * that store references to each texture so we do not waste resources
 * opening the input stream and loading the data back in.
 *
 * @param file name, and pointer to the texture.
 * @return void.
 */
static void
cache_texture( const char *file_name, SDL_Texture *sdl_texture ) {
  texture_t *texture;
  texture = malloc( sizeof( texture_t ) );

  if ( texture == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for texture_t. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( texture, 0, sizeof( texture_t ) );
  app.texture_tail->next = texture;
  app.texture_tail       = texture;

  strncpy( texture->name, file_name, MAX_FILE_NAME_LEN );
  texture->texture = sdl_texture;
}
