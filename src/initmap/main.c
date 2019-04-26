#include <stdio.h>
#include <stdlib.h>

#include "cases.h"
#include "ppm-loader.h"
#include "itd-file.h"
#include "short-path-algo.h"

extern Plateau* plateau;

int main(int argc, char *argv[])
{
    MapData* mapData = itd_initMapData();
    idt_load("level1.itd", mapData);
    
    case_initPlateau(mapData);
      
    int* idEntrees = malloc(sizeof(int)*plateau->nbEntree);
    
    getIdEntrees(mapData, idEntrees);
    
    int idOut = getIdOut(mapData);
    int* distances = malloc(sizeof(int)*mapData->nbNoeud);
    Node* previous = malloc(sizeof(Node)*mapData->nbNoeud);
    getShortPath(mapData, distances, previous, idOut);
}
