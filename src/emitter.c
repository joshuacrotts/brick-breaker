#include "emitter.h"

Emitter* create_emitter(int32_t x, int32_t y, uint32_t maxParticles, uint32_t idFlags) {
  Emitter* em;
  em = malloc(sizeof(Emitter));
  memset(em, 0, sizeof(Emitter));

  em->x = x;
  em->y = y;
  em->maxParticles = maxParticles;
  em->idFlags = idFlags;
  em->particleTail = &em->particleHead;

  return em;
}

void emitter_update(Emitter* em) {
  Entity* p;
  Entity* prev;
  prev = &em->particleHead;

  spawnBloodParticles(em, em->x, em->y, 5, ID_P_BLOOD_CIRCLE_MASK);

  for (p = em->particleHead.next; p != NULL; p = p->next) {
    particle_tick(p);

    if (p->flags & DEATH_MASK) {
      if (p == em->particleTail) {
        em->particleTail = prev;
      }
      prev->next = p->next;
      free(p);
      p = prev;
    }

    prev = p;
  }
}

void emitter_draw(Emitter* em) {
  Entity* p;

  for (p = em->particleHead.next; p != NULL; p = p->next) {
    particle_draw(p);
  }
}

void spawnBloodParticles(Emitter* em, int32_t x, int32_t y, uint32_t n, uint32_t idFlags) {
  for (int i = 0; i < n; i++) {
    bool scatterParticle = randomInt(0, 1);
    float dx = randomFloat(-20, 20);
    float dy = randomFloat(-20, 20);
    float decX;
    float decY;
    float deltaAlpha;

    if (!scatterParticle) {
      decX = randomFloat(0.50, 0.70);
      decY = randomFloat(0.50, 0.70);
    } else {
      decX = randomFloat(0.70, 0.95);
      decY = randomFloat(0.70, 0.95);
      deltaAlpha = randomFloat(1, 3);
    }

    uint16_t w = randomInt(1, 10);
    uint16_t h = w;
    uint8_t r = randomInt(20, 0xff);
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 0xff;
    uint16_t angle = 0;

    Entity* en;
    en = add_particle(x, y, dx, dy, decX, decY, w, h, angle, r, g, b, a, deltaAlpha, idFlags);

    if (em != NULL) {
      em->particleTail->next = en;
      em->particleTail = en;
    } else {
      stage.entityTail->next = en;
      stage.entityTail = en;
    }
  }
}

void spawnColorfulParticles(Emitter* em, int32_t x, int32_t y, uint32_t n, uint32_t flags) {
  for (int i = 0; i < n; i++) {
    bool scatterParticle = randomInt(0, 1);
    float dx = randomFloat(-20, 20);
    float dy = randomFloat(-20, 20);
    float decX;
    float decY;
    float deltaAlpha;
    uint16_t angle = 0;
    
    if (!scatterParticle) {
      decX = randomFloat(0.50, 0.70);
      decY = randomFloat(0.50, 0.70);
    } else {
      decX = randomFloat(0.70, 0.95);
      decY = randomFloat(0.70, 0.95);
      deltaAlpha = randomFloat(1, 3);
    }

    Animation* particleAnimation;
    uint8_t animationColor = randomInt(0, 2);
    switch(animationColor) {
      case 0:
        particleAnimation = add_animation("../res/img/particles/red/p", 2, randomFloat(0.166, 0.70));
        break;
      case 1:
        particleAnimation = add_animation("../res/img/particles/blue/p", 2, randomFloat(0.166, 0.70));
        break;
      case 2:
        particleAnimation = add_animation("../res/img/particles/green/p", 2, randomFloat(0.166, 0.70));
        break;
    }

    particleAnimation->flags |= STD_ANIMATION_MASK;

    Entity* en;
    en = add_animated_particle(x, y, dx, dy, decX, decY, angle, ID_P_ANIMATED_PARTICLE_MASK, particleAnimation);

    if (em != NULL) {
      em->particleTail->next = en;
      em->particleTail = en;
    } else {
      stage.entityTail->next = en;
      stage.entityTail = en;
    }
  }
}
