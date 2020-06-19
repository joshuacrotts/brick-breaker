#ifndef BALL_H
#define BALL_H

#include "commons.h"
#include "particle.h"

extern App app;
extern Stage stage;
extern Level* currentLevel;
/*
 *
 */
Entity* add_ball(float, float, uint32_t flags);

/*
 *
 */
void ball_update(Entity*);

/*
 *
 */
void ball_draw(Entity*);

/*
 *
 */
void ball_die(Entity*);

extern void drawRect(SDL_Rect*, uint8_t, uint8_t, uint8_t, uint8_t, bool);
extern void blit(SDL_Texture*, float, float, bool);
extern void blitRotated(SDL_Texture*, float, float, uint16_t);
extern SDL_Texture* loadTexture(char*);

#endif