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
  e->life = FPS * 5;
  e->deltaAccelX = decX;
  e->deltaAccelY = decY;

  SDL_Color color;
  color.r = randomInt(0x20, 0xff);
  color.g = 0;
  color.b = 0;
  color.a = 0xff;

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
  //int16_t currAlpha = e->color.a;
  //int16_t currAlpha -= (int16_t) e->deltaAlpha;

  if (e->life <= 0) {
    e->die(e);
    return;
  }

  if (e->animation != NULL) {
      e->animation->tick(e->animation);
  }

  e->dx *= e->deltaAccelX;
  e->dy *= e->deltaAccelY;

  e->x += e->dx;
  e->y += e->dy;
}

void particle_draw(Entity* e) {
  if (e->animation == NULL) {
    SDL_Rect rect;

    rect.x = e->x - app.camera.x;
    rect.y = e->y - app.camera.y;
    rect.w = e->w;
    rect.h = e->h;
    drawRect(&rect, e->color.r, e->color.g, e->color.b, e->color.a, true);
  } else {
    e->animation->draw(e, e->animation);
  }
}

void particle_die(Entity* e) {
    if (!(e->flags & DEATH_MASK)) {
      e->flags |= DEATH_MASK;
    }
}
