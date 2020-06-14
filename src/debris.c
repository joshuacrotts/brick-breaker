#include "debris.h"

void add_debris(Entity* parentBrick, uint32_t flags) {
  Debris* d;
  int x, y, w, h;


  // Create really small bricks.
  w = parentBrick->w >> 4;
  h = parentBrick->h >> 4;

  for (y = 0; y <= h * 2; y += h) {
    for (x = 0; x <= w * 2; x += w) {
      d = malloc(sizeof(Debris));
      memset(d, 0, sizeof(Debris));
      stage.debrisTail->next = d;
      stage.debrisTail = d;

      d->x = parentBrick->x + parentBrick->w / 2;
      d->y = parentBrick->y + parentBrick->h / 2;
      d->dx = randomFloat(0, 5) - randomFloat(0, 5);
      d->dy = randomFloat(-1, 1);
      d->texture = parentBrick->texture;

      d->rect.x = x;
      d->rect.y = y;
      d->rect.w = w;
      d->rect.h = h;
    }
  }
}

void debris_update(Debris* d) {
    d->x += d->dx;
    d->y += d->dy;

    d->dy += 0.5f;

    if (d->y > SCREEN_HEIGHT) {
        d->flags |= DEATH_MASK;
        return;
    }
}

void debris_draw(Debris* d) {
    blitRect(d->texture, &d->rect, d->x, d->y);
}

void debris_die(Debris* d) {
    free(d);
}