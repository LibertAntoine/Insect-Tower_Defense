#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <GL/gl.h>
#include <SDL2/SDL.h>

typedef struct SpriteImage {
  SDL_Surface* surface;
  Uint32 loop_duration;
  int sprite_totalX;
  int sprite_totalY;
} SpriteImage;

typedef struct SpriteTexture {
  int sprite_totalX;
  int sprite_totalY;
  int sprite_numX;
  int sprite_numY;
  Uint32 loop_duration;
  Uint32 last_frame;
  GLuint texture_id;
} SpriteTexture;

#endif //STRUCTURES_H_

