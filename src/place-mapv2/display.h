#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include "cases.h"

// Functions
void display_gridList(Plateau *plateau, GLuint id);
void display_drawSingleTower(int X, int Y, TypeCase type);
void display_drawAllTowers(Plateau *plateau) ;

#endif //DISPLAY_H_


