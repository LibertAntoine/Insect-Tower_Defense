#ifndef SHORT_PATH_ALGO_H_
#define SHORT_PATH_ALGO_H_

#include <stdio.h>
#include "itd-file.h"
#include "monster.h"
#include <math.h>

extern Plateau* plateau;

int getShortPath(InfosNodes* infosNodes);
void fill(int* array, int size, int value);
double distanceNodes(Node StartNode, Node ArrivedNode);
int initItineraire(Monster* monster, InfosNodes* infosNodes);
int addToItineraire(Itineraire* itineraire, Node* node);
#endif //SHORT_PATH_ALGO_H_