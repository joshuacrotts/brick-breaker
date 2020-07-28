#ifndef GAME_H
#define GAME_H

#include "stds.h"

extern struct app_t app;

extern void Stds_PrepareScene( void );

extern void Stds_ProcessInput( void );

extern void Stds_PresentScene( void );

extern void Stds_GameLoop( void );

extern void Stds_InitAppStructures( void );

extern void init_window_fps( void  ); 

#endif // GAME_H
