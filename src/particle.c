#include "../include/particle.h"

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
  color.r = r;
  color.g = g;
  color.b = b;
  color.a = a;

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

void particle_update(Entity* e) {
  e->life--;
  if (e->life <= 0) {
    e->flags |= DEATH_MASK;
    return;
  }

  if (e->animation != NULL) {
      animation_update(e);
  }

  if (floor(e->deltaAccelX) != 0) {
    e->dx *= e->deltaAccelX;
  }

  if (floor(e->deltaAccelY) != 0) {
    e->dy *= e->deltaAccelY;
  }

  if (e->idFlags & ID_SCATTER_PARTICLE_MASK) {
    e->dy += 0.5f;
  } else if (e->idFlags & ID_P_STAR_MASK) {
    if (e->y < -100) {
      e->flags |= DEATH_MASK;
    }
  }
  
  int16_t tmp_alpha = (int16_t) (e->color.a + e->deltaAlpha);
  
  if (tmp_alpha < 0) {
    tmp_alpha = 0;
  } 

  e->color.a = tmp_alpha;
  e->x += e->dx;
  e->y += e->dy;
}

void particle_draw(Entity* e) {
  if (e->animation == NULL) {
    SDL_Rect rect;
    rect.x = (int32_t) (e->x - app.camera.x);
    rect.y = (int32_t) (e->y - app.camera.y);
    rect.w = e->w;
    rect.h = e->h;
    if (e->idFlags & ID_P_SQUARE_MASK) {
      drawRect(&rect, e->color.r, e->color.g, e->color.b, e->color.a, true);
    } else if (e->idFlags & ID_P_CIRCLE_MASK) {
      uint32_t r = rect.w >> 1;
      fillCircle(rect.x, rect.y, r, e->color.r, e->color.g, e->color.b, e->color.a);
    }
  } else {
    animation_draw(e);
  }
}

void particle_die(Entity* e) {
  free(e);
}
