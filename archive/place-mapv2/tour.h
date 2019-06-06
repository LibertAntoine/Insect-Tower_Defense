#ifndef TOUR_H_
#define TOUR_H_

#include <stdlib.h>

#include "cases.h"


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

#endif //TOUR_H_
