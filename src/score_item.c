#include "../include/score_item.h"

#define BRICK_SCORE 100

void
add_score_item( f32 x, f32 y, uint32_t score ) {
  score_item_t *s;
  const int8_t  MAX_DIGITS = 5;

  s = malloc( sizeof( score_item_t ) );
  memset( s, 0, sizeof( score_item_t ) );

  s->x    = x;
  s->y    = y;
  s->life = 100;

  s->score = score == 0 ? BRICK_SCORE : score;

  if ( currentLevel->last_break_timer && score == 0 ) {
    s->score *= currentLevel->last_break_timer;
  }

  stage.score += s->score;
  char number_buffer[MAX_DIGITS];
  memset( number_buffer, '\0', sizeof( number_buffer ) );
  sprintf( number_buffer, "%d", s->score );
  strcat( s->text, number_buffer );
  currentLevel->score_item_tail->next = s;
  currentLevel->score_item_tail       = s;
}

void
score_item_update( score_item_t *s ) {
  if ( --s->life <= 0 ) {
    s->flags |= DEATH_MASK;
    currentLevel->last_break_timer = 0;
    return;
  }
}

void
score_item_draw( score_item_t *s ) {
  SDL_Color white = {0xff, 0xff, 0xff, 0xff};
  draw_text( s->x, s->y, &white, "res/fonts/nes.ttf", 18, s->text );
}