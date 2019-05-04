#ifndef CASES_H_
#define CASES_H_

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <stdio.h>
#include "itd-file.h"
#include "ppm-loader.h"
#include "tour.h"
#include "player.h"
#include "monster.h"


typedef struct ListTours ListTours;
typedef struct ListMonsters ListMonsters;
typedef struct Tour Tour;
typedef struct ListProjectiles ListProjectiles;

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
  NOEUD,
  ENTREE,
  SORTIE
} TypeCase;

typedef struct Monster Monster;

typedef struct Tour {
  TypeCase type;
  int armement;
  int centrale;
  int munition;
  float rechargement;
  int radar;
  double x;
  double y;
  Monster* lastMonster;
  struct Tour* next;
} Tour;

typedef enum Action {
  ADD,
  GETINFO,
  REMOVE
} Action;

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
  ListTours* listTours;
  ListMonsters* listMonsters;
  ListProjectiles* listProjectiles;
  Tour **tours;
  TypeCase *cases;
} Plateau;

extern Plateau *plateau;

/** 
 * @brief Remplis les informations de cases de la structure plateau.
 * @param[in] mapData données du fichier .itd.
 */
int case_initPlateau(MapData* mapdata);
int case_RGBCompare(RGBcolor color1, RGBcolor color2);

int case_getCaseIndex(int caseX, int caseY);
void case_getCasePosition(int caseIndex, int* caseX, int* caseY);
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

