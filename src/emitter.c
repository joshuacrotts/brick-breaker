#include "../include/emitter.h"

emitter_t *
add_emitter( int32_t x, int32_t y, uint32_t maxParticles, uint32_t id_flags ) {
  emitter_t *em;
  em = malloc( sizeof( emitter_t ) );
  memset( em, 0, sizeof( emitter_t ) );

  em->x             = x;
  em->y             = y;
  em->maxParticles  = maxParticles;
  em->id_flags      = id_flags;
  em->particle_tail = &em->particle_head;

  return em;
}

void
emitter_update( emitter_t *em ) {
  entity_t *p;
  entity_t *prev;
  prev = &em->particle_head;

  for ( p = em->particle_head.next; p != NULL; p = p->next ) {
    particle_update( p );

    if ( p->flags & DEATH_MASK ) {
      if ( p == em->particle_tail ) {
        em->particle_tail = prev;
      }

      prev->next = p->next;
      particle_die( p );
      p = prev;
    }

    prev = p;
  }
}

void
emitter_draw( emitter_t *em ) {
  entity_t *p;

  for ( p = em->particle_head.next; p != NULL; p = p->next ) {
    particle_draw( p );
  }
}

void
spawn_blood_particles( emitter_t *em, int32_t x, int32_t y, uint32_t n, uint32_t id_flags ) {
  for ( int i = 0; i < n; i++ ) {
    bool  scatterParticle = random_int( 0, 1 );
    float dx              = random_float( -20.0f, 20.0f );
    float dy              = random_float( -15.0f, 10.0f );
    float decX;
    float decY;
    float delta_alpha;

    if ( !scatterParticle ) {
      decX = random_float( 0.50f, 0.70f );
      decY = random_float( 0.50f, 0.70f );
    } else {
      decX        = random_float( 0.70f, 0.95f );
      decY        = random_float( 0.70f, 0.95f );
      delta_alpha = random_float( 1.0f, 3.0f );
    }

    uint16_t w     = random_int( 1, 10 );
    uint16_t h     = w;
    uint8_t  r     = random_int( 20, 0xff );
    uint8_t  g     = 0;
    uint8_t  b     = 0;
    uint8_t  a     = 0xff;
    uint16_t angle = 0;

    entity_t *en;
    en = add_particle( x, y, dx, dy, decX, decY, w, h, angle, r, g, b, a, delta_alpha, id_flags );

    if ( em != NULL ) {
      em->particle_tail->next = en;
      em->particle_tail       = en;
    } else {
      currentLevel->entity_tail->next = en;
      currentLevel->entity_tail       = en;
    }
  }
}

void
spawn_star_particles( emitter_t *em, int32_t x, int32_t y, uint32_t n, uint32_t flags ) {
  for ( int i = 0; i < n; i++ ) {
    float dx = -10;
    float dy = -10;

    uint16_t w = random_int( 1, 4 );
    uint16_t h = w;
    uint8_t  r = 0xff;
    uint8_t  g = 0xff;
    uint8_t  b = 0xff;
    uint8_t  a = random_int( 10, 40 );

    entity_t *en;
    en = add_particle( x, y, dx, dy, 0, 0, w, h, 0, r, g, b, a, 0, flags | ID_P_SQUARE_MASK );
    if ( em != NULL ) {
      em->particle_tail->next = en;
      em->particle_tail       = en;
    } else {
      currentLevel->entity_tail->next = en;
      currentLevel->entity_tail       = en;
    }
  }
}

void
spawn_colorful_particles( emitter_t *em, int32_t x, int32_t y, uint32_t n, uint32_t flags ) {

  for ( int i = 0; i < n; i++ ) {
    bool  scatterParticle = random_int( 0, 1 );
    float dx              = random_float( -10.0f, 10.0f );
    float dy              = random_float( -15.0f, 10.0f );
    float decX;
    float decY;
    float delta_alpha;

    uint16_t angle = 0;

    if ( !scatterParticle ) {
      decX = random_float( 0.50f, 0.70f );
      decY = random_float( 0.50f, 0.70f );
    } else {
      decX        = random_float( 0.70f, 0.95f );
      decY        = random_float( 0.70f, 0.95f );
      delta_alpha = random_float( 1.0f, 3.0f );
    }

    animation_t *particleAnimation;
    uint8_t      animationColor = random_int( 0, 2 );
    switch ( animationColor ) {
    case 0:
      particleAnimation =
          add_animation( "res/img/particles/red/p", 2, random_float( 0.166f, 0.70f ) );
      break;
    case 1:
      particleAnimation =
          add_animation( "res/img/particles/blue/p", 2, random_float( 0.166f, 0.70f ) );
      break;
    case 2:
      particleAnimation =
          add_animation( "res/img/particles/green/p", 2, random_float( 0.166f, 0.70f ) );
      break;
    }

    particleAnimation->flags |= STD_ANIMATION_MASK;

    entity_t *en;
    en = add_animated_particle( x, y, dx, dy, decX, decY, angle, ID_P_ANIMATED_PARTICLE_MASK,
                                particleAnimation );

    if ( em != NULL ) {
      em->particle_tail->next = en;
      em->particle_tail       = en;
    } else {
      currentLevel->entity_tail->next = en;
      currentLevel->entity_tail       = en;
    }
  }
}
