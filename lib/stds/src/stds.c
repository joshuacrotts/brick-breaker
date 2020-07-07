#include "../include/stds.h"

static char number_buffer[MAX_INT_DIGITS];
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

void
clamp( int32_t *value, int32_t min, int32_t max ) {
  if ( *value < min ) {
    *value = min;
  } else if ( *value > max ) {
    *value = max;
  }
}

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

float
get_angle( int32_t x1, int32_t y1, int32_t x2, int32_t y2 ) {
  float angle = ( float ) ( -90.0f + atan2( y1 - y2, x1 - x2 ) * ( 180.0f / PI ) );
  return angle >= 0 ? angle : 360.0f + angle;
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

bool
is_mouse_over_rect( float x, float y, SDL_Rect rect ) {
  return ( x > rect.x && x < rect.x + rect.w ) && ( y > rect.y && y < rect.y + rect.h );
}

float
to_radians( float degrees ) {
  return ( float ) ( degrees * ( PI / 180.0f ) );
}

float
to_degrees( float radians ) {
  return ( float ) ( radians * ( 180.0f / PI ) );
}

char *
str_substring( const char *str, int first, int last ) {
  uint32_t s_len = strlen( str );
  assert( s_len > 0 && first < last && first >= 0 && last <= s_len );

  char *s = malloc( sizeof( char ) * ( last - first ) );
  memcpy( s, str + first, last - first );
  return s;
}

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

char *
strcat_int( const char *s, int32_t n ) {
  memset(text_buffer, '\0', sizeof(text_buffer));
  strncat(text_buffer, s, strlen(s));
  int32_t digits = sprintf(number_buffer, "%d", n);
  strncat(text_buffer, number_buffer, digits);
  return text_buffer;
}