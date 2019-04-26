#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "cases.h"
#include "tour.h"

// Functions
void display_drawRange(int caseX, int caseY, int range);
void display_drawCircle(int fillMode);
void display_drawSquare(int fillMode);
void display_gridList(GLuint id);
void display_drawSingleTower(int X, int Y, TypeCase type);
void display_drawAllTowers();
void display_drawBoard();
void display_drawRanges();

#endif //DISPLAY_H_


