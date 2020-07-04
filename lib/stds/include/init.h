#ifndef INIT_H
#define INIT_H

#include "stds.h"

app_t app;

/**
 * Calls the remainder of the initialization functions, and
 * sets up the game loop structure.
 *
 * @param const char *window title.
 * @param uint16_t window width.
 * @param uint16_t window height.
 *
 * @return void.
 */
extern void init_game( const char *, uint16_t, uint16_t );

/**
 * Initializes the SDL sound context.
 *
 * @return void.
 */
extern void init_sounds( void );

/**
 * Initializes the SDL ttf_font context.
 *
 * @return void.
 */
extern void init_fonts( void );

/**
 * Toggles debug mode either on or off. When on, debug messages
 * are printed to the console.
 *
 * @param bool true for debug mode on, false otherwise.
 *
 * @return void.
 */
extern void toggle_debug_mode( bool is_debugging );

/**
 * Releases all fonts and the font context from memory.
 */
extern void free_fonts( void );

#endif // INIT_H
