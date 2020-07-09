#include "../include/trail.h"

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

void
trail_update( trail_t *t ) {
  t->alpha -= t->alpha_decay_rate;
  if ( t->alpha <= 0 ) {
    t->flags |= DEATH_MASK;
  }
}

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