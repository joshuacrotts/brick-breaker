#ifndef GAME_H
#define GAME_H

#include "stds.h"

extern app_t app;

extern void prepare_scene( void );
extern void process_input( void );
extern void present_scene( void );
extern void loop( void );
extern void init_app_structures( void );
extern void init_window_fps( void  ); 

#endif // GAME_H
