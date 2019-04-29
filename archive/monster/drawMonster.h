#ifndef DRAW_MONSTER_H_
#define DRAW_MONSTER_H_

#include <stdio.h>
#include <stdlib.h>
#include "caseS.h"

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

typedef enum TypeMonster {
  SOLDER,
  FIRST_SOLDER,
  GENERAL
} TypeCase;




void display_gridList(GLuint id);
void display_drawSingleMonster(int X, int Y, TypeCase type);

#endif //DRAW_MONSTER_H_