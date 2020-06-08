#include "player.h"

static SDL_Texture* playerTexture;

static void keyInputUpdate(void);
static void mouseInputUpdate(void);

void init_player(void) {

  player = malloc(sizeof(Entity));
  memset(player, 0, sizeof(Entity));

  player->x = SCREEN_WIDTH >> 1;
  player->y = SCREEN_HEIGHT >> 1;
  player->texture = loadTexture("../res/img/player.png");
  SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);

  player->idFlags |= ID_PLAYER_MASK;
  player->life = 1;
  //
  // player->tick = player_update;
  // player->draw = player_draw;
  // player->die = player_die;
}

void player_update(void) {

  if (player->life <= 0) {
    player_die();
    return;
  }
  keyInputUpdate();
  mouseInputUpdate();
}

void player_draw(void) {
  blitTextureScaled(player->texture, player->x - app.camera.x, player->y - app.camera.y, 1, 1, player->angle);
}

void player_die(void) {
  if (!(player->flags & DEATH_MASK)) {
    player->flags |= DEATH_MASK;
  }
}

static void keyInputUpdate(void) {
  player->dx *= 0.95;
  player->dy *= 0.95;

  if (app.keyboard[SDL_SCANCODE_W]) {
    player->dy = -5;
  }

  if (app.keyboard[SDL_SCANCODE_S]) {
    player->dy = 5;
  }

  if (app.keyboard[SDL_SCANCODE_A]) {
    player->dx = -5;
  }

  if (app.keyboard[SDL_SCANCODE_D]) {
    player->dx = 5;
  }

  player->x += player->dx;
  player->y += player->dy;
}

static void mouseInputUpdate(void) {
  player->angle = getAngle(player->x - app.camera.x, player->y - app.camera.y, app.mouse.x, app.mouse.y);
}
