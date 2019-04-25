#ifndef TOUR_H_
#define TOUR_H_

#include <stdlib.h>

#include "cases.h"

typedef struct ConstructionData {
  TypeCase type;
  int degats;
  int alimentation;
  int cadence;
  int portee;
  int valeur_achat;
  int valeur_revente;
} ConstructionData;


typedef struct Tour {
  TypeCase type;
  int degats;
  int alimentation;
  int cadence;
  int portee;
} Tour;


int tour_getPrix(TypeCase type);

#endif //TOUR_H_
