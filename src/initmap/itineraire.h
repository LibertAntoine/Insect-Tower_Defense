#ifndef SHORT_PATH_ALGO_H_
#define SHORT_PATH_ALGO_H_
#pragma once

#include <stdio.h>
#include <math.h>

#include "itd-file.h"
#include "cases.h"

// TODO: convention de nommage des fonctions
// NOTE: le but est de facilement trouver ce qu'elles font et où les trouver

int *itineraire_initVisitedArray(int size);
int *itineraire_initDistanceArray(int size);

int itineraire_findShortestPath(InfosNodes* infosNodes);
void fill(int* array, int size, int value);
double distanceNodes(Node StartNode, Node ArrivedNode);
int itineraire_initMonster(Monster* monster, InfosNodes* infosNodes);
int addToItineraire(Itineraire* itineraire, Node* node);
#endif //SHORT_PATH_ALGO_H_
