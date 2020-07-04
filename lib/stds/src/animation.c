#include "../include/animation.h"

static char input_buffer[MAX_BUFFER_SIZE];

animation_t *
add_spritesheet( char *directory, uint8_t no_of_frames, float frame_delay, uint16_t x,
                 uint16_t y ) {
  animation_t *a;
  a = malloc( sizeof( animation_t ) );

  if ( a == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for animation_t. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( a, 0, sizeof( animation_t ) );

  a->number_of_frames = no_of_frames;
  a->current_texture  = load_texture( directory );
  a->frame_delay      = frame_delay;
  a->frame_timer      = frame_delay * FPS;
  a->start_x          = x;
  a->start_y          = y;

  SDL_QueryTexture( a->current_texture, NULL, NULL, &a->sprite_sheet_width,
                    &a->sprite_sheet_height );

  a->w = a->sprite_sheet_width / no_of_frames;
  a->h = a->sprite_sheet_height;

  a->current_frame_id = 0;
  a->id_flags |= SPRITE_SHEET_MASK;
  a->flags |= ANIMATION_ACTIVE_MASK;
}

animation_t *
add_animation( char *directory, uint8_t no_of_frames, float frame_delay ) {
  animation_t *a;
  a = malloc( sizeof( animation_t ) );

  if ( a == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for animation_t. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  memset( a, 0, sizeof( animation_t ) );

  a->frames = malloc( sizeof( SDL_Texture * ) * no_of_frames );

  if ( a->frames == NULL ) {
    SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for a->frames. %s.\n",
                 SDL_GetError() );
    exit( EXIT_FAILURE );
  }

  a->number_of_frames = no_of_frames;
  a->frame_delay      = frame_delay;
  a->frame_timer      = frame_delay * FPS;
  a->current_frame_id = 0;

  SDL_QueryTexture( a->current_texture, NULL, NULL, &a->w, &a->h );
  a->id_flags |= STD_ANIMATION_MASK;
  a->flags |= ANIMATION_ACTIVE_MASK;

  char  number_buffer[3];
  char *file_extsn = ".png";
  for ( int i = 0; i < a->number_of_frames; i++ ) {
    itoa( i, number_buffer, 10 );
    strcpy( input_buffer, directory );
    char *file_name     = strcat( input_buffer, number_buffer );
    char *file_name_ext = strcat( input_buffer, file_extsn );
    a->frames[i]        = load_texture( file_name_ext );
    memset( input_buffer, '\0', sizeof( input_buffer ) );
  }
  a->current_texture = a->frames[0];
  a->default_texture = a->frames[0];
}

void
animation_update( animation_t *a ) {
  if ( a->flags & ANIMATION_ACTIVE_MASK )
    a->frame_timer -= 1;

  if ( a->frame_timer < 0 ) {
    // Resets the frame countdown.
    a->frame_timer = a->frame_delay * FPS;
    a->current_frame_id += 1;

    // If we have a spritesheet, we advance x coordinate
    // of the sprite. Otherwise, we advance the pointer
    // referencing which sprite to render in the
    if ( a->id_flags & SPRITE_SHEET_MASK ) {
      a->splice_x += a->sprite_sheet_width / a->number_of_frames;
    } else {
      a->current_texture = a->frames[a->current_frame_id];
    }

    // If we reach the end of the animation sequence,
    // return to the start.
    if ( a->current_frame_id >= a->number_of_frames ) {
      a->current_frame_id = 0;
      if ( a->id_flags & SPRITE_SHEET_MASK ) {
        a->splice_x = 0;
      } else {
        a->current_frame_id = 0;
      }

      // If we have the flag enabled to cycle through the animation
      // only once (and we just finished), deactivate the flag to
      // continue and quit.
      if ( a->cycle_once ) {
        a->flags ^= ANIMATION_ACTIVE_MASK;
        a->cycle_once = false;
        return;
      }
    }
  }
}

void
animation_draw( animation_t *a ) {
  if ( a->flags & ANIMATION_ACTIVE_MASK ) {
    if ( a->id_flags & STD_ANIMATION_MASK ) {
      blit_texture_rotated( a->frames[a->current_frame_id], a->pos_x, a->pos_y, a->angle, a->flip);
    } else if ( a->id_flags & SPRITE_SHEET_MASK ) {
      // Yes, the math IS correct; don't second-guess yourself!
      // The offset is due to the RECTANGLE!
      //
      // This rectangle splices the correct frame
      // from the sprite sheet.
      SDL_Rect curr_rect;
      curr_rect.x = ( int32_t ) a->splice_x;
      curr_rect.y = ( int32_t ) a->splice_y;
      curr_rect.w = a->w;
      curr_rect.h = a->h;
      blit_rect( a->current_texture, &curr_rect, a->pos_x, a->pos_y );
    }
  }
}

void
animation_die( animation_t *a ) {
  for ( int i = 0; i < a->number_of_frames; i++ ) {
    SDL_DestroyTexture( a->frames[i] );
  }

  SDL_DestroyTexture( a->current_texture );
  free( a->frames );
  free( a );
}
