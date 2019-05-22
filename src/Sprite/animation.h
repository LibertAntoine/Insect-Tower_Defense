#ifndef ANIMATION_H_
#define ANIMATION_H_

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
SpriteImage *animation_loadSprite(char image_path[], int total_splitX, int total_splitY, Uint32 loop_duration);

SpriteTexture* animation_loadTexture(SpriteImage *sprite_data);
void animation_displaySprite(SpriteTexture* sprite);
void animation_updateSprite(SpriteTexture* sprite);
void animation_translateTexture(SpriteTexture* sprite);

#endif //ANIMATION_H_
