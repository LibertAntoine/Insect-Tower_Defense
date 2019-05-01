#ifndef MONSTER_H_
#define MONSTER_H_

#include <stdio.h>
#include <math.h>
#include "cases.h"
#include "tour.h"
#include "projectile.h"

typedef struct Tour Tour;
typedef struct Projectile Projectile;

typedef enum Orientation {
   HAUT,
   BAS,
   GAUCHE,
   DROITE
} Orientation;

typedef enum Statut {
   ALIVE,
   DEAD
} Statut;

typedef struct Etape Etape;
struct Etape {
    Node* node;
    Etape* next;
};

typedef struct Itineraire {
   int nbEtape;
   Etape* next;
} Itineraire;


typedef struct Monster Monster;
struct Monster {
   int PDV;
   int strength;
   double mass;
   int idIn;
   TypeMonster type;
   Statut status;
   Orientation orientation;
   double x;
   double y;
   Itineraire* itineraire;
   Monster* next; 
};

typedef struct DataMonsters {
   int* PDV;
   int* strength;
   double* mass;
} DataMonsters;

typedef struct ListMonsters {
   int nbMonsters;
   Monster* firstMonster;
   DataMonsters* dataMonsters;
} ListMonsters;

int initListMonsters();
int addToList(Monster* monster);
int createMonster(InfosNodes* InfosNodes, int type, int idIN);
void attackMonster(Projectile* projectile);
int deleteToList(Monster* monster);
void killMonster(Monster* monster);
int moveMonster(Monster* monster);

/**
 * @brief Parcours la liste de montre afin d'en demander le déplacement.
 */
int moveAllMonster();
int findMonster(Tour* tour);
int refindMonster(Tour* tour);
#endif //MONSTER_H_
