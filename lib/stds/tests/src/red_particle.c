#include "../include/red_particle.h"

void
red_particle_update( particle_t *p ) {
  if ( --p->life <= 0 ) {
    p->flags |= DEATH_MASK;
    return;
  }

  p->x += p->dx;
  p->y += p->dy;
}

void
red_particle_draw( particle_t *p ) {
  SDL_FRect r = {p->x, p->y, p->w, p->h};
  SDL_Color c = {p->color.r, p->color.g, p->color.b, p->color.a};
  draw_frect( &r, &c, true, false );
}