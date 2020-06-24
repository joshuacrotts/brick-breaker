#include "../include/particle.h"

entity_t *
add_particle( float x, float y, float dx, float dy, float decX, float decY, uint16_t w, uint16_t h,
              uint16_t angle, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float delta_alpha,
              uint32_t id_flags ) {
  entity_t *en;

  en = malloc( sizeof( entity_t ) );
  memset( en, 0, sizeof( entity_t ) );

  en->x             = x;
  en->y             = y;
  en->w             = w;
  en->h             = h;
  en->dx            = dx;
  en->dy            = dy;
  en->life          = FPS * 5;
  en->delta_accel_x = decX;
  en->delta_accel_y = decY;
  en->animation     = NULL;

  SDL_Color color;
  color.r = r;
  color.g = g;
  color.b = b;
  color.a = a;

  en->color       = color;
  en->delta_alpha = delta_alpha;
  en->angle       = angle;
  en->id_flags |= id_flags | ID_PARTICLE_MASK;
  en->flags |= ID_PARTICLE_MASK;

  return en;
}

entity_t *
add_animated_particle( float x, float y, float dx, float dy, float decX, float decY, uint16_t angle,
                       uint32_t id_flags, animation_t *animation ) {
  entity_t *en;

  en = malloc( sizeof( entity_t ) );
  memset( en, 0, sizeof( entity_t ) );

  en->x         = x;
  en->y         = y;
  en->animation = animation;

  if ( animation->flags & STD_ANIMATION_MASK ) {
    en->w = animation->sprite_sheet_width / animation->number_of_frames;
    en->h = animation->sprite_sheet_height / animation->number_of_frames;
  } else {
    SDL_QueryTexture( animation->current_texture, NULL, NULL, &en->w, &en->h );
  }

  en->dx = dx;
  en->dy = dy;

  en->life          = FPS * 5;
  en->delta_accel_x = decX;
  en->delta_accel_y = decY;

  en->angle = angle;
  en->id_flags |= id_flags | ID_PARTICLE_MASK;

  return en;
}

void
particle_update( entity_t *e ) {
  e->life--;
  if ( e->life <= 0 ) {
    e->flags |= DEATH_MASK;
    return;
  }

  if ( e->animation != NULL ) {
    animation_update( e );
  }

  if ( floor( e->delta_accel_x ) != 0 ) {
    e->dx *= e->delta_accel_x;
  }

  if ( floor( e->delta_accel_y ) != 0 ) {
    e->dy *= e->delta_accel_y;
  }

  if ( e->id_flags & ID_SCATTER_PARTICLE_MASK ) {
    e->dy += 0.5f;
  } else if ( e->id_flags & ID_P_STAR_MASK ) {
    if ( e->y < -100 ) {
      e->flags |= DEATH_MASK;
    }
  }

  int16_t tmp_alpha = ( int16_t )( e->color.a + e->delta_alpha );

  if ( tmp_alpha < 0 ) {
    tmp_alpha = 0;
  }

  e->color.a = tmp_alpha;
  e->x += e->dx;
  e->y += e->dy;
}

void
particle_draw( entity_t *e ) {
  if ( e->animation == NULL ) {
    SDL_Rect rect;
    rect.x = ( int32_t )( e->x - app.camera.x );
    rect.y = ( int32_t )( e->y - app.camera.y );
    rect.w = e->w;
    rect.h = e->h;
    if ( e->id_flags & ID_P_SQUARE_MASK ) {
      draw_rect( &rect, e->color.r, e->color.g, e->color.b, e->color.a, true );
    } else if ( e->id_flags & ID_P_CIRCLE_MASK ) {
      uint32_t r = rect.w >> 1;
      fill_circle( rect.x, rect.y, r, e->color.r, e->color.g, e->color.b, e->color.a );
    }
  } else {
    animation_draw( e );
  }
}

void
particle_die( entity_t *e ) {
  free( e );
}
