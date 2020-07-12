//=============================================================================================//
// FILENAME :       trail.c
//
// DESCRIPTION :
//        This file defines trail functionality with alpha-blending support.
//
// PUBLIC FUNCTIONS :
//        void      add_trail( entity_t *parent_entity, int16_t alpha_decay_rate, int16_t starting_alpha,
//                             bool is_texture, SDL_RendererFlip flip );
//        void      trail_update( trail_t *t );
//        void      trail_draw( trail_t *t );
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
// AUTHOR :   Joshua Crotts        START DATE :    18 Jun 2020
//
//=============================================================================================//

#include "../include/trail.h"

/**
 * Initializes a trail object using the supplied Entity as the parent
 * where it will stay for the duration of its life. The trail is added
 * to the App automatically, so nothing is returned.
 *
 * @param entity_t* parent entity.
 * @param int16_t rate at which the alpha decreases (should be between 0
 *        and 255, the higher it is, the faster it goes).
 * @param int16_t starting alpha of the object.
 * @param bool blends the alpha a different way if it is a texture or not.
 * @param SDL_RendererFlip flip enum for if the trail should be flipped.
 *
 * @return void.
 */
void
add_trail( entity_t *parent, int16_t alpha_decay, int16_t initial_alpha, bool is_texture,
           SDL_RendererFlip flip ) {
  trail_t *t;
  t = malloc( sizeof( trail_t ) );

  if ( t == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for trail_t. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( t, 0, sizeof( trail_t ) );

  t->x          = parent->x;
  t->y          = parent->y;
  t->flip       = flip;
  t->is_texture = is_texture;

  if ( parent->animation != NULL ) {
    t->texture = parent->animation->frames[parent->animation->current_frame_id];
  } else {
    t->texture = parent->texture[0];
  }

  t->alpha            = initial_alpha;
  t->alpha_decay_rate = alpha_decay;

  app.trail_tail->next = t;
  app.trail_tail       = t;
}

/**
 * Updates the trail by iterating through the trail's linked lists,
 * and constantly decreasing its alpha value. Once any arbitrary
 * tail node has an alpha of 0 or less (clamped to 0), it is
 * removed.
 *
 * @param trail_t struct to update.
 *
 * @return void
 */
void
trail_update( trail_t *t ) {
  t->alpha -= t->alpha_decay_rate;
  if ( t->alpha <= 0 ) {
    t->flags |= DEATH_MASK;
  }
}

/**
 * Draws the tail linked list.
 *
 * @param trail_t struct to draw.
 *
 * @return void.
 */
void
trail_draw( trail_t *t ) {
  if ( !t->is_texture ) {
    SDL_SetTextureBlendMode( t->texture, SDL_BLENDMODE_BLEND );
  }

  SDL_SetTextureAlphaMod( t->texture, t->alpha );
  blit_texture_rotated( t->texture, t->x, t->y, 0, t->flip, true );

  if ( !t->is_texture ) {
    SDL_SetTextureBlendMode( t->texture, SDL_BLENDMODE_NONE );
  }
}