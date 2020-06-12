#include "animation.h"

static char inputBuffer[MAX_BUFFER_SIZE];

Animation* add_spritesheet(char* directory, uint8_t numberOfFrames, float frameDelay, uint16_t x, uint16_t y) {
  Animation* a;

  a = malloc(sizeof(Animation));
  memset(a, 0, sizeof(Animation));

  a->numberOfFrames = numberOfFrames;
  a->currentTexture = loadTexture(directory);
  a->frameDelay = frameDelay;
  a->frameTimer = frameDelay * FPS;
  a->startX = x;
  a->startY = y;
  SDL_QueryTexture(a->currentTexture, NULL, NULL, &a->spriteSheetW, &a->spriteSheetH);
  a->currentFrameID = 0;
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

  a->defaultTexture = a->frames[0];
}

void animation_update(Entity* e) {
  Animation* a = e->animation;

  a->frameTimer -= 1;

  if (a->frameTimer < 0) {
    // Resets the frame countdown.
    a->frameTimer = a->frameDelay * FPS;
    a->currentFrameID += 1;

    // If we have a spritesheet, we advance x coordinate
    // of the sprite. Otherwise, we advance the pointer
    // referencing which sprite to render in the
    if (a->idFlags & SPRITE_SHEET_MASK) {
      a->x += a->spriteSheetW / a->numberOfFrames;
    } else {
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
  if (e != NULL) {
    Animation* a = e->animation;
    if (a->flags & STD_ANIMATION_MASK) {
      blitRotated(a->frames[a->currentFrameID], e->x - app.camera.x, e->y - app.camera.y, e->angle);
    } else if (a->flags & SPRITE_SHEET_MASK) {
      SDL_Rect currRect;
      currRect.x = a->x;
      currRect.y = a->y;
      SDL_QueryTexture(a->currentTexture, NULL, NULL, &currRect.w, &currRect.h);
      blitRect(a->currentTexture, &currRect, a->x - app.camera.x, a->y - app.camera.y);
    }
  }
}

void animation_die(Entity* e) {
  Animation* a = e->animation;

  for (int i = 0; i < a->numberOfFrames; i++) {
    SDL_DestroyTexture(a->frames[i]);
  }

  SDL_DestroyTexture(a->currentTexture);
  free(a->frames);
  free(a);
}