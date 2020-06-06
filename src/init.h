#ifndef INIT_H
#define INIT_H

#include "stds.h"

bool debugMode;
extern App app;

/*
 *
 */
extern void initGame(const char*, int, int);

/*
 * Initializes the SDL context, renderer, and
 * window.
 */
extern void initSDL(const char*, int, int);

/*
 *
 */
extern void initAudioContext(void);

/*
 *
 */
extern void initFonts(void);

/*
 *
 */
extern void initSounds(void);

/*
 *
 */
extern void cleanup(void);

/*
 *
 */
extern void toggleDebugMode(bool);

#endif
