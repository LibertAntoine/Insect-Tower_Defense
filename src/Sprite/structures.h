#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <GL/gl.h>
#include <SDL2/SDL.h>

typedef struct SpriteTexture {
  //TODO: Bool loop;
  int sprite_totalX;
  int sprite_totalY;
  int sprite_numX;
  int sprite_numY;
  Uint32 loop_duration;
  Uint32 last_frame;
  GLuint texture_id;
} SpriteTexture;

#endif //STRUCTURES_H_

