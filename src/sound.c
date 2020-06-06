#include "sound.h"

static void loadSounds(void);

static Mix_Chunk* sounds[SND_MAX];
static Mix_Music* music;

/*
 *
 */
void initSounds(void) {
  memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);

  music = NULL;

  loadSounds();
}

/*
 *
 */
 void loadMusic(char* fileName) {
   if (music != NULL) {
     Mix_HaltMusic();
     Mix_FreeMusic(music);
     music = NULL;
   }

   music = Mix_LoadMUS(fileName);
 }

 /*
  *
  */
void playMusic(int loop) {
  Mix_PlayMusic(music, loop ? -1 : 0);
}

/*
 *
 */
void playSound(int id, int channel) {
  //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Playing sound started.\n");
  Mix_PlayChannel(channel, sounds[id], 0);
}

/*
 *
 */
static void loadSounds(void) {
  
}
