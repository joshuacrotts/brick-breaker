#include "../include/sound.h"

static void load_sounds( void );

static Mix_Chunk *sounds[SND_MAX];
static Mix_Music *music;

void
init_sounds( void ) {
  memset( sounds, 0, sizeof( Mix_Chunk * ) * SND_MAX );

  music = NULL;

  load_sounds();
}

void
load_music( const char *fileName ) {
  if ( music != NULL ) {
    Mix_HaltMusic();
    Mix_FreeMusic( music );
    music = NULL;
  }

  music = Mix_LoadMUS( fileName );
}

void
play_music( bool loop ) {
  Mix_PlayMusic( music, loop ? -1 : 0 );
}

void
play_sound( int16_t id, int16_t channel ) {
  Mix_PlayChannel( channel, sounds[id], 0 );
}

static void
load_sounds( void ) {}
