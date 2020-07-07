#ifndef STDS_H
#define STDS_H

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include "stddefine.h"
#include "structs.h"

#define MAX_INT_DIGITS 11

#define MAX( a, b )     ( ( a ) > ( b ) ? ( a ) : ( b ) )
#define MIN( a, b )     ( ( a ) < ( b ) ? ( a ) : ( b ) )
#define MAX3( a, b, c ) ( MAX( MAX( a, b ), c ) )
#define MIN3( a, b, c ) ( MIN( MIN( a, b ), c ) )

/**
 * Returns a random integer variable between
 * the interval specified, inclusive.
 *
 * @param int32_t minimum number to choose from.
 * @param int32_t maximum number to choose from.
 *
 * @return int32_t random number in the set [min, max].
 */
extern int32_t random_int( int32_t min, int32_t max );

/**
 * Returns a random floating point variable between
 * the interval specified, inclusive.
 *
 * @param float minimum number to choose from.
 * @param float maximum number to choose from.
 *
 * @return float random number in the set [min, max].
 */
extern float random_float( float min, float max );

/**
 * Bounds an integer n in-between the interval [min, max].
 *
 * @param int32_t* pointer to number to clamp.
 * @param int32_t min number n can be (n >= min).
 * @param int32_t max number n can be (n <= max).
 */
extern void clamp( int32_t *n, int32_t min, int32_t max );

/**
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
extern void calc_slope( int32_t x1, int32_t y1, int32_t x2, int32_t y2, float *x_slope, float *y_slope );

/**
 * Calculates the angle between two points.
 *
 * @param int32_t x1
 * @param int32_t y1
 * @param int32_t x2
 * @param int32_t y2
 *
 * @return float angle.
 */
extern float get_angle( int32_t x1, int32_t y1, int32_t x2, int32_t y2 );

/**
 * Calculates the distance between two points.
 *
 * @param int32_t x1
 * @param int32_t y1
 * @param int32_t x2
 * @param int32_t y2
 *
 * @return int32_t distance.
 */
extern int32_t get_distance( int32_t x1, int32_t y1, int32_t x2, int32_t y2 );

/**
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
extern void print( const char * s, ... );

/**
 * Converts a float variable in degrees to radians.
 *
 * @param float angle in degrees (0.0f to 360.0f)
 *
 * @return float angle in radians.
 */
extern float to_radians( float degree_angle );

/**
 * Converts a float variable in radians to degrees.
 * This is best used with the tangental functions.
 *
 * @param float angle in radians (0 to 2PI)
 *
 * @return float angle in degrees.
 */
extern float to_degrees( float radian_angle );

/*
 *
 */
extern bool is_mouse_over_rect( float x, float y, SDL_Rect rect );

/**
 * Finds and returns the substring between the indices
 * [first, last). (last - first) gives the number of characters
 * inside the returning char*.
 *
 * @precondition last > first, first >= 0 and last >= 0,
 *               first < length of str and last < length of
 *               str.
 *
 * @param const char * string with substring to find.
 * @param int first index of substring.
 * @param int index to stop the search (not inclusive!).
 *
 * @return char* substring.
 */
extern char *str_substring( const char *str, int first, int last );

/**
 * Returns the index of the first occurrence of search_str
 * inside s.
 *
 * @param const char* string to search in.
 * @param const char* string to search for.
 *
 * @return int32_t >= 0 for index, -1 if not in string.
 */
extern int32_t str_index_of( const char *s, const char *search_str );

/**
 * Concatenates a signed 32-bit integer to the end of
 * a string. 
 *
 * @param const char* string to concatenate onto.
 * @param int32_t integer to concatenate.
 *
 * @return void.
 */
extern char * strcat_int( const char *s, int32_t n );

#endif // STDS_H