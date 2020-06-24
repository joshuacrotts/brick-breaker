#include "../include/game.h"

static uint16_t current_fps;

static void     cap_framerate( long *, float * );
static uint32_t update_window_title( uint32_t, void * );

void
init_app_structures() {
  app.parallax_tail = &app.parallax_head;
  app.texture_tail  = &app.texture_head;
  app.button_tail   = &app.button_head;
  app.trail_tail    = &app.trail_head;
  app.font_tail     = &app.font_head;
}

void
loop() {
  long  timer;
  long  then;
  float remainder;

  then      = SDL_GetTicks();
  remainder = 0;

  SDL_AddTimer( WINDOW_UPDATE_TIMER, update_window_title, &current_fps );

  // Main game loop.
  while ( true ) {
    prepare_scene();
    process_input();
    app.delegate.tick();
    app.delegate.draw();
    present_scene();
    cap_framerate( &then, &remainder );
  }
}

/*
 * Halts the framerate to approximately sixty frames
 * per second when possible.
 *
 * @param pointers to the times from the previous iteration,
 *        and remainder.
 *
 * @return void.
 */
static void
cap_framerate( long *then, float *remainder ) {
  long wait, frame_time;

  wait = ( int32_t )( 16 + *remainder );
  *remainder -= ( int ) *remainder;
  frame_time = SDL_GetTicks() - *then;
  wait -= frame_time;
  if ( wait < 1 ) {
    wait = 1;
  }

  SDL_Delay( wait );

  current_fps = 1000 / wait;
  *remainder += ( 0.667f );
  *then = SDL_GetTicks();
}

/*
 * Callback function to the SDL_AddTimer function that changes
 * the SDL_Window title to a set value with the FPS concatenated
 * onto the end.
 *
 * @param timer interval, and arguments for concatenating. This
 *        should be the frames per second (integer).
 *
 * @return interval time for callback function.
 */
static uint32_t
update_window_title( uint32_t interval, void *args ) {
  uint16_t fps = *( uint16_t * ) args;
  // Create text window buffer.
  char window_buffer[SMALL_TEXT_BUFFER];

  // Buffer for FPS string representation.
  char num_buffer[3];

  // Convert fps to string - store in num_buffer.
  itoa( fps, num_buffer, 10 );

  // Copy the title to the buffer.
  strcpy( window_buffer, app.original_title );

  // Create temp variable for title.
  char *title = " | FPS: ";

  // Move temp var to buffer. Receive ptr.
  strcat( window_buffer, title );

  // Concatenate number to title variable.
  strcat( window_buffer, num_buffer );

  SDL_SetWindowTitle( app.window, window_buffer );

  memset( num_buffer, '\0', sizeof( num_buffer ) );
  memset( window_buffer, '\0', sizeof( window_buffer ) );

  return interval;
}