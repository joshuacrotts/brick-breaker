#include "../include/particle.h"

particle_t
add_particle( f32 x, f32 y, f32 dx, f32 dy, f32 decX, f32 decY, uint16_t w, uint16_t h,
              uint16_t angle, uint8_t r, uint8_t g, uint8_t b, uint8_t a, f32 delta_alpha,
              uint32_t id_flags ) {
  particle_t en;

  en.x             = x;
  en.y             = y;
  en.w             = w;
  en.h             = h;
  en.dx            = dx;
  en.dy            = dy;
  en.life          = FPS * 3;
  en.delta_accel_x = decX;
  en.delta_accel_y = decY;
  en.animation     = NULL;

  SDL_Color color = {r, g, b, a};

  en.color       = color;
  en.delta_alpha = delta_alpha;
  en.angle       = angle;
  en.id_flags |= id_flags | ID_PARTICLE_MASK;
  en.flags |= ID_PARTICLE_MASK;

  en.particle_update = particle_update;
  en.particle_draw   = particle_draw;
  
  return en;
}

particle_t *
add_animated_particle( f32 x, f32 y, f32 dx, f32 dy, f32 decX, f32 decY, uint16_t angle,
                       uint32_t id_flags, animation_t *animation ) {
  particle_t *en;
  en = malloc( sizeof( particle_t ) );
  memset( en, 0, sizeof( particle_t ) );

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

  en->life          = FPS * 3;
  en->delta_accel_x = decX;
  en->delta_accel_y = decY;

  en->angle = angle;
  en->id_flags |= id_flags | ID_PARTICLE_MASK;

  en->particle_update = particle_update;
  en->particle_draw   = particle_draw;

  return en;
}

void
particle_update( particle_t *e ) {
  if ( --e->life <= 0 ) {
    e->flags |= DEATH_MASK;
    return;
  }

  if ( floor( e->delta_accel_x ) != 0 ) {
    e->dx *= e->delta_accel_x;
  }

  if ( floor( e->delta_accel_y ) != 0 ) {
    e->dy *= e->delta_accel_y;
  }

  if ( e->id_flags & ID_P_STAR_MASK ) {
    if ( e->y < -100.0f ) {
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
particle_draw( particle_t *e ) {
  if ( e->animation == NULL ) {
    if ( e->id_flags & ID_P_SQUARE_MASK ) {
      SDL_FRect frect = {e->x, e->y, e->w, e->h};
      draw_frect( &frect, &e->color, true, false );
    } else if ( e->id_flags & ID_P_CIRCLE_MASK ) {
      circle_t c = {e->x, e->y, e->w / 2};
      fill_circle( &c, &e->color );
    }
  } else {
    animation_draw( e->animation );
  }
}