#ifndef CASES_H_
#define CASES_H_

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

int Xsplit;
int Ysplit;

typedef enum TypeCase {
  TOWER_ACTIVE = 1,
  TOWER_INACTIVE,
  CENTRALE
} TypeCase;

int case_getCaseIndex(int caseX, int caseY);
int case_getCaseCoordFromPixels(int positionX, int positionY, int *caseX, int *caseY, int px_width, int px_height);
int case_isEmpty(int caseX, int caseY, int cases[]);
void case_addTower(int caseX, int caseY, int cases[], TypeCase type);
void case_activateAllTowers(int cases[], int range);

#endif //CASES_H_

