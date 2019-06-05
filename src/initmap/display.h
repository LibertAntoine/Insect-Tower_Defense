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
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include "gui.h"
#include "structures.h"
#include "cases.h"
#include "monster.h"
#include "tour.h"
#include "projectile.h"
#include "sprite.h"
#include <time.h>

GLuint display_initDefaultListIcon(TextureName texture_name);
void display_printMoney();
void display_menuButtonText(Button* button);
void display_mainMenu();
void display_endMenu();
void display_showCursor();
void display_genTourList(Tour* tour);
void display_genBatimentList(TypeCase type);

void display_drawCaseHover(int index_case);
TextureText*  display_loadTextureText(char text[]);
void display_drawSingleStat(GeneralType generalType, char text[], TextureName texture_name, char str2[]);
void display_initDefaultList();
void display_printInfos();
void display_drawMonsterLife(float PDV);
void display_drawTriangle(int fillMode);
void display_drawCircle(int fillMode);
void display_drawTargetRange(int caseX, int caseY, float range);
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
void display_buttonBackground(Display display);

void display_game(GUI *plateau_gui, GLuint idMap, GLuint idGrid);
void display_window();
void display_left();
void display_top();
void display_drawZoneBasedOnGUI(GUI *section);
void display_drawButtonsBasedOnGUI(GUI *section);
void display_setDrawingZone(GUI *section);
void display_drawSingleButton(Button *button);
#endif //DRAW_MONSTER_H_
