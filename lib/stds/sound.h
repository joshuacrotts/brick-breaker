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
extern void loadMusic(char*);

/*
 *
 */
extern void playMusic(bool);

/*
 *
 */
extern void playSound(int, int);

#endif
