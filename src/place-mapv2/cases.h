#ifndef CASES_H_
#define CASES_H_

#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>


typedef enum GeneralType {
  TOUR = 1,
  BATIMENT = 2,
  OTHER
} GeneralType;

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

typedef struct ConstructionData {
  TypeCase type;
  int degats;
  int alimentation;
  int cadence;
  int portee;
  int range;
  int valeur_achat;
  int valeur_revente;
} ConstructionData;

typedef struct Tour {
  TypeCase type;
  int armement;
  int centrale;
  int munition;
  int radar;
} Tour;

typedef enum Action {
  ADD,
  GETINFO,
  REMOVE
} Action;

typedef struct Etat {
  TypeCase type;
  Action action;
  int argent;
} Etat;

typedef struct Plateau {
  int Xsplit;
  int Ysplit;
  Etat joueur;
  ConstructionData constructionData[6];
  Tour **tours;
  TypeCase *cases;
} Plateau;

#include "tour.h"
#include "player.h"

extern Plateau *plateau;

// Functions
void case_initPlateau(int Xsplit, int Ysplit);
int case_getCaseIndex(int caseX, int caseY);
int case_getType(int caseX, int caseY);
int case_getCaseCoordFromPixels(int positionX, int positionY, int *caseX, int *caseY, int px_width, int px_height);
GeneralType case_getGeneralConstructionType(TypeCase type);
int case_isConstructible(int caseX, int caseY);
void case_update(int caseX, int caseY, TypeCase newType);
int case_isUserPlaced(int caseX, int caseY);
void case_removeConstruction(int caseX, int caseY);
void case_addConstruction(int caseX, int caseY);
void case_printInfos(int caseX, int caseY);

#endif //CASES_H_
