#ifndef TOUR_H_
#define TOUR_H_
#pragma once

#include <stdlib.h>
#include "cases.h"

typedef enum TypeCase TypeCase;
typedef struct Monster Monster;

typedef struct Tour Tour;
struct Tour {
  TypeCase type;
  int armement;
  int centrale;
  int munition;
  int rechargement;
  int radar;
  Monster* lastMonster;
  Tour* next;
};

typedef struct ListTours {
  int nbTours;
  Tour* next;
} ListTours;

// Functions
void tour_initConstructionData();
int tour_getDegats(TypeCase type);
int tour_getAlimentation(TypeCase type);
int tour_getCadence(TypeCase type);
int tour_getRange(TypeCase type);
int tour_getPortee(TypeCase type);
int tour_getPrixAchat(TypeCase type);
int tour_getPrixRevente(TypeCase type);
Tour *tour_create(TypeCase type);
int tour_countBatiments(TypeCase type, int index_case);
void tour_completeInfo(TypeCase type, int index_case);
void tour_add(TypeCase type, int index_case);
int addToListTour(Tour* tour);
int attackTour(Tour* tour);

#endif //TOUR_H_
