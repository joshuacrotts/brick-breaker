#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "math.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

#include "defs.h"
#include "structs.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int randomInt(int, int);
float randomFloat(float, float);
int clamp(int, int, int);
int collision(int, int, int, int, int, int, int, int);
void calcSlope(int, int, int, int, float*, float*);
