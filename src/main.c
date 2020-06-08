#include "main.h"

static void initScene(void);
static void draw(void);
static void tick(void);

static Entity* mainEntity;

// Barebones game. This is the minimum amount of code
// necessary to run a window.
int main(int argc, char* argv[]) {
  initGame("Standards C Library", SCREEN_WIDTH, SCREEN_HEIGHT);
  initScene();
  loop();

  return 0;
}

/*
 * Initializes the delegation structure to use the
 * tick and draw methods for rendering and updating
 * the game. These methods must be defined because the
 * delegation structure uses them in the loop function.
 *
 * Sprites and structs are also initalized here.
 */
static void initScene(void) {
  app.delegate.tick = tick;
  app.delegate.draw = draw;

  mainEntity = malloc(sizeof(Entity));
  memset(mainEntity, 0, sizeof(Entity));

  mainEntity->x = 0;
  mainEntity->y = 0;
  mainEntity->dx = 0;
  mainEntity->dy = 0;
  mainEntity->scaleX = 2;
  mainEntity->scaleY = 2;
  mainEntity->texture = loadTexture("../res/img/player.png");
  mainEntity->angle = 0;
  SDL_QueryTexture(mainEntity->texture, NULL, NULL, &mainEntity->w, &mainEntity->h);
}

static void tick(void) {
  mainEntity->dx *= 0.95;
  mainEntity->dy *= 0.95;

  SDL_QueryTexture(mainEntity->texture, NULL, NULL, &mainEntity->w, &mainEntity->h);

  //  Keyboard input.
  if (app.keyboard[SDL_SCANCODE_W]) {
    mainEntity->dy = -5;
  }

  if (app.keyboard[SDL_SCANCODE_S]) {
    mainEntity->dy = 5;
  }

  if (app.keyboard[SDL_SCANCODE_A]) {
    mainEntity->dx = -5;
  }

  if (app.keyboard[SDL_SCANCODE_D]) {
    mainEntity->dx = 5;
  }

  // Collision detection.
  if (mainEntity->x < 0) {
    mainEntity->x = 0;
  }

  if (mainEntity->x + (mainEntity->w * mainEntity->scaleX) > SCREEN_WIDTH) {
    mainEntity->x = SCREEN_WIDTH - (mainEntity->w * mainEntity->scaleX);
  }

  if (mainEntity->y < 0) {
    mainEntity->y = 0;
  }

  if (mainEntity->y + (mainEntity->h * mainEntity->scaleY) > SCREEN_HEIGHT) {
    mainEntity->y = SCREEN_HEIGHT - (mainEntity->h * mainEntity->scaleY);
  }

  mainEntity->x += mainEntity->dx;
  mainEntity->y += mainEntity->dy;

  mainEntity->angle = getAngle(mainEntity->x, mainEntity->y, app.mouse.x, app.mouse.y);
}

static void draw(void) {
  blitTextureScaled(mainEntity->texture, mainEntity->x, mainEntity->y, mainEntity->scaleX, mainEntity->scaleY, mainEntity->angle);
}
