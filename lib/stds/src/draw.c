#include "../include/draw.h"

static SDL_Texture* get_texture(char*);
static void cache_texture(char*, SDL_Texture*);


void 
prepare_scene() {
  SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
  SDL_RenderClear(app.renderer);
}


void 
present_scene() {
  SDL_RenderPresent(app.renderer);
}


void 
blit_texture(SDL_Texture* texture, float x, float y, bool is_center) {
  SDL_Rect dest;

  dest.x = (int) x;
  dest.y = (int) y;

  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

  if (is_center) {
    dest.x -= (dest.w >> 1);
    dest.y -= (dest.h >> 1);
  }

  SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}


void 
blit_rect(SDL_Texture* texture, SDL_Rect* src, float x, float y) {
  SDL_Rect dest;
  dest.x = (int) x;
  dest.y = (int) y;

  dest.w = src->w;
  dest.h = src->h;
  SDL_RenderCopy(app.renderer, texture, src, &dest);
}


void 
blit_texture_rotated(SDL_Texture* texture, float x, float y, uint16_t angle) {
  SDL_Rect dest;
  dest.x = (int) x;
  dest.y = (int) y;
  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

  dest.x -= (dest.w >> 1);
  dest.y -= (dest.h >> 1);

  SDL_RenderCopyEx(app.renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}


void 
blit_texture_color_scaled(SDL_Texture* texture, float x, float y, float scale_x, float scale_y, uint16_t angle, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  uint32_t texture_width = 0;
  uint32_t texture_height = 0;

  SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);

  // Apply the scaling procedure to the image.
  SDL_Rect dest_rect;
  dest_rect.x = (int32_t) x;
  dest_rect.y = (int32_t) y;
  dest_rect.w = (uint32_t) (texture_width * scale_x);
  dest_rect.h = (uint32_t) (texture_height * scale_y);

  // If all four color values are less than 0, don't draw a color.
  if (r >= 0 && g >= 0 && b >= 0 && a >= 0) {
    SDL_SetTextureColorMod(texture, r, g, b);
    SDL_SetTextureAlphaMod(texture, a);
  }
  SDL_RenderCopyEx(app.renderer, texture, NULL, &dest_rect, angle, NULL, SDL_FLIP_NONE);
}


void 
blit_texture_scaled(SDL_Texture* texture, float x, float y, float scale_x, float scale_y, uint16_t angle) {
  blit_texture_color_scaled(texture, x, y, scale_x, scale_y, angle, -1, -1, -1, -1);
}


void 
draw_rect(SDL_Rect* rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a, bool is_filled) {
  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(app.renderer, r, g, b, a);

  if (is_filled) {
    SDL_RenderFillRect(app.renderer, rect);
  } else {
    SDL_RenderDrawRect(app.renderer, rect);
  }
  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}


void 
draw_rect_stroke(int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t stroke, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  if (stroke <= 0) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Error: stroke %d cannot be a negative or zero value!", stroke);
    exit(EXIT_FAILURE);
  } else {
    SDL_Rect r1;
    SDL_Rect r2;
    SDL_Rect r3;
    SDL_Rect r4;

    // Top-left to TR
    r1.x = x;
    r1.y = y;
    r1.w = w;
    r1.h = stroke;

    //TL to BL
    r2.x = x;
    r2.y = y;
    r2.w = stroke;
    r2.h = h;

    //BL to BR
    r3.x = x;
    r3.y = h - stroke;
    r3.w = w;
    r3.h = stroke;

    r4.x = w - stroke;
    r4.y = y;
    r4.w = stroke;
    r4.h = h;

    draw_rect(&r1, r, g, b, a, true);
    draw_rect(&r2, r, g, b, a, true);
    draw_rect(&r3, r, g, b, a, true);
    draw_rect(&r4, r, g, b, a, true);
  }
}


void 
draw_line(float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
  SDL_RenderDrawLine(app.renderer, (int32_t) x1, (int32_t) y1, (int32_t) x2, (int32_t) y2);
}


void 
draw_circle(int32_t center_x, int32_t center_y, uint32_t radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(app.renderer, center_x + x, center_y - y);
      SDL_RenderDrawPoint(app.renderer, center_x + x, center_y + y);
      SDL_RenderDrawPoint(app.renderer, center_x - x, center_y - y);
      SDL_RenderDrawPoint(app.renderer, center_x - x, center_y + y);
      SDL_RenderDrawPoint(app.renderer, center_x + y, center_y - x);
      SDL_RenderDrawPoint(app.renderer, center_x + y, center_y + x);
      SDL_RenderDrawPoint(app.renderer, center_x - y, center_y - x);
      SDL_RenderDrawPoint(app.renderer, center_x - y, center_y + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}


void 
fill_circle(int32_t x, int32_t y, uint32_t radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  int offsetx, offsety, d;
  int status;

  offsetx = 0;
  offsety = radius;
  d = radius - 1;
  status = 0;
  SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
  
  while (offsety >= offsetx) {
      status += SDL_RenderDrawLine(app.renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
      status += SDL_RenderDrawLine(app.renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
      status += SDL_RenderDrawLine(app.renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
      status += SDL_RenderDrawLine(app.renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);

      if (status < 0) {
          status = -1;
          break;
      }

      if (d >= 2 * offsetx) {
          d -= 2 * offsetx + 1;
          offsetx +=1;
      }
      else if (d < 2 * (radius - offsety)) {
          d += 2 * offsety - 1;
          offsety -= 1;
      }
      else {
          d += 2 * (offsety - offsetx - 1);
          offsety -= 1;
          offsetx += 1;
      }
  }
}


SDL_Color 
combine_fade_color(fade_color_t *f) {
  if (f->time <= 1.0f && f->is_first_color) {
    f->time = (float) (f->time + f->alpha);
  } else {
    f->is_first_color = false;
  }

  if (f->time >= 0.0f && !f->is_first_color) {
    f->time = (float) (f->time - f->alpha);
  } else {
    f->is_first_color = true;
  }

  int r = (int) (f->time * f->c2.r + (1.0f - f->time) * f->c1.r);
  int g = (int) (f->time * f->c2.g + (1.0f - f->time) * f->c1.g);
  int b = (int) (f->time * f->c2.b + (1.0f - f->time) * f->c1.b);
  
  SDL_Color c;
  c.r = clamp(r, 0, 0xff);
  c.g = clamp(g, 0, 0xff);
  c.b = clamp(b, 0, 0xff);

  return c;
}


SDL_Texture* 
load_texture(char *fileName) {
  SDL_Texture* texture;

  texture = get_texture(fileName);

  if (texture == NULL) {
    texture = IMG_LoadTexture(app.renderer, fileName);
    if (texture == NULL) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Error: could not load image %s. Error Code: %s.\n", fileName, SDL_GetError());
      exit(EXIT_FAILURE);
    }
    
    cache_texture(fileName, texture);
  }

  return texture;
}


/*
 * Searches through the SDL_Texture list to see if we have previously
 * loaded in this texture. If so, it is returned. Otherwise, NULL.
 * 
 * @param file name of SDL_Texture.
 * @return SDL_Texture pointer - either NULL or object.
 */
static SDL_Texture* 
get_texture(char *file_name) {
  texture_t* t;

  for (t = app.texture_head.next; t != NULL; t = t->next) {
    if (strcmp(t->name, file_name) == 0) {
      return t->texture;
    }
  }
}


/*
 * If a SDL_Texture has not been previously loaded in, we add it to
 * the cache here. The cache is a linked-list of SDL_Texture pointers
 * that store references to each texture so we do not waste resources
 * opening the input stream and loading the data back in.
 * 
 * @param file name, and pointer to the texture.
 * @return void.
 */
static void 
cache_texture(char *file_name, SDL_Texture *sdl_texture) {
  texture_t* texture;

  texture = malloc(sizeof(texture_t));

  if (texture == NULL) {
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for texture_t. %s.\n", SDL_GetError());
    exit(EXIT_FAILURE);    
  }
  
  memset(texture, 0, sizeof(texture_t));
  app.texture_tail->next = texture;
  app.texture_tail = texture;

  strncpy(texture->name, file_name, MAX_FILE_NAME_LEN);
  texture->texture = sdl_texture;
}
