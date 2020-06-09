#ifndef EMITTER_H
#define EMITTER_H

#include "commons.h"

extern Entity* e;
extern App app;
extern Stage stage;

extern Emitter* create_emitter(int32_t, int32_t, uint32_t, uint32_t);
extern void emitter_update(Emitter*);
extern void emitter_draw(Emitter*);
extern void emitter_die(Emitter*);
extern void particle_tick(Entity*);
extern void particle_draw(Entity*);
extern void particle_die(Entity*);
extern Entity* add_particle(float, float, float, float, float, float, uint16_t, uint16_t, uint16_t, uint8_t, uint8_t, uint8_t, uint8_t, float, uint32_t);
extern Entity* add_animated_particle(float, float, float, float, float, float, uint16_t, uint32_t, Animation*);
extern Animation* add_animation(char*, uint8_t, float);
extern void spawnBloodParticles(Emitter*, int32_t, int32_t, uint32_t, uint32_t);
extern void spawnColorfulParticles(Emitter*, int32_t, int32_t, uint32_t, uint32_t);
#endif
