#ifndef MAIN_H
#define MAIN_H

#include "commons.h"

App app;
Stage stage;
Entity* paddle;
extern Level* currentLevel;
extern Background* background;

extern void init_paddle(void);
extern void init_background(void);
extern void background_update(void);
extern void background_draw(void);
extern void background_die(void);
extern void paddle_update(void);
extern void paddle_draw(void);
extern void paddle_die(void);
extern void emitter_update(Emitter*);
extern void emitter_draw(Emitter*);
extern void emitter_die(Emitter*);
extern void particle_update(Entity*);
extern void particle_draw(Entity*);
extern void particle_die(Entity*);
extern void level_update(void);
extern void level_draw(void);
extern void level_die(void);
extern void debris_update(Debris*);
extern void debris_draw(Debris*);
extern void debris_die(Debris*);

extern Entity* add_ball(float, float, uint32_t);
extern Level* add_level();
extern Entity* add_particle(float, float, float, float, float, float, uint16_t, uint16_t, uint16_t, int16_t, int16_t, int16_t, int16_t, float);
extern Animation* add_animation(char*, uint8_t, float);
extern Entity* add_powerup(float, float, uint32_t, int8_t);
extern Emitter* create_emitter(int32_t, int32_t, uint32_t, uint32_t);
extern void spawnBloodParticles(Emitter*, int32_t, int32_t, uint32_t, uint32_t);
extern void spawnColorfulParticles(Emitter*, int32_t, int32_t, uint32_t, uint32_t);

extern void initGame(const char*, int, int);
extern void updateCamera(Entity*);
extern void loop();
extern void drawText(float, float, int, int, int, const char*, ...);
extern void blitColorTextureScaled(SDL_Texture*, float, float, float, float, uint16_t, int16_t, int16_t, int16_t, int16_t);
extern void blitTextureScaled(SDL_Texture*, float, float, float, float, uint16_t);
extern void blit(SDL_Texture*, float, float, bool);
extern void drawRect(SDL_Rect*, uint8_t, uint8_t, uint8_t, uint8_t, bool);
extern void drawRectStroke(int32_t, int32_t, int32_t, int32_t, uint32_t, uint8_t, uint8_t, uint8_t, uint8_t);
extern SDL_Texture* loadTexture(const char*);
extern SDL_Color combineFadeColor(FadeColor*);

#endif
