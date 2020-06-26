#include "../include/stds.h"

static char text_buffer[MAX_LINE_LENGTH];
static bool seed = false;

int32_t
random_int( int32_t min, int32_t max ) {
  if ( !seed ) {
    srand( ( uint32_t ) time( NULL ) );
    seed = true;
  }
  return ( rand() % ( max - min + 1 ) ) + min;
}

float
random_float( float min, float max ) {
  if ( !seed ) {
    srand( ( uint32_t ) time( NULL ) );
    seed = true;
  }

  float scale = rand() / ( float ) RAND_MAX;
  return min + scale * ( max - min );
}

int32_t
clamp( int32_t value, int32_t min, int32_t max ) {
  int newValue = value;
  if ( value < min ) {
    newValue = min;
  } else if ( value > max ) {
    newValue = max;
  }

  return newValue;
}

void
calc_slope( int x1, int y1, int x2, int y2, float *dx, float *dy ) {
  int steps = MAX( abs( x1 - x2 ), abs( y1 - y2 ) );

  if ( steps == 0 ) {
    *dx = *dy = 0;
    return;
  }

  *dx = ( x1 - x2 );
  *dx /= steps;

  *dy = ( y1 - y2 );
  *dy /= steps;
}

float
get_angle( int32_t x1, int32_t y1, int32_t x2, int32_t y2 ) {
  float angle = ( float ) ( -90 + atan2( y1 - y2, x1 - x2 ) * ( 180 / PI ) );
  return angle >= 0 ? angle : 360 + angle;
}

int32_t
get_distance( int32_t x1, int32_t y1, int32_t x2, int32_t y2 ) {
  int x = x2 - x1;
  int y = y2 - y1;

  return ( int32_t ) sqrt( x * x + y * y );
}

void
print( const char *str, ... ) {
  va_list args;
  memset( &text_buffer, '\0', sizeof( text_buffer ) );

  va_start( args, str );
  vsprintf( text_buffer, str, args );
  va_end( args );

  SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, text_buffer );
}

bool is_mouse_over_rect( float x, float y, SDL_Rect rect ){
	return ( x > rect.x && x < rect.x + rect.w ) && ( y > rect.y && y < rect.y + rect.h );
}

float
to_radians( float degrees ) {
  return ( float ) ( degrees * ( PI / 180.0 ) );
}

char *
str_substring( char *str, int first, int last ) {
  char *s = malloc( sizeof( char ) * ( last - first ) );
  memcpy( s, str + first, last - first );
  return s;
}

int32_t
str_index_of( char *s, const char *search_str ) {
  const char *ptr = strstr( s, search_str );

  if ( ptr ) {
    int32_t index = ptr - s;
    return index;
  }

  return -1;
}

char *
strcat_int( char *s, int n ) {
  // Create a char buffer with the number of digits with an
  // extra character for null terminator.
  int32_t digits = ( int32_t ) ceil( log10( n ) ) + 1;
  char *  buffer = malloc( ( sizeof( char ) * strlen( s ) ) + digits );
  strcpy( buffer, s );
  char num_buf[MAX_INT_DIGITS];
  sprintf( num_buf, "%d", n);
  strcat( buffer, num_buf );
  return buffer;
}