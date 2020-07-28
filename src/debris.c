#include "../include/debris.h"

void
add_debris( struct entity_t *parentBrick, uint32_t flags ) {
  debris_t *d;
  int       x, y, w, h;

  // Create really small bricks.
  w = parentBrick->w >> 4;
  h = parentBrick->h >> 4;

  for ( y = 0; y <= h * 2; y += h ) {
    for ( x = 0; x <= w * 2; x += w ) {
      d = malloc( sizeof( debris_t ) );
      memset( d, 0, sizeof( debris_t ) );
      stage.debris_tail->next = d;
      stage.debris_tail       = d;

      d->x       = parentBrick->x + parentBrick->w / 2;
      d->y       = parentBrick->y + parentBrick->h / 2;
      d->dx      = Stds_RandomFloat( -5.0f, 5.0f );
      d->dy      = Stds_RandomFloat( 1.0f, 2.0f );
      d->texture = parentBrick->texture[0];

      d->rect.x = x;
      d->rect.y = y;
      d->rect.w = w;
      d->rect.h = h;
    }
  }
}

void
debris_update( debris_t *d ) {
  d->x += d->dx;
  d->y += d->dy;

  d->dy += 0.5f;

  if ( d->y > app.SCREEN_HEIGHT ) {
    d->flags |= STDS_DEATH_MASK;
    return;
  }
}

void
debris_draw( debris_t *d ) {
  Stds_BlitTexture( d->texture, &d->rect, d->rect.x, d->rect.y, d->rect.w, d->rect.h, 0,
                    SDL_FLIP_NONE, NULL, false );
}

void
debris_die( debris_t *d ) {
  free( d );
}