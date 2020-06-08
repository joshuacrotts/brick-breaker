#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "math.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"
#include "time.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include "stddefine.h"
#include "structs.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX3(a, b, c) (MAX(MAX(a, b), c))
#define MIN3(a, b, c) (MIN(MIN(a, b), c))

/*
 *
 */
uint32_t randomInt(uint32_t, uint32_t);

/*
 *
 */
float randomFloat(float, float);

/*
 *
 */
uint32_t clamp(uint32_t, uint32_t, uint32_t);

/*
 *
 */
bool collision(int, int, int, int, int, int, int, int);

/*
 *
 */
void calcSlope(int, int, int, int, float*, float*);

/*
 *
 */
float getAngle(int, int, int, int);

/*
 *
 */
int getDistance(int x1, int y1, int x2, int y2);
