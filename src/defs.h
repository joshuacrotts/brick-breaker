#define SCREEN_WIDTH            1280
#define SCREEN_HEIGHT           720
#define EXIT_ERROR              1
#define EXIT_SUCCESS            0
#define MAX_KEYBOARD_KEYS       350
#define FRAMES_PER_SECOND       60
#define MAX_SND_CHANNELS        8


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
