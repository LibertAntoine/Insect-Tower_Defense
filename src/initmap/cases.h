#ifndef CASES_H_
#define CASES_H_

#ifdef WIN32
    #include <GL/glew.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

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
  int nbEntree; 
} Plateau;

#include <stdio.h>
#include "itd-file.h"
#include "ppm-loader.h"

int case_initPlateau(MapData* mapdata);
int case_RGBCompare(RGBcolor color1, RGBcolor color2);

int case_getCaseIndex(int caseX, int caseY);
int case_getType(int caseX, int caseY);
int case_getCaseCoordFromPixels(int positionX, int positionY, int *caseX, int *caseY, int px_width, int px_height);
int case_isEmpty(int caseX, int caseY);

#endif //CASES_H_

