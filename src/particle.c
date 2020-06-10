#include "particle.h"

Entity* add_particle(float x, float y, float dx, float dy, float decX, float decY,
                     uint16_t w, uint16_t h, uint16_t angle, uint8_t r, uint8_t g,
                     uint8_t b, uint8_t a, float deltaAlpha, uint32_t idFlags) {
  Entity* en;

  en = malloc(sizeof(Entity));
  memset(en, 0, sizeof(Entity));

  en->x = x;
  en->y = y;
  en->w = w;
  en->h = h;
  en->dx = dx;
  en->dy = dy;
  en->life = FPS * 5;
  en->deltaAccelX = decX;
  en->deltaAccelY = decY;
  en->animation = NULL;

  SDL_Color color;
  color.r = randomInt(0x20, 0xff);
  color.g = 0;
  color.b = 0;
  color.a = 0xff;

  en->color = color;
  en->deltaAlpha = deltaAlpha;
  en->angle = angle;
  en->idFlags |= idFlags | ID_PARTICLE_MASK;
  en->flags |= ID_PARTICLE_MASK;

  return en;
}

Entity* add_animated_particle(float x, float y, float dx, float dy, float decX, float decY,
                              uint16_t angle, uint32_t idFlags, Animation* animation) {
  Entity* en;

  en = malloc(sizeof(Entity));
  memset(en, 0, sizeof(Entity));

  en->x = x;
  en->y = y;
  en->animation = animation;

  if (animation->flags & STD_ANIMATION_MASK) {
    en->w = animation->spriteSheetW / animation->numberOfFrames;
    en->h = animation->spriteSheetH / animation->numberOfFrames;
  } else {
    SDL_QueryTexture(animation->currentTexture, NULL, NULL, &en->w, &en->h);
  }

  en->dx = dx;
  en->dy = dy;

  en->life = FPS * 5;
  en->deltaAccelX = decX;
  en->deltaAccelY = decY;

  en->angle = angle;
  en->idFlags |= idFlags | ID_PARTICLE_MASK;

  return en;
}

void particle_tick(Entity* e) {
  e->life--;

  if (e->life <= 0) {
    particle_die(e);
    return;
  }

  if (e->animation != NULL) {
      e->animation->tick(e->animation);
  }

  e->dx *= e->deltaAccelX;
  e->dy *= e->deltaAccelY;

  if (e->idFlags & ID_SCATTER_PARTICLE_MASK) {
    e->dy += 0.5;
  }

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

    if (e->idFlags & ID_P_BLOOD_SQUARE_MASK) {
      drawRect(&rect, e->color.r, e->color.g, e->color.b, e->color.a, true);
    } else {
      uint32_t r = rect.w >> 1;
      fillCircle(rect.x, rect.y, r, e->color.r, e->color.g, e->color.b, e->color.a);
    }
  } else {
    e->animation->draw(e);
  }
}

void particle_die(Entity* e) {
    if (!(e->flags & DEATH_MASK)) {
      e->flags |= DEATH_MASK;
    }
}
