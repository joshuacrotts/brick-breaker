#include "../include/sound.h"

static void loadSounds(void);

static Mix_Chunk* sounds[SND_MAX];
static Mix_Music* music;

void initSounds(void) {
  memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);

  music = NULL;

  loadSounds();
}

 void loadMusic(const char* fileName) {
   if (music != NULL) {
     Mix_HaltMusic();
     Mix_FreeMusic(music);
     music = NULL;
   }

   music = Mix_LoadMUS(fileName);
 }

void playMusic(bool loop) {
  Mix_PlayMusic(music, loop ? -1 : 0);
}

void playSound(int16_t id, int16_t channel) {
  Mix_PlayChannel(channel, sounds[id], 0);
}

/*
 *
 */
static void loadSounds(void) {
  sounds[SND_BRICK_SHATTER] = Mix_LoadWAV("res/sfx/explode_1.mp3");
  sounds[SND_BRICK_BREAK] = Mix_LoadWAV("res/sfx/explode_2.mp3");
  sounds[SND_PAUSE] = Mix_LoadWAV("res/sfx/pause.mp3");
  loadMusic("res/sfx/music/metalsong.wav");
  playMusic(true);
}
