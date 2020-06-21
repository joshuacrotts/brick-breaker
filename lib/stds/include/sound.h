#ifndef SOUND_H
#define SOUND_H

#include "stds.h"

/*
 * Initializes the sound context for SDL.
 * 
 * @return void.
 */
extern void 
init_sounds(void);


/*
 * Loads a music file from the respective path.
 * 
 * @param const char* path of music file.
 * 
 * @return void.
 */
extern void 
load_music(const char*);


/*
 * Toggles the playback of the currently-loaded song.
 * 
 * @param bool true to play, false otherwise.
 * 
 * @return void.
 */
extern void 
play_music(bool);


/*
 * Plays a sound with the respective channel and ID of the SFX.
 * For instance, 
 * 
 * Ex: play_sound(SND_BRICK_BREAKER, CH_ANY).
 * 
 * @param int16_t sound effect ID from enum.
 * @param int16_t channel from enum. 
 */
extern void 
play_sound(int16_t, int16_t);

#endif
