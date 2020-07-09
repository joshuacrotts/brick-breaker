#include "../include/sound.h"

static void load_sounds( void );

static Mix_Chunk *sounds[SND_MAX];
static Mix_Music *music;

/**
 * Initializes the sound context for SDL.
 *
 * @param void.
 * 
 * @return void.
 */
void
init_sounds( void ) {
  memset( sounds, 0, sizeof( Mix_Chunk * ) * SND_MAX );

  music = NULL;

  load_sounds();
}

/**
 * Loads a music file from the respective path.
 *
 * @param const char* path of music file.
 *
 * @return void.
 */
void
load_music( const char *fileName ) {
  if ( music != NULL ) {
    Mix_HaltMusic();
    Mix_FreeMusic( music );
    music = NULL;
  }

  music = Mix_LoadMUS( fileName );
}

/**
 * Toggles the playback of the currently-loaded song.
 *
 * @param bool true to play, false otherwise.
 *
 * @return void.
 */
void
play_music( bool loop ) {
  Mix_PlayMusic( music, loop ? -1 : 0 );
}

/**
 * Plays a sound with the respective channel and ID of the SFX.
 * For instance,
 *
 * Ex: play_sound(SND_BRICK_BREAKER, CH_ANY).
 *
 * @param int16_t sound effect ID from enum.
 * @param int16_t channel from enum.
 * 
 * @return void.
 */
void
play_sound( int16_t id, int16_t channel ) {
  Mix_PlayChannel( channel, sounds[id], 0 );
}

/**
 * 
 * 
 * @param void.
 * 
 * @return void.
 */
static void
load_sounds( void ) {
  sounds[SND_BRICK_SHATTER] = Mix_LoadWAV( "res/sfx/explode_1.ogg" );
  sounds[SND_BRICK_BREAK]   = Mix_LoadWAV( "res/sfx/explode_2.ogg" );
  sounds[SND_COIN]          = Mix_LoadWAV( "res/sfx/coin0.ogg" );
  sounds[SND_EXTRA_LIFE]    = Mix_LoadWAV( "res/sfx/extra-life.ogg" );
  sounds[SND_PAUSE]         = Mix_LoadWAV( "res/sfx/pause.ogg" );
}
