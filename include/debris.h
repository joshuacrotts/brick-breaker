#ifndef DEBRIS_H
#define DEBRIS_H

#include "../lib/stds/include/draw.h"
#include "commons.h"

extern stage_t stage;

/*
 *
 */
extern void add_debris( entity_t *, uint32_t );

/*
 *
 */
extern void debris_update( debris_t * );

/*
 *
 */
extern void debris_draw( debris_t * );

/*
 *
 */
extern void debris_die( debris_t * );

#endif