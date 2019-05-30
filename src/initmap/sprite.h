#ifndef SPRITE_H_
#define SPRITE_H_

#ifdef _WIN32
  #include <GL/glew.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

#include <stdlib.h>
#include <SDL2/SDL_image.h>

#include "structures.h"

// NOTE: Un peu à part
Texture* sprite_importTexture(char image_path[], int totalX, int totalY);
void sprite_init();
SpriteTexture* sprite_loadSprite(TextureName texture_name, int loop_duration, Bool loop);
void sprite_displaySprite(SpriteTexture* sprite);
void sprite_updateSprite(SpriteTexture* sprite);
void sprite_translateTexture(SpriteTexture* sprite);

#endif //SPRITE_H_
