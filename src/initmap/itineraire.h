#ifndef ITINERAIRE_H_
#define ITINERAIRE_H_
#pragma once

#include <stdio.h>
#include <math.h>

#include "structures.h"

#include "itd-file.h"
#include "cases.h"
#include "monster.h"

// TODO: convention de nommage des fonctions
// NOTE: le but est de facilement trouver ce qu'elles font et où les trouver

int *itineraire_initVisitedArray(int size);
int *itineraire_initDistanceArray(int size);

int itineraire_findShortestPath(InfosNodes* infosNodes);
void itineraire_fillArray(int* array, int size, int value);
double itineraire_getValueChemin(Node startNode, Node arrivedNode);
int itineraire_initMonster(Monster* monster, InfosNodes* infosNodes);
void itineraire_addEtape(Itineraire* itineraire, Node* node);

ListChemins* itineraire_initListChemins(MapData* mapData);
void itineraire_checkExistChemin(ListChemins* listChemins, Node* node_in, Node* node_out);
void itineraire_addChemin(ListChemins* listChemins, Node* node_in, Node* node_out);
void itineraire_addValueChemin(Monster* monster);
void itineraire_removeValueChemin(Monster* monster);
Chemin* itineraire_getChemin(Node* node_in, Node* node_out);


#endif //ITINERAIRE_H_
