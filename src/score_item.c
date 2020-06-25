#include "../include/score_item.h"

void
add_score_item( float x, float y, uint32_t score ) {
  score_item_t *s;
  s = malloc( sizeof( score_item_t ) );
  memset( s, 0, sizeof( score_item_t ) );

  s->x    = x;
  s->y    = y;
  s->life = 100;

  s->score = score == 0 ? 100 : score;

  if ( currentLevel->last_break_timer && score == 0 ) {
    s->score *= currentLevel->last_break_timer;
  }

  stage.score += s->score;
  char number_buffer[5];
  memset( number_buffer, '\0', sizeof( number_buffer ) );
  itoa( s->score, number_buffer, 10 );
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
  draw_text( s->x, s->y, 0xff, 0xff, 0xff, "res/fonts/nes.ttf", 18, s->text );
}