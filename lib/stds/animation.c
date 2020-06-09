#include "animation.h"

static char inputBuffer[MAX_BUFFER_SIZE];

Animation* add_spritesheet(char* directory, uint8_t numberOfFrames, float frameDelay, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
  Animation* a;

  a = malloc(sizeof(Animation));
  memset(a, 0, sizeof(Animation));

  a->numberOfFrames = numberOfFrames;
  a->frameDelay = frameDelay;
  a->frameTimer = frameDelay * FPS;
  a->startX = x;
  a->startY = y;
  a->spriteSheetW = w;
  a->spriteSheetH = h;
  a->currentFrameID = 0;
  a->currentTexture = NULL;
  a->idFlags |= SPRITE_SHEET_MASK;
}

Animation* add_animation(char* directory, uint8_t numberOfFrames, float frameDelay) {
  Animation* a;

  a = malloc(sizeof(Animation));
  memset(a, 0, sizeof(Animation));

  a->frames = malloc(sizeof(SDL_Texture*) * numberOfFrames);
  a->numberOfFrames = numberOfFrames;
  a->frameDelay = frameDelay;
  a->frameTimer = frameDelay * FPS;
  a->currentFrameID = 0;
  a->currentTexture = a->frames[a->currentFrameID];
  a->idFlags |= STD_ANIMATION_MASK;

  char numberBuffer[3];
  char* fileExtsn = ".png";

  for (int i = 0; i < a->numberOfFrames; i++) {
    itoa(i, numberBuffer, 10);
    strcpy(inputBuffer, directory);
    char* fileName = strcat(inputBuffer, numberBuffer);
    char* fileNameExt = strcat(inputBuffer, fileExtsn);
    a->frames[i] = loadTexture(fileNameExt);
    memset(inputBuffer, '\0', sizeof(inputBuffer));
  }

  a->tick = animation_update;
  a->draw = animation_draw;
}

void animation_update(Animation* a) {
  a->frameTimer -= 1;

  if (a->frameTimer < 0) {
    // Resets the frame countdown.
    a->frameTimer = a->frameDelay * FPS;

    if (a->idFlags & SPRITE_SHEET_MASK) {
      a->x += a->spriteSheetW;
    } else {
      a->currentFrameID += 1;
      a->currentTexture = a->frames[a->currentFrameID];
    }

    // If we reach the end of the animation sequence,
    // return to the start.
    if (a->currentFrameID >= a->numberOfFrames) {
      a->currentFrameID = 0;
      if (a->idFlags & SPRITE_SHEET_MASK) {
        a->x = 0;
      } else {
        a->currentFrameID = 0;
      }
    }
  }
}

void animation_draw(Entity* e) {
  if (e != NULL && e->animation != NULL) {
    blit(e->animation->frames[e->animation->currentFrameID],
         e->x - app.camera.x, e->y - app.camera.y, false);
  }
}

void animation_die(Animation* a) {
  for (int i = 0; i < a->numberOfFrames; i++) {
    SDL_DestroyTexture(a->frames[i]);
  }

  SDL_DestroyTexture(a->currentTexture);
  free(a->frames);
  free(a);
}
