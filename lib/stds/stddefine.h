#ifndef DEFS_H
#define DEFS_H

#define LEVEL_WIDTH             9999
#define LEVEL_HEIGHT            9999
#define SCREEN_WIDTH            1280
#define SCREEN_HEIGHT           720
#define EXIT_ERROR              1
#define EXIT_SUCCESS            0
#define MAX_KEYBOARD_KEYS       350
#define FPS                     60
#define MAX_SND_CHANNELS        8
#define MAX_LINE_LENGTH         1024
#define MAX_KEYBOARD_KEYS       350
#define MAX_MOUSE_BUTTONS       350
#define MAX_BUFFER_SIZE         128
#define MAX_FILE_NAME_LEN       48
#define PI                      3.14159265358979323846

#define SPRITE_SHEET_MASK       2
#define STD_ANIMATION_MASK      1


enum {
  RUNNING,
  PAUSED
};

enum {
  CH_ANY = -1,
  CH_PLAYER,
  CH_ALIEN_FIRE,
  CH_POINTS
};

enum {
  SND_PLAYER_FIRE,
  SND_ALIEN_FIRE,
  SND_PLAYER_DIE,
  SND_ALIEN_DIE,
  SND_POINTS,
  SND_MAX
};

#endif
