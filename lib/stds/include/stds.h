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
int32_t 
random_int(int32_t, int32_t);


/*
 *
 */
float 
random_float(float, float);


/*
 *
 */
int32_t 
clamp(int32_t, int32_t, int32_t);


/*
 *
 */
bool 
collision(float, float, int32_t, int32_t, float, float, int32_t, int32_t);


/*
 * Calculates the slope between two lines, and stores the x/y result in the pointers
 * defined by the last two parameters.
 * 
 * @param int32_t x1
 * @param int32_t y1
 * @param int32_t x2
 * @param int32_t y2
 * @param float* pointer to store x slope.
 * @param float* pointer to store y slope.
 * 
 * @return void.
 */
void 
calc_slope(int32_t, int32_t, int32_t, int32_t, float*, float*);


/*
 * Calculates the angle between two points.
 * 
 * @param int32_t x1
 * @param int32_t y1
 * @param int32_t x2
 * @param int32_t y2
 * 
 * @return float angle.
 */
float 
get_angle(int32_t, int32_t, int32_t, int32_t);


/*
 * Calculates the distance between two points.
 * 
 * @param int32_t x1
 * @param int32_t y1
 * @param int32_t x2
 * @param int32_t y2
 * 
 * @return int32_t distance.
 */
int32_t 
get_distance(int32_t, int32_t, int32_t, int32_t);


/*
 *
 */
void 
print(const char*, ...);


/*
 *
 */
float 
to_radians(float);