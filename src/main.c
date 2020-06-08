#include "main.h"

static void initScene(void);
static void draw(void);
static void tick(void);

static void updateParticleHandler(void);
static void drawParticleHandler(void);

static void spawnBloodParticles(int32_t, int32_t, uint32_t);

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

  memset(&stage, 0, sizeof(Stage));
  init_player();

  backgroundTexture = loadTexture("../res/img/background1.jpg");

  stage.particleTail = &stage.particleHead;
}

static void tick(void) {
  updateCamera(player);

  if (app.mouse.button[SDL_BUTTON_LEFT]) {
    //spawnBloodParticles(app.mouse.x - app.camera.x, app.mouse.y - app.camera.y, 128);
    spawnBloodParticles(player->x, player->y, 128);
    app.mouse.button[SDL_BUTTON_LEFT] = 0;
  }

  updateParticleHandler();
  player_update();
}

static void draw(void) {
  drawParticleHandler();
  player_draw();
}

static void spawnBloodParticles(int32_t x, int32_t y, uint32_t n) {
  for (int i = 0; i < n; i++) {
    bool scatterParticle = randomInt(0, 1);
    float dx = randomFloat(-20, 20);
    float dy = randomFloat(-20, 20);
    float decX;
    float decY;
    float deltaAlpha;
    if (!scatterParticle) {
      decX = randomFloat(0.50, 0.70);
      decY = randomFloat(0.50, 0.70);
    } else {
      decX = randomFloat(0.70, 0.95);
      decY = randomFloat(0.70, 0.95);
      deltaAlpha = randomFloat(1, 3);
    }
    uint16_t w = randomInt(1, 10);
    uint16_t h = w;
    uint8_t r = randomInt(20, 0xff);
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 0xff;
    uint16_t angle = 0;
    Entity* e;
    e = add_particle(x, y, dx, dy, decX, decY, w, h, angle, r, g, b, a, deltaAlpha);
    stage.particleTail->next = e;
    stage.particleTail = e;
  }
}

static void updateParticleHandler() {
  Entity* e;
  Entity* prev;

  prev = &stage.particleHead;
  for (e = stage.particleHead.next; e != NULL; e = e->next) {
    e->tick(e);

    if (e->flags & DEATH_MASK) {
      if (e == stage.particleTail) {
        stage.particleTail = prev;
      }

      prev->next = e->next;
      free(e);
      e = prev;
    }
    prev = e;
  }
}

static void drawParticleHandler() {
  Entity* e;

  for (e = stage.particleHead.next; e != NULL; e = e->next) {
    e->draw(e);
  }
}
