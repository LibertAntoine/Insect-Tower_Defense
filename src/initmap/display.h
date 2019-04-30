#ifndef DRAW_MONSTER_H_
#define DRAW_MONSTER_H_
#pragma once

#ifdef _WIN32
    #include <GL/glew.h>
    #define _USE_MATH_DEFINES
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cases.h"
#include "monster.h"
#include "tour.h"




void display_drawCircle(int fillMode);
void display_drawTargetRange(int caseX, int caseY, int range);
void display_drawSquare(int fillMode);
void display_gridList(GLuint id);
void display_drawSingleMonster(Monster* monster);
int display_drawAllMonsters();
void display_drawSingleTower(int X, int Y, TypeCase type);
void display_drawAllTowers();
void display_drawBoard();
void display_drawAllTargetRanges();

#endif //DRAW_MONSTER_H_
