//=============================================================================================//
// FILENAME :       collision.c
//
// DESCRIPTION :
//        This file defines the primary collision detectin functions. As of 7/9/2020, we have
//        an AABB collision-response function (returning an enum of the collision side), and a 
//        primitive rectangle-overlap test.
//
// PUBLIC FUNCTIONS :
//        enum CollisionSide check_aabb_collision( entity_t *, entity_t * );
//        bool check_intersection( f32, f32, int32_t, int32_t, f32, f32, int32_t, int32_t )
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

#include "../include/collision.h"

/**
 * Determines which side entity_t a collided onto entity_t b.
 *
 * @param entity_t* first entity.
 * @param entity_t* second entity.
 *
 * @return enum side that a collided onto b with (the side of b).
 */
enum CollisionSide
check_aabb_collision( entity_t *a, entity_t *b ) {
  f32 w  = 0.5f * ( b->w + a->w );
  f32 h  = 0.5f * ( b->h + a->h );
  f32 dx = ( b->x + b->w / 2.0f ) - ( a->x + a->w / 2.0f );
  f32 dy = ( b->y + b->h / 2.0f ) - ( a->y + a->h / 2.0f );

  if ( fabs( dx ) < w && fabs( dy ) < h ) {
    f32 wy = w * dy;
    f32 hx = h * dx;

    if ( wy >= hx ) {
      if ( wy > -hx ) { // top
        a->y = b->y - a->h;
        return SIDE_TOP;
      } else { // right
        a->x = b->x + b->w;
        return SIDE_RIGHT;
      }
    } else {
      if ( wy > -hx ) { // left
        a->x = b->x - a->w;
        return SIDE_LEFT;
      } else { // bottom
        a->y = b->y + b->h;
        return SIDE_BOTTOM;
      }
    }
  }

  return SIDE_NONE;
}

/**
 * Determines if two rectangles are collided.
 *
 * @param
 * @param
 * @param
 * @param
 * @param
 * @param
 * @param
 * @param
 * 
 * @return true if overlap exists, false otherwise.
 */
bool
check_intersection( f32 x1, f32 y1, int32_t w1, int32_t h1, f32 x2, f32 y2, int32_t w2,
                    int32_t h2 ) {
  return ( MAX( x1, x2 ) < MIN( x1 + w1, x2 + w2 ) ) && ( MAX( y1, y2 ) < MIN( y1 + h1, y2 + h2 ) );
}
