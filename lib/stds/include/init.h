#ifndef INIT_H
#define INIT_H

#include "sound.h"
#include "stds.h"
#include "text.h"

app_t app;

extern void init_game( const char *title, uint32_t w, uint32_t h, uint32_t lw, uint32_t lh );

extern void toggle_debug_mode( bool is_debugging );

#endif // INIT_H
