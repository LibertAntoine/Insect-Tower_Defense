#ifndef CASES_H_
#define CASES_H_

#ifdef WIN32
    #include <GL/glew.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <stdio.h>
#include "../check-itd-file/itd-file.h"
#include "ppm-loader.h"

typedef enum TypeCase {
  LASER = 0,
  MISSILE,
  RADAR,
  ARMEMENT,
  CENTRALE,
  MUNITION,
  TERRAIN,
  CHEMIN,
  NOEUD,
  ENTREE,
  SORTIE
} TypeCase;


typedef struct Plateau {
  int Xsplit;
  int Ysplit;
  TypeCase *cases;
} Plateau;

int case_initPlateau(Plateau* plateau, MapData* mapdata);
int case_RGBCompare(RGBcolor color1, RGBcolor color2);

int case_getCaseIndex(Plateau *plateau, int caseX, int caseY);
int case_getType(Plateau *plateau, int caseX, int caseY);
int case_getCaseCoordFromPixels(Plateau *plateau, int positionX, int positionY, int *caseX, int *caseY, int px_width, int px_height);
int case_isEmpty(Plateau *plateau, int caseX, int caseY);

#endif //CASES_H_

