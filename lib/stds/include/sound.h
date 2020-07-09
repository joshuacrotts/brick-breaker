#ifndef SOUND_H
#define SOUND_H

#include "stds.h"

extern void init_sounds( void );

extern void load_music( const char *music_path );

extern void play_music( bool is_playing );

extern void play_sound( int16_t sound_effect_id, int16_t channel );

#endif // SOUND_H
