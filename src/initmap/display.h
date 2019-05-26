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

#include "gui.h"
#include "structures.h"
#include "cases.h"
#include "monster.h"
#include "tour.h"
#include "projectile.h"
#include "sprite.h"

void display_drawMonsterLife(float PDV);
void display_drawTriangle(int fillMode);
void display_drawCircle(int fillMode);
void display_drawTargetRange(int caseX, int caseY, int range);
void display_drawSquare(int fillMode);
void display_gridList(GLuint id);
void display_mapList(GLuint id);
void display_drawSingleMonster(Monster* monster);
int display_drawAllMonsters();
void display_drawSingleTower(int X, int Y, TypeCase type);
void display_drawAllTowers();

/**
 * @brief Affichage des tours sur le plateau.
 */
void display_drawBoard();
void display_drawAllTargetRanges();
int display_drawAllProjectiles();
void display_drawSingleProjectile(Projectile* projectile);
void display_drawItineraire(Monster* monster);

void display_game(GUI *plateau_gui, GLuint idMap, GLuint idGrid);
void display_window();
void display_left();
void display_top();
void display_drawZoneBasedOnGUI(GUI *section);
void display_setDrawingZone(GUI *section);
void display_drawSingleButton(Button *button);
#endif //DRAW_MONSTER_H_
