#ifndef CASES_H_
#define CASES_H_

#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

typedef enum TypeCase {
  LASER = 0,
  MISSILE,
  RADAR,
  ARMEMENT,
  CENTRALE,
  MUNITION,
  TERRAIN,
  CHEMIN,
} TypeCase;

typedef struct Plateau {
  int Xsplit;
  int Ysplit;
  TypeCase *cases;
} Plateau;

void case_initPlateau(Plateau *plateau, int Xsplit, int Ysplit);

int case_getCaseIndex(Plateau *plateau, int caseX, int caseY);

int case_getType(Plateau *plateau, int caseX, int caseY);

int case_getCaseCoordFromPixels(Plateau *plateau, int positionX, int positionY, int *caseX, int *caseY, int px_width, int px_height);


int case_isEmpty(Plateau *plateau, int caseX, int caseY);



#endif //CASES_H_
