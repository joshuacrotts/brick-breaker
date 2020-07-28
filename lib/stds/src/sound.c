//=============================================================================================//
// FILENAME :       sound.c
//
// DESCRIPTION :
//        This file defines the SDL sound mixer initialization, and how to play/pause both sound
//        effects and music.
//
// NOTES :
//        Permission is hereby granted, free of charge, to any person obtaining a copy
//        of this software and associated documentation files (the "Software"), to deal
//        in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
//        furnished to do so, subject to the following conditions:
//
//        The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
//        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//        SOFTWARE.
//
// AUTHOR :   Joshua Crotts        START DATE :    18 Jun 2020
//
//=============================================================================================//

#include "../include/sound.h"

static void Stds_LoadSounds( void );

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
Stds_InitSounds( void ) {
  memset( sounds, 0, sizeof( Mix_Chunk * ) * SND_MAX );

  music = NULL;

  Stds_LoadSounds();
}

/**
 * Loads a music file from the respective path.
 *
 * @param const char* path of music file.
 *
 * @return void.
 */
void
Stds_LoadMusic( const char *fileName ) {
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
Stds_PlayMusic( const bool loop ) {
  Mix_PlayMusic( music, loop ? -1 : 0 );
}

/**
 * Plays a sound with the respective channel and ID of the SFX.
 * For instance,
 *
 * Ex: Stds_PlaySounds(SND_BRICK_BREAKER, CH_ANY).
 *
 * @param int16_t sound effect ID from enum.
 * @param int16_t channel from enum.
 *
 * @return void.
 */
void
Stds_PlaySounds( const int16_t id, const int16_t channel ) {
  Mix_PlayChannel( channel, sounds[id], 0 );
}

/**
 * Loads the sound effects for your game.
 *
 * @param void.
 *
 * @return void.
 */
static void
Stds_LoadSounds( void ) {
  sounds[SND_BRICK_SHATTER] = Mix_LoadWAV( "res/sfx/explode_1.ogg" );
  sounds[SND_BRICK_BREAK]   = Mix_LoadWAV( "res/sfx/explode_2.ogg" );
  sounds[SND_COIN]          = Mix_LoadWAV( "res/sfx/coin0.ogg" );
  sounds[SND_EXTRA_LIFE]    = Mix_LoadWAV( "res/sfx/extra-life.ogg" );
  sounds[SND_PAUSE]         = Mix_LoadWAV( "res/sfx/pause.ogg" );
}
