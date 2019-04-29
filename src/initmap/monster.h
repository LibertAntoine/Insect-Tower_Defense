#ifndef MONSTER_H_
#define MONSTER_H_

#include <stdio.h>
#include "cases.h"

typedef enum Orientation {
   HAUT,
   BAS,
   GAUCHE,
   DROITE
} TypeMonster;


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
   int type;
   int orientation;
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

ListMonsters* initListMonsters();
int addToList(ListMonsters* listmonsters, Monster* monster);
int createMonster(ListMonsters* listmonster, InfosNodes* InfosNodes, int type, int idIN);
void attackMonster(Monster* monster, int damage);
void killMonster(Monster* monster);
int moveMonster(Monster* monster);
int moveAllMonster(ListMonsters* listmonsters);
#endif //MONSTER_H_