//=============================================================================================//
// FILENAME :       stds.c
//
// DESCRIPTION :
//        This file defines the standard functions and procedures for math, trigonometry,
//        simple non string.h string manipulation, random numbers, etc. stds.h also defines
//        a few simple macros for min and max.
//
// PUBLIC FUNCTIONS :
//        int32_t   random_int( int32_t min, int32_t max );
//        int32_t   str_index_of( const char *s, const char *search_str );
//        int32_t   get_distance( int32_t x1, int32_t y1, int32_t x2, int32_t y2 );
//        f32     random_f32( f32 min, f32 max );
//        f32     get_angle( int32_t x1, int32_t y1, int32_t x2, int32_t y2 );
//        f32     to_radians( f32 degree_angle );
//        f32     to_degrees( f32 radian_angle );
//        bool      is_mouse_over_rect( f32 x, f32 y, SDL_Rect rect );
//        char      *str_substring( const char *str, int first, int last );
//        char      *strcat_int( const char *s, int32_t n );
//        void      clamp( int32_t *n, int32_t min, int32_t max );
//        void      calc_slope( int32_t x1, int32_t y1, int32_t x2, int32_t y2, f32 *x_slope, f32 *y_slope );
//        void      print( const char * s, ... );
//
// NOTES :
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.
//
// AUTHOR :   Joshua Crotts        START DATE :    18 Jun 2020
//
//=============================================================================================//

#include "../include/stds.h"

static char number_buffer[MAX_INT_DIGITS];
static char text_buffer[MAX_LINE_LENGTH];
static bool seed = false;

/**
 * Returns a random integer variable between
 * the interval specified, inclusive.
 *
 * @param int32_t minimum number to choose from.
 * @param int32_t maximum number to choose from.
 *
 * @return int32_t random number in the set [min, max].
 */
int32_t
random_int( int32_t min, int32_t max ) {
  if ( !seed ) {
    srand( ( uint32_t ) time( NULL ) );
    seed = true;
  }
  return ( rand() % ( max - min + 1 ) ) + min;
}

/**
 * Returns a random f32ing point variable between
 * the interval specified, inclusive.
 *
 * @param f32 minimum number to choose from.
 * @param f32 maximum number to choose from.
 *
 * @return f32 random number in the set [min, max].
 */
f32
random_f32( f32 min, f32 max ) {
  if ( !seed ) {
    srand( ( uint32_t ) time( NULL ) );
    seed = true;
  }

  f32 scale = rand() / ( f32 ) RAND_MAX;
  return min + scale * ( max - min );
}

/**
 * Bounds an integer n in-between the interval [min, max].
 *
 * @param int32_t* pointer to number to clamp.
 * @param int32_t min number n can be (n >= min).
 * @param int32_t max number n can be (n <= max).
 *
 * @return void.
 */
void
clamp( int32_t *value, int32_t min, int32_t max ) {
  if ( *value < min ) {
    *value = min;
  } else if ( *value > max ) {
    *value = max;
  }
}

/**
 * Calculates the slope between two lines, and stores the x/y result in the pointers
 * defined by the last two parameters.
 *
 * @param int32_t x1
 * @param int32_t y1
 * @param int32_t x2
 * @param int32_t y2
 * @param f32* pointer to store x slope.
 * @param f32* pointer to store y slope.
 *
 * @return void.
 */
void
calc_slope( int32_t x1, int32_t y1, int32_t x2, int32_t y2, f32 *dx, f32 *dy ) {
  int32_t steps = MAX( abs( x1 - x2 ), abs( y1 - y2 ) );

  if ( steps == 0 ) {
    *dx = *dy = 0;
    return;
  }

  *dx = ( x1 - x2 );
  *dx /= steps;

  *dy = ( y1 - y2 );
  *dy /= steps;
}

/**
 * Calculates the angle between two points.
 *
 * @param int32_t x1
 * @param int32_t y1
 * @param int32_t x2
 * @param int32_t y2
 *
 * @return f32 angle.
 */
f32
get_angle( int32_t x1, int32_t y1, int32_t x2, int32_t y2 ) {
  f32 angle = ( f32 ) ( -90.0f + atan2( y1 - y2, x1 - x2 ) * ( 180.0f / PI ) );
  return angle >= 0 ? angle : 360.0f + angle;
}

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
int32_t
get_distance( int32_t x1, int32_t y1, int32_t x2, int32_t y2 ) {
  int x = x2 - x1;
  int y = y2 - y1;

  return ( int32_t ) sqrt( x * x + y * y );
}

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
void
print( const char *str, ... ) {
  va_list args;
  memset( &text_buffer, '\0', sizeof( text_buffer ) );

  va_start( args, str );
  vsprintf( text_buffer, str, args );
  va_end( args );

  SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "%s", text_buffer );
}

/**
 *
 *
 * @param
 * @param
 * @param
 *
 * @return
 */
bool
is_mouse_over_rect( f32 x, f32 y, SDL_Rect rect ) {
  return ( x > rect.x && x < rect.x + rect.w ) && ( y > rect.y && y < rect.y + rect.h );
}

/**
 * Converts a f32 variable in degrees to radians.
 *
 * @param f32 angle in degrees (0.0f to 360.0f)
 *
 * @return f32 angle in radians.
 */
f32
to_radians( f32 degrees ) {
  return ( f32 ) ( degrees * ( PI / 180.0f ) );
}

/**
 * Converts a f32 variable in radians to degrees.
 * This is best used with the tangental functions.
 *
 * @param f32 angle in radians (0 to 2PI)
 *
 * @return f32 angle in degrees.
 */
f32
to_degrees( f32 radians ) {
  return ( f32 ) ( radians * ( 180.0f / PI ) );
}

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
char *
str_substring( const char *str, int first, int last ) {
  uint32_t s_len = strlen( str );
  assert( s_len > 0 && first < last && first >= 0 && last <= s_len );

  char *s = malloc( sizeof( char ) * ( last - first ) );
  memcpy( s, str + first, last - first );
  return s;
}

/**
 * Returns the index of the first occurrence of search_str
 * inside s.
 *
 * @param const char* string to search in.
 * @param const char* string to search for.
 *
 * @return int32_t >= 0 for index, -1 if not in string.
 */
int32_t
str_index_of( const char *s, const char *search_str ) {
  uint32_t s_len          = strlen( s );
  uint32_t search_str_len = strlen( search_str );

  assert( s_len > 0 && s_len >= search_str_len );

  const char *ptr = strstr( s, search_str );

  if ( ptr ) {
    int32_t index = ptr - s;
    return index;
  }

  return -1;
}

/**
 * Concatenates a signed 32-bit integer to the end of
 * a string.
 *
 * @param const char* string to concatenate onto.
 * @param int32_t integer to concatenate.
 *
 * @return void.
 */
char *
strcat_int( const char *s, int32_t n ) {
  memset( text_buffer, '\0', sizeof( text_buffer ) );
  strncat( text_buffer, s, strlen( s ) );
  int32_t digits = sprintf( number_buffer, "%d", n );
  strncat( text_buffer, number_buffer, digits );
  return text_buffer;
}