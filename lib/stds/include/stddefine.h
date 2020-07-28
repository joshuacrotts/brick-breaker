#ifndef DEFS_H
#define DEFS_H

#define EXIT_ERROR          1
#define EXIT_SUCCESS        0
#define MAX_KEYBOARD_KEYS   350
#define FPS                 60
#define FPS_TIME            ( 1000 / FPS )
#define MAX_SND_CHANNELS    16
#define MAX_LINE_LENGTH     1024
#define SMALL_TEXT_BUFFER   64
#define MAX_KEYBOARD_KEYS   350
#define MAX_MOUSE_BUTTONS   350
#define MAX_BUFFER_SIZE     128
#define MAX_FILE_NAME_LEN   48
#define TEXTURE_BUFFER_SIZE 4
#define WINDOW_UPDATE_TIMER 1000
#define PI                  3.14159265358979323846

#define STDS_SPRITE_SHEET_MASK              2
#define STDS_ANIMATION_MASK                 1
#define STDS_DEATH_MASK                     0x10000000
#define STDS_TRAIL_TEXTURE_MASK             0x00100000
#define STDS_TRAIL_TRANSPARENT_TEXTURE_MASK 0x00200000 /* Use this if your texture has a background that should be transparent. */
#define STDS_TRAIL_CIRCLE_MASK              0x00400000
#define STDS_TRAIL_SQUARE_MASK              0x00800000
#define STDS_ANIMATION_ACTIVE_MASK          0x01000000

enum GameState { RUNNING, PREGAME, INIT, TRANSITION, PAUSED };

enum CollisionSide { SIDE_TOP, SIDE_LEFT, SIDE_RIGHT, SIDE_BOTTOM, SIDE_NONE = -1 };

enum SoundChannel { CH_ANY = -1, CH_BRICK };

enum SFX { SND_COIN, SND_EXTRA_LIFE, SND_PAUSE, SND_BRICK_BREAK, SND_BRICK_SHATTER, SND_MAX };

#endif // DEFS_H
