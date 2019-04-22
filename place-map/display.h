#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include "cases.h"

void display_gridList(GLuint id);
void display_drawSingleTower(int X, int Y, TypeCase type);
void display_drawAllTowers(int cases[]);

#endif //DISPLAY_H_

