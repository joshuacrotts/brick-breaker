#include "player.h"

static SDL_Texture* playerTexture;

static void keyInputUpdate(void);
static void mouseInputUpdate(void);

static void followCursor(int32_t x, int32_t y);

void init_player(void) {
  player = malloc(sizeof(Entity));
  memset(player, 0, sizeof(Entity));
  player->x = SCREEN_WIDTH >> 1;
  player->y = SCREEN_HEIGHT >> 1;
  player->animation = add_animation("../res/img/player/Walk_gun_00", 6, 0.10);

  player->idFlags |= ID_PLAYER_MASK;
  player->animation->flags |= STD_ANIMATION_MASK;
  player->life = 1;

  if (player->animation->flags & SPRITE_SHEET_MASK) {
    player->w = player->animation->spriteSheetW / player->animation->numberOfFrames;
    player->h = player->animation->spriteSheetH;
  } else if (player->animation->flags & STD_ANIMATION_MASK){
    SDL_QueryTexture(player->animation->currentTexture, NULL, NULL, &player->w, &player->h);
  }
}

void player_update(void) {
  if (player->flags & MOVE_MASK) {
    animation_update(player->animation);
  }

  if (player->life <= 0) {
    player_die();
    return;
  }

  keyInputUpdate();
  mouseInputUpdate();
}

void player_draw(void) {
  if (player->flags & MOVE_MASK) {
    animation_draw(player);
  } else {
    player->flags &= ~MOVE_MASK;
  //  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "ass");
    blitRotated(player->animation->defaultTexture, player->x - app.camera.x, player->y - app.camera.y, player->angle);
  }
  //blitTextureScaled(player->texture, player->x - app.camera.x, player->y - app.camera.y, 1, 1, player->angle);
}

void player_die(void) {
  if (!(player->flags & DEATH_MASK)) {
    player->flags |= DEATH_MASK;
    animation_die(player->animation);
  }
}

static void keyInputUpdate(void) {
  // player->dx *= 0.95;
  // player->dy *= 0.95;
  //
  if (app.keyboard[SDL_SCANCODE_W] || app.keyboard[SDL_SCANCODE_S] || app.keyboard[SDL_SCANCODE_A] || app.keyboard[SDL_SCANCODE_D]) {
    player->flags |= MOVE_MASK;
  } else {
    player->flags &= ~MOVE_MASK;
  }

  followCursor(app.mouse.x + app.camera.x, app.mouse.y + app.camera.y);

  if (player->flags & MOVE_MASK) {
    player->x += player->dx;
    player->y += player->dy;
  }
}

static void followCursor(int32_t x, int32_t y) {

  int32_t entityApproachVel = 8;
  float approachVel = -6.0f;

  float diffX = player->x - x - entityApproachVel;
  float diffY = player->y - y - entityApproachVel;

  float distance = sqrt(((player->x - x) * (player->x - x)) + ((player->y - y) * (player->y - y)));

  player->dx = ((approachVel / distance) * diffX);
  player->dy = ((approachVel / distance) * diffY);
}

static void mouseInputUpdate(void) {
  player->angle = getAngle(player->x - app.camera.x, player->y - app.camera.y, app.mouse.x, app.mouse.y);
}
