#ifndef SCORE_ITEM_H
#define SCORE_ITEM_H

#include "../lib/stds/include/draw.h"
#include "../lib/stds/include/text.h"
#include "commons.h"
#include "score_item.h"

extern level_t *currentLevel;
extern stage_t  stage;

extern void add_score_item( f32, f32, uint32_t );

extern void score_item_update( score_item_t * );

extern void score_item_draw( score_item_t * );

#endif