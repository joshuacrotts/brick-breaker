#ifndef SOUND_H
#define SOUND_H

#include "stds.h"

/*
 *
 */
extern void initSound(void);

/*
 *
 */
extern void loadMusic(const char*);

/*
 *
 */
extern void playMusic(bool);

/*
 *
 */
extern void playSound(int16_t, int16_t);

#endif
