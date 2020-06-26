#ifndef STDS_H
#define STDS_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include "stddefine.h"
#include "structs.h"

#define MAX_INT_DIGITS 11

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX3(a, b, c) (MAX(MAX(a, b), c))
#define MIN3(a, b, c) (MIN(MIN(a, b), c))


/*
 *
 */
extern int32_t 
random_int(int32_t, int32_t);


/*
 *
 */
extern float 
random_float(float, float);


/*
 *
 */
extern int32_t 
clamp(int32_t, int32_t, int32_t);


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
extern void 
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
extern float 
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
extern int32_t 
get_distance(int32_t, int32_t, int32_t, int32_t);


/*
 * Prints to the SDL LogInfo stream. This is just to 
 * prevent having to type out the long line if you
 * want to do simple debugging. Supports varargs
 * and formatting.
 * 
 * @param const char* string.
 * @param ... variable arguments.
 * 
 * @return void.
 */
extern void 
print(const char*, ...);


/*
 * Converts a float variable in degrees to radians.
 * 
 * @param float angle in degrees (0.0f to 360.0f)
 * 
 * @return float angle in radians.
 */
extern float 
to_radians(float);


/*
 *
 */
extern bool
is_mouse_over_rect(float x, float y, SDL_Rect rect);

/*
 * Finds and returns the substring between the indices 
 * [first, last). (last - first) gives the number of characters
 * inside the returning char*. 
 *
 * @precondition last > first, first >= 0 and last >= 0,
 *               first < length of str and last < length of
 *               str.
 *
 * @param char * string with substring to find.
 * @param int first index of substring.
 * @param int index to stop the search (not inclusive!).
 *
 * @return char* substring.
 */
extern char* 
str_substring(char* str, int first, int last);


/*
 * Returns the index of the first occurrence of search_str
 * inside s. 
 *
 * @param char* string to search in.
 * @param char* string to search for.
 *
 * @return int32_t >= 0 for index, -1 if not in string.
 */
extern int32_t
str_index_of( char* s, const char* search_str );

/*
 * Concatenates a signed 32-bit integer to the end of 
 * a string. 
 *
 * @param char* string to concatenate onto.
 * @param int32_t integer to concatenate.
 *
 * @return modified string with number on end.
 */ 
extern char*
strcat_int( char *s, int32_t n );

#endif