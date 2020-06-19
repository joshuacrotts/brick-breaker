#ifndef INIT_H
#define INIT_H

#include "stds.h"

App app;

/*
 *
 */
extern void initGame(const char*, uint16_t, uint16_t);

/*
 *
 */
extern void initSounds(void);

 /*
  *
  */
extern void initFonts(void);

/*
 *
 */
extern void toggleDebugMode(bool);

/*
 *
 */
extern void freeFonts(void);

#endif
