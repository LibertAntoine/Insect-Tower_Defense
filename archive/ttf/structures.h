#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#ifdef _WIN32
  #include <GL/glew.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

typedef struct Div {
  int x;
  int y;
  int width;
  int height;
} Div;

typedef struct TextureText {
  GLuint texture_id;
  float ratio;
} TextureText;

#endif //STRUCTURES_H_
