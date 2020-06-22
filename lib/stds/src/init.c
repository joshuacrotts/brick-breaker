#include "../include/init.h"

static bool debug_mode = false;

static void init_SDL(const char*, uint16_t, uint16_t);
static void init_audio_context(void);
static void cleanup(void);


void 
init_game(const char *window_name, uint16_t window_width, uint16_t window_height) {
  init_SDL(window_name, window_width, window_height);
  init_sounds();
  init_fonts();

  app.original_title = window_name;
  
  // Assigns the callback function to clean up the
  // SDL context when closing the program.
  atexit(cleanup);
}


void 
toggle_debug_mode(bool db) {
  debug_mode = db;
}


/*
 * Initializes the SDL context, renderer, and window.
 * 
 * @param window name, window width, and window height.
 * @return none.
 */
static void 
init_SDL(const char *window_name, uint16_t window_width, uint16_t window_height) {
  int8_t renderer_flags;
  int8_t window_flags;

  renderer_flags = SDL_RENDERER_ACCELERATED;
  window_flags   = 0;

  if (debug_mode) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initialization of SDL started.");
  }

  memset(&app, 0, sizeof(app_t));

  // Initialize SDL and exit if we fail.
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s.\n", SDL_GetError());
    exit(EXIT_ERROR);
  }

  if (debug_mode) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initializing window.");
  }

  // Initialize the SDL window.
  app.window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, window_flags);

  if (!app.window) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not open window. %s.\n", SDL_GetError());
    exit(EXIT_ERROR);
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

  if (debug_mode) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Creating SDL renderer.");
  }

  // Create renderer with the default graphics context.
  app.renderer = SDL_CreateRenderer(app.window, -1, renderer_flags);

  if (!app.renderer) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize renderer: %s.\n", SDL_GetError());
    exit(EXIT_ERROR);
  }

  if (debug_mode) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initialization Completed.");
  }

  //  Initialize SDL to accept both JPG and PNGs.
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

  //  Remove cursor.
  SDL_ShowCursor(true);

  init_audio_context();
}


/*
 * Initializes the SDL audio context, and allocates the necessary
 * memory for the number of channels allowed by Standards.
 * 
 * @param none.
 * @return void.
 */
static void 
init_audio_context(void) {
  if (debug_mode) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initializing audio context and SDL Mixer.");
  }

  if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) == -1) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL Mixer.\n");
    exit(EXIT_ERROR);
  }

  Mix_AllocateChannels(MAX_SND_CHANNELS);
}


/*
 * Cleans up the SDL context and game upon closing the application.
 * 
 * @param none.
 * @return void.
 */
static void 
cleanup(void) {
  if (debug_mode) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Cleaning up.");
  }

	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);

  // Free the memory of the linked lists defined by
  // the app struct.
  parallax_background_t *pbg;
  texture_t *t;
  button_t *b;
  trail_t *tr;

  if (debug_mode) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Freeing parallax backgrounds.");
  }

  while (app.parallax_head.next) {
    pbg = app.parallax_head.next;
    app.parallax_head.next = pbg->next;
    free(pbg);
  }

  if (debug_mode) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Freeing textures.");
  }  

  while (app.texture_head.next) {
    t = app.texture_head.next;
    app.texture_head.next = t->next;
    free(t);
  }

  if (debug_mode) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Freeing trails.");
  }  

  while (app.trail_head.next) {
    tr = app.trail_head.next;
    app.trail_head.next = tr->next;
    free(tr);
  }      

  if (debug_mode) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Freeing buttons.");
  }

  while (app.button_head.next) {
    b = app.button_head.next;
    app.button_head.next = b->next;
    free(b);
  }

  free(&app);
  free_fonts();
	SDL_Quit();

  if (debug_mode) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Program quit.");
  }
}
