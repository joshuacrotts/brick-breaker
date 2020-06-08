#include "stds.h"

static bool seed = false;

uint32_t randomInt(uint32_t min, uint32_t max) {
  if (!seed) {
    srand((uint32_t) time(NULL));
    seed = true;
  }
  return (rand() % (max - min + 1)) + min;
}

float randomFloat(float min, float max) {
  float scale = rand() / (float) RAND_MAX;
  return min + scale * (max - min);
}

uint32_t clamp(uint32_t value, uint32_t min, uint32_t max) {
  int newValue = value;
  if (value < min) {
    value = min;
  } else if (value > max) {
    value = max;
  }

  return newValue;
}

bool collision(int32_t x1, int32_t y1, int32_t w1, int32_t h1, int32_t x2, int32_t y2, int32_t w2, int32_t h2) {
  return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}

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

float getAngle(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
  float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
  return angle >= 0 ? angle : 360 + angle;
}

int getDistance(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
  int x = x2 - x1;
  int y = y2 - y1;

  return sqrt(x * x + y * y);
}
