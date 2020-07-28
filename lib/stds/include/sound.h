#ifndef SOUND_H
#define SOUND_H

#include "stds.h"

extern void Stds_InitSounds( void );

extern void Stds_LoadMusic( const char *music_path );

extern void Stds_PlayMusic( const bool is_playing );

extern void Stds_PlaySounds( const int16_t sound_effect_id, const int16_t channel );

#endif // SOUND_H
