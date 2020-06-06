#include "stds.h"

static bool seed = false;

/*
 *
 */
int randomInt(int min, int max) {
  if (!seed) {
    srand((unsigned int) time(NULL));
    seed = true;
  }
  return (rand() % (max - min + 1)) + min;
}

/*
 *
 */
float randomFloat(float min, float max) {
  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}

/*
 *
 */
int clamp(int value, int min, int max) {
  int newValue = value;
  if (value < min) {
    value = min;
  } else if (value > max) {
    value = max;
  }

  return newValue;
}

/*
 *
 */
int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
  return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}

/*
 *
 */
void calcSlope(int x1, int y1, int x2, int y2, float* dx, float* dy) {
  int steps = MAX(abs(x1 - x2), abs(y1 - y2));

  if (steps == 0) {
    *dx = *dy = 0;
    return;
  }

  *dx = (x1 - x2);
  *dx /= steps;

  *dy = (y1 - y2);
  *dy /= steps;
}
