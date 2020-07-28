#ifndef STDS_H
#define STDS_H

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
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

#include "..\lib\structures\include\stds_vector.h"

#define MAX_INT_DIGITS 11
#define DEBUG          1

extern void Stds_SetRandomSeed( void );

extern int32_t Stds_RandomInt( const int32_t min, const int32_t max );

extern int32_t Stds_RandomIntBounded( const int32_t min, const int32_t min_upper_bound,
                                      const int32_t max_lower_bound, const int32_t max );

extern float Stds_RandomFloat( const float min, const float max );

extern float Stds_RandomFloatBounded( const float min, const float min_upper_bound,
                                      const float max_lower_bound, const float max );

extern void Stds_ClampInt( int32_t *n, const int32_t min, const int32_t max );

extern void Stds_CalcSlope( const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2,
                            float *x_slope, float *y_slope );

extern float Stds_GetAngle( const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2 );

extern int32_t Stds_GetDistance( const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2 );

extern void Stds_Print( const char *s, ... );

extern float Stds_ToRadians( const float degree_angle );

extern float Stds_ToDegrees( const float radian_angle );

extern bool Stds_IsMouseOverRect( const float x, const float y, const SDL_Rect *rect );

extern SDL_Color Stds_ConvertARGBToColor( const uint32_t c );

extern uint32_t Stds_ConvertColorToARGB( const SDL_Color *c );

extern char *Stds_Substring( const char *str, const int32_t first, const int32_t last );

extern int32_t Stds_IndexOf( const char *s, const char *search_str );

extern char *Stds_StrCatIntPtr( const char *s, const int32_t n );

extern char *Stds_StrCatIntArray( const char s[], const int32_t n );

#endif // STDS_H