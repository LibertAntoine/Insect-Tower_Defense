#include "short-path-algo.h"



int getShortPath(MapData* mapdata, int* distances, Node* previous, int idOut) {
    if (idOut > mapdata->nbNoeud -1 || idOut <= 0) {
        return 0;
    }
    int* idVisited = malloc(sizeof(int)*mapdata->nbNoeud);
    fill(idVisited, mapdata->nbNoeud, 0);
    fill(distances, mapdata->nbNoeud, plateau->Xsplit*plateau->Ysplit);
    distances[idOut] = 0;
    int i = idOut;
    int dis;
    while (i != -1) {
        idVisited[i] = 1;
        for(int j = 0; j < 4; j++)
        {   

            if(mapdata->nodes[i].link[j] == -1) {break;}
            else if (distances[i] + distanceNodes(mapdata->nodes[i], mapdata->nodes[mapdata->nodes[i].link[j]]) < distances[mapdata->nodes[i].link[j]]) { 
                distances[mapdata->nodes[i].link[j]] = distances[i] + distanceNodes(mapdata->nodes[i], mapdata->nodes[mapdata->nodes[i].link[j]]);
                previous[mapdata->nodes[i].link[j]] = mapdata->nodes[i];
            }
        }
        i = -1;
        dis = plateau->Xsplit*plateau->Ysplit;
        for(int k = 0; k < mapdata->nbNoeud; k++) {
            
            if(!idVisited[k] && dis >= distances[k]) { 
                dis = distances[k];     
                i = k;   
            }
        }
        
    }
}


void fill(int* array, int size, int value) {
    for(int i = 0; i < size; i++) {
        array[i] = value;
    }
}

double distanceNodes(Node StartNode, Node ArrivedNode) {
    if (StartNode.x == ArrivedNode.x) {
        return fabs(StartNode.y - ArrivedNode.y);
    } else if (StartNode.y == ArrivedNode.y) {
        return fabs(StartNode.x - ArrivedNode.x);
    } else {
        return 0;
    }
}
int getIdEntrees(MapData* mapData, int* idEntrees) {
    int j = 0;
    for (int i = 0; i < mapData->nbNoeud; i++)
    {
        if(mapData->nodes[i].type == 2) {
            idEntrees[j] = mapData->nodes[i].id;
            j++;
        }
    }
    if (plateau->nbEntree != j) {
        return 0;
    } else {
        return 1;
    }
}

int getIdOut(MapData* mapData) {
    for (int i = 0; i < mapData->nbNoeud; i++)
    {
        if(mapData->nodes[i].type == 3) {
            return mapData->nodes[i].id;
        }
    }
}