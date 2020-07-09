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
 * Returns a random floating point variable between
 * the interval specified, inclusive.
 *
 * @param float minimum number to choose from.
 * @param float maximum number to choose from.
 *
 * @return float random number in the set [min, max].
 */
float
random_float( float min, float max ) {
  if ( !seed ) {
    srand( ( uint32_t ) time( NULL ) );
    seed = true;
  }

  float scale = rand() / ( float ) RAND_MAX;
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
 * @param float* pointer to store x slope.
 * @param float* pointer to store y slope.
 *
 * @return void.
 */
void
calc_slope( int32_t x1, int32_t y1, int32_t x2, int32_t y2, float *dx, float *dy ) {
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
 * @return float angle.
 */
float
get_angle( int32_t x1, int32_t y1, int32_t x2, int32_t y2 ) {
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
is_mouse_over_rect( float x, float y, SDL_Rect rect ) {
  return ( x > rect.x && x < rect.x + rect.w ) && ( y > rect.y && y < rect.y + rect.h );
}

/**
 * Converts a float variable in degrees to radians.
 *
 * @param float angle in degrees (0.0f to 360.0f)
 *
 * @return float angle in radians.
 */
float
to_radians( float degrees ) {
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
float
to_degrees( float radians ) {
  return ( float ) ( radians * ( 180.0f / PI ) );
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