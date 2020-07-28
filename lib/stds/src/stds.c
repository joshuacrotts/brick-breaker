//=============================================================================================//
// FILENAME :       stds.c
//
// DESCRIPTION :
//        This file defines the standard functions and procedures for math, trigonometry,
//        simple non string.h string manipulation, random numbers, etc. stds.h also defines
//        a few simple macros for min and max.
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
 * Sets the seed for the randomization. This should be called prior to
 * any RNG. It is called by default in the init.c file.
 * @param void.
 *
 * @return void.
 */
void
Stds_SetRandomSeed( void ) {
  if ( !seed ) {
    srand( ( uint32_t ) time( NULL ) );
    seed = true;
  }
}

/**
 * Returns a random integer variable between
 * the interval specified, inclusive.
 *
 * @param int32_t minimum number to choose from.
 * @param int32_t maximum number to choose from.
 *
 * @return int32_t random number in the set [min, max].
 */
inline int32_t
Stds_RandomInt( const int32_t min, const int32_t max ) {
  return ( rand() % ( max - min + 1 ) ) + min;
}

/**
 * Generates a 32-bit integer number between [min, min_upper_bound) U (max_lower_bound, max).
 * For instance, to generate a number between -10 and 10, but no lower than
 * -5 or 5, do Stds_RandomIntBounded( -10, -5, 5, 10). Precision doesn't really matter;
 *
 * @param min
 * @param min_upper_bound
 * @param max_lower_bound
 * @param max
 *
 * In the end,
 * @return min ≤ x ≤ min_upper_bound OR max_lower_bound ≤ x ≤ max;
 */
inline int32_t
Stds_RandomIntBounded( const int32_t min, const int32_t min_upper_bound,
                       const int32_t max_lower_bound, const int32_t max ) {
  int32_t n;
  do {
    n = Stds_RandomInt( min, max );
  } while ( ( n < min || n > min_upper_bound ) && ( n < max_lower_bound || n > max ) );
  return n;
}

/**
 * Returns a random floating point variable between
 * the interval specified, inclusive.
 *
 * @param float minimum number to choose from.
 * @param float maximum number to choose from.
 *
 * @return float random number in the set [min, max].
 */
inline float
Stds_RandomFloat( const float min, const float max ) {
  float scale = rand() / ( float ) RAND_MAX;
  return min + scale * ( max - min );
}

/**
 * Generates a floating-point number between [min, min_upper_bound) U (max_lower_bound, max).
 * For instance, to generate a number between -10.f and 10.f, but no lower than
 * -5.f or 5.f, do Stds_RandomFloatBounded( -10.f, -5.f, 5.f, 10.f). Precision doesn't really
 * matter;
 *
 * @param min
 * @param min_upper_bound
 * @param max_lower_bound
 * @param max
 *
 * In the end,
 * @return min ≤ x ≤ min_upper_bound OR max_lower_bound ≤ x ≤ max;
 */
inline float
Stds_RandomFloatBounded( const float min, const float min_upper_bound, const float max_lower_bound,
                         const float max ) {
  float n;
  do {
    n = Stds_RandomFloat( min, max );
  } while ( ( n < min || n > min_upper_bound ) && ( n < max_lower_bound || n > max ) );
  return n;
}

/**
 * Bounds an integer n in-between the interval [min, max].
 *
 * @param int32_t* pointer to number to Stds_ClampInt.
 * @param int32_t min number n can be (n >= min).
 * @param int32_t max number n can be (n <= max).
 *
 * @return void.
 */
void
Stds_ClampInt( int32_t *value, const int32_t min, const int32_t max ) {
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
 * @param float* pointer to store x slope.
 * @param float* pointer to store y slope.
 *
 * @return void.
 */
void
Stds_CalcSlope( const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2, float *dx,
                float *dy ) {
  int32_t steps = ( int32_t ) fmax( abs( x1 - x2 ), abs( y1 - y2 ) );

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
 * @return float angle.
 */
inline float
Stds_GetAngle( const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2 ) {
  float angle = ( float ) ( -90.0f + atan2( y1 - y2, x1 - x2 ) * ( 180.0f / PI ) );
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
inline int32_t
Stds_GetDistance( const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2 ) {
  int32_t x = x2 - x1;
  int32_t y = y2 - y1;

  return ( int32_t ) sqrt( x * x + y * y );
}

/**
 * Stds_Prints to the SDL LogInfo stream. This is just to
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
Stds_Print( const char *str, ... ) {
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
inline bool
Stds_IsMouseOverRect( const float x, const float y, const SDL_Rect *rect ) {
  return ( x > rect->x && x < rect->x + rect->w ) && ( y > rect->y && y < rect->y + rect->h );
}

/**
 * Converts a float variable in degrees to radians.
 *
 * @param float angle in degrees (0.0f to 360.0f)
 *
 * @return float angle in radians.
 */
inline float
Stds_ToRadians( const float degrees ) {
  return ( float ) ( degrees * ( PI / 180.0f ) );
}

/**
 * Converts a float variable in radians to degrees.
 * This is best used with the tangental functions.
 *
 * @param float angle in radians (0 to 2PI)
 *
 * @return float angle in degrees.
 */
inline float
Stds_ToDegrees( const float radians ) {
  return ( float ) ( radians * ( 180.0f / PI ) );
}

/**
 * Converts an integer into an SDL_Color object. The number should
 * be an unsigned 32-bit integer in the form
 *
 * 0xAARRGGBB (ARGB)
 *
 * @param uint32_t color to be converted.
 *
 * @return SDL_Color object.
 */
SDL_Color
Stds_ConvertARGBToColor( const uint32_t c ) {
  uint8_t   r     = c >> 16 & 0xff;
  uint8_t   g     = c >> 8 & 0xff;
  uint8_t   b     = c & 0xff;
  uint8_t   a     = c >> 24 & 0xff;
  SDL_Color color = {r, g, b, a};
  return color;
}

/**
 * Converts a SDL_Color object into an unsigned 32bit integer.
 *
 * @param SDL_Color * color to be converted.
 *
 * @return uint32_t color integer representation.
 */
uint32_t
Stds_ConvertColorToARGB( const SDL_Color *c ) {
  uint32_t color;
  color |= c->a << 24;
  color |= c->r << 16;
  color |= c->g << 8;
  color |= c->b;

  return color;
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
 * @param int32_t first index of substring.
 * @param int32_t index to stop the search (not inclusive!).
 *
 * @return char* substring.
 */
char *
Stds_Substring( const char *str, const int32_t first, const int32_t last ) {
  uint32_t s_len = strlen( str );

  /* Primitive error checking... */
  if ( s_len <= 0 ) {
    Stds_Print( "Error: your string cannot be empty: %d.\n", s_len );
    exit( EXIT_FAILURE );
  } else if ( first >= last ) {
    Stds_Print( "Error:: your first index %d cannot more than or equal to your last %d.\n", first,
                last );
    exit( EXIT_FAILURE );
  } else if ( first < 0 ) {
    Stds_Print( "Error: your first index cannot be less than 0. %d.\n", first );
    exit( EXIT_FAILURE );
  } else if ( last >= s_len ) {
    Stds_Print( "Error: your last index cannot be >= length of your string. %d.\n", last );
    exit( EXIT_FAILURE );
  }

  memset( text_buffer, 0, sizeof( MAX_LINE_LENGTH ) );
  memcpy( text_buffer, str + first, last - first );
  return text_buffer;
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
Stds_IndexOf( const char *s, const char *search_str ) {
  uint32_t s_len          = strlen( s );
  uint32_t search_str_len = strlen( search_str );

  if ( s_len <= 0 ) {
    Stds_Print( "Error: your string cannot be empty: %d.\n", s_len );
    exit( EXIT_FAILURE );
  } else if ( s_len < search_str_len ) {
    Stds_Print( "Error: your string length of %d is less than your search string length of %d.\n",
                s_len, search_str_len );
    exit( EXIT_FAILURE );
  }

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
Stds_StrCatIntPtr( const char *s, const int32_t n ) {
  memset( text_buffer, '\0', sizeof( text_buffer ) );
  strncat( text_buffer, s, strlen( s ) );
  int32_t digits = sprintf( number_buffer, "%d", n );
  strncat( text_buffer, number_buffer, digits );
  return text_buffer;
}

/**
 *
 */
char *
Stds_StrCatIntArray( const char s[], const int32_t n ) {
  memset( text_buffer, '\0', sizeof( text_buffer ) );
  strncat( text_buffer, s, strlen( s ) );
  int32_t digits = sprintf( number_buffer, "%d", n );
  strncat( text_buffer, number_buffer, digits );
  return text_buffer;
}