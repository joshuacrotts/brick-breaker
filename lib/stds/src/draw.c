#include "../include/draw.h"

static SDL_Texture* getTexture(char*);
static void addTextureToCache(char*, SDL_Texture*);

void prepareScene() {
  SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
  SDL_RenderClear(app.renderer);
}

void presentScene() {
  SDL_RenderPresent(app.renderer);
}

void blit(SDL_Texture* texture, float x, float y, bool isCenter) {
  SDL_Rect dest;

  dest.x = (int) x;
  dest.y = (int) y;

  SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

  if (isCenter) {
    dest.x -= (dest.w >> 1);
    dest.y -= (dest.h >> 1);
  }

  SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blitRect(SDL_Texture* texture, SDL_Rect* src, float x, float y) {
  SDL_Rect dest;
  dest.x = (int) x;
  dest.y = (int) y;

  dest.w = src->w;
  dest.h = src->h;
  SDL_RenderCopy(app.renderer, texture, src, &dest);
}

void blitRotated(SDL_Texture* texture, float x, float y, uint16_t angle) {
  SDL_Rect destRect;
  destRect.x = (int) x;
  destRect.y = (int) y;
  SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);

  destRect.x -= (destRect.w >> 1);
  destRect.y -= (destRect.h >> 1);

  SDL_RenderCopyEx(app.renderer, texture, NULL, &destRect, angle, NULL, SDL_FLIP_NONE);
}

void blitColorTextureScaled(SDL_Texture* texture, float x, float y, float scaleX, float scaleY, uint16_t angle, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  uint32_t textureWidth = 0;
  uint32_t textureHeight = 0;

  SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

  // Apply the scaling procedure to the image.
  SDL_Rect dest_rect;
  dest_rect.x = (int32_t) x;
  dest_rect.y = (int32_t) y;
  dest_rect.w = (uint32_t) (textureWidth * scaleX);
  dest_rect.h = (uint32_t) (textureHeight * scaleY);

  // If all four color values are less than 0, don't draw a color.
  if (r >= 0 && g >= 0 && b >= 0 && a >= 0) {
    SDL_SetTextureColorMod(texture, r, g, b);
    SDL_SetTextureAlphaMod(texture, a);
  }
  SDL_RenderCopyEx(app.renderer, texture, NULL, &dest_rect, angle, NULL, SDL_FLIP_NONE);
}

void blitTextureScaled(SDL_Texture* texture, float x, float y, float scaleX, float scaleY, uint16_t angle) {
  blitColorTextureScaled(texture, x, y, scaleX, scaleY, angle, -1, -1, -1, -1);
}

void drawRect(SDL_Rect* rect, uint8_t r, uint8_t g, uint8_t b, uint8_t a, bool isFilled) {
  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(app.renderer, r, g, b, a);

  if (isFilled) {
    SDL_RenderFillRect(app.renderer, rect);
  } else {
    SDL_RenderDrawRect(app.renderer, rect);
  }
  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

void drawRectStroke(int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t stroke, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  if (stroke <= 0) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error: stroke %d cannot be a negative or zero value!", stroke);
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

    drawRect(&r1, r, g, b, a, true);
    drawRect(&r2, r, g, b, a, true);
    drawRect(&r3, r, g, b, a, true);
    drawRect(&r4, r, g, b, a, true);
  }
}

void drawLine(float x1, float y1, float x2, float y2, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  SDL_SetRenderDrawColor(app.renderer, r, g, b, a);
  SDL_RenderDrawLine(app.renderer, (int32_t) x1, (int32_t) y1, (int32_t) x2, (int32_t) y2);
}

void drawCircle(int32_t centerX, int32_t centerY, uint32_t radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
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
      SDL_RenderDrawPoint(app.renderer, centerX + x, centerY - y);
      SDL_RenderDrawPoint(app.renderer, centerX + x, centerY + y);
      SDL_RenderDrawPoint(app.renderer, centerX - x, centerY - y);
      SDL_RenderDrawPoint(app.renderer, centerX - x, centerY + y);
      SDL_RenderDrawPoint(app.renderer, centerX + y, centerY - x);
      SDL_RenderDrawPoint(app.renderer, centerX + y, centerY + x);
      SDL_RenderDrawPoint(app.renderer, centerX - y, centerY - x);
      SDL_RenderDrawPoint(app.renderer, centerX - y, centerY + x);

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

void fillCircle(int32_t x, int32_t y, uint32_t radius, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
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

SDL_Color combineFadeColor(FadeColor* f) {
  if (f->time <= 1.0f && f->firstColor) {
    f->time = (float) (f->time + f->alpha);
  } else {
    f->firstColor = false;
  }

  if (f->time >= 0.0f && !f->firstColor) {
    f->time = (float) (f->time - f->alpha);
  } else {
    f->firstColor = true;
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

SDL_Texture* loadTexture(char* fileName) {
  SDL_Texture* texture;

  texture = getTexture(fileName);

  if (texture == NULL) {
    texture = IMG_LoadTexture(app.renderer, fileName);
    if (texture == NULL) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Error: could not load image %s. Error Code: %s.\n", fileName, SDL_GetError());
      exit(EXIT_FAILURE);
    }
    
    addTextureToCache(fileName, texture);
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
static SDL_Texture* getTexture(char* fileName) {
  Texture* t;

  for (t = app.textureHead.next; t != NULL; t = t->next) {
    if (strcmp(t->name, fileName) == 0) {
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
static void addTextureToCache(char* fileName, SDL_Texture* sdlTexture) {
  Texture* texture;

  texture = malloc(sizeof(Texture));
  memset(texture, 0, sizeof(Texture));
  app.textureTail->next = texture;
  app.textureTail = texture;

  strncpy(texture->name, fileName, MAX_FILE_NAME_LEN);
  texture->texture = sdlTexture;
}
