#include "short-path-algo.h"



int getShortPath(InfosNodes* infosNodes) {
    
    
    if (infosNodes->idOut > infosNodes->nbNoeud -1 || infosNodes->idOut <= 0) {
        return 0;
    }
    int* idVisited = malloc(sizeof(int)*infosNodes->nbNoeud);
    fill(idVisited, infosNodes->nbNoeud, 0);
    int* distances = malloc(sizeof(int)*infosNodes->nbNoeud);
    fill(distances, infosNodes->nbNoeud, plateau->Xsplit*plateau->Ysplit);
    distances[infosNodes->idOut] = 0;
    Node* previous = malloc(sizeof(Node)*infosNodes->nbNoeud);
    int i = infosNodes->idOut;
    int dis;
    while (i != -1) {
        idVisited[i] = 1;
        for(int j = 0; j < 4; j++)
        {   

            if(infosNodes->nodes[i].link[j] == -1) {break;}
            else if (distances[i] + distanceNodes(infosNodes->nodes[i], infosNodes->nodes[infosNodes->nodes[i].link[j]]) < distances[infosNodes->nodes[i].link[j]]) { 
                distances[infosNodes->nodes[i].link[j]] = distances[i] + distanceNodes(infosNodes->nodes[i], infosNodes->nodes[infosNodes->nodes[i].link[j]]);
                previous[infosNodes->nodes[i].link[j]] = infosNodes->nodes[i];
            }
        }
        i = -1;
        dis = plateau->Xsplit*plateau->Ysplit;
        for(int k = 0; k < infosNodes->nbNoeud; k++) {
            
            if(!idVisited[k] && dis >= distances[k]) { 
                dis = distances[k];     
                i = k;   
            }
        }
    }
    infosNodes->shortPaths = previous;
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

