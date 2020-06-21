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
 *
 */
extern void 
load_music(const char*);


/*
 *
 */
extern void 
play_music(bool);


/*
 *
 */
extern void 
play_sound(int16_t, int16_t);

#endif
