#ifndef CASES_H_
#define CASES_H_

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <stdio.h>

#include "structures.h"

#include "itd-file.h"
#include "ppm-loader.h"
#include "tour.h"
#include "player.h"
#include "monster.h"
#include "projectile.h"

TypeCase* case_loadFromPPM();
Plateau* case_initPlateau();
int case_RGBCompare(RGBcolor color1, RGBcolor color2);

int case_getCaseIndex(int caseX, int caseY);
void case_getCasePosition(int caseIndex, int* caseX, int* caseY);
TypeCase case_getType(int caseX, int caseY);
int case_getCaseCoordFromPixels(int positionX, int positionY, int *caseX, int *caseY, int px_width, int px_height);
GeneralType case_getGeneralConstructionType(TypeCase type);
int case_isConstructible(int caseX, int caseY);
void case_update(int caseX, int caseY, TypeCase newType);
int case_isUserPlaced(int caseX, int caseY);
void case_removeConstruction(int caseX, int caseY);
void case_addConstruction(int caseX, int caseY);
void case_printInfos(int caseX, int caseY);
Tour* case_getTourPointer(int caseX, int caseY);

void get_casesi(int *caseX, int *caseY, Div *plateau_div);
void get_casesf(float *caseX, float *caseY, Div *plateau_div);

void case_actionAdd(int caseX, int caseY);
void case_actionRemove(int caseX, int caseY);
void case_actionInfo(int caseX, int caseY);
void case_handleAction(int caseX, int caseY);
void case_freePlateau();
#endif //CASES_H_

