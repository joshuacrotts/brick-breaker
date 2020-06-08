#include "particle.h"

Entity* add_particle(float x, float y, float dx, float dy, float decX, float decY,
                     uint16_t w, uint16_t h, uint16_t angle,
                     uint8_t r, uint8_t g, uint8_t b, uint8_t a, float deltaAlpha) {
  Entity* e;

  e = malloc(sizeof(Entity));
  memset(e, 0, sizeof(Entity));

  e->x = x;
  e->y = y;
  e->w = w;
  e->h = h;
  e->dx = dx;
  e->dy = dy;
  e->deltaAccelX = decX;
  e->deltaAccelY = decY;
  e->life = FPS * 5;

  SDL_Color color;
  color.r = r;
  color.g = g;
  color.b = b;
  color.a = a;
  e->color = color;
  e->deltaAlpha = deltaAlpha;
  e->angle = angle;
  e->idFlags |= ID_PARTICLE_MASK;

  e->draw = particle_draw;
  e->tick = particle_tick;
  e->die = particle_die;

  return e;
}

void particle_tick(Entity* e) {
  e->life--;
  int16_t currAlpha = e->color.a;
  currAlpha -= (int16_t) e->deltaAlpha;

  if (e->life <= 0 || currAlpha <= 0) {
    e->color.a = 0;
    e->die(e);
    return;
  }

  e->color.a = currAlpha;

  e->dx *= e->deltaAccelX;
  e->dy *= e->deltaAccelY;

  e->x += e->dx;
  e->y += e->dy;
}

void particle_draw(Entity* e) {
  SDL_Rect rect;

  rect.x = e->x - app.camera.x;
  rect.y = e->y - app.camera.y;
  rect.w = e->w;
  rect.h = e->h;

  drawRect(&rect, e->color.r, e->color.g, e->color.b, e->color.a, true);
}

void particle_die(Entity* e) {
    if (!(e->flags & DEATH_MASK)) {
      e->flags |= DEATH_MASK;
    }
}
