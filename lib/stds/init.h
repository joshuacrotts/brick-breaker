#ifndef INIT_H
#define INIT_H

#include "stds.h"

App app;

/*
 *
 */
extern void initGame(const char*, int, int);

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

#endif
