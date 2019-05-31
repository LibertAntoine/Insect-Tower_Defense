#include "itineraire.h"

int itineraire_findShortestPath()
{
  if (mapData->infosNodes->idOut > mapData->infosNodes->nbNoeud -1 || mapData->infosNodes->idOut < 0) {
    return 0;
  }

  int *idVisited = itineraire_initVisitedArray(mapData->infosNodes->nbNoeud);
  int *distances = itineraire_initDistanceArray(mapData->infosNodes->nbNoeud);

  distances[mapData->infosNodes->idOut] = 0;

  Node** previous = malloc(sizeof(Node*) * mapData->infosNodes->nbNoeud);
  // TODO: Vérifier l'allocation dynamique

  int i = mapData->infosNodes->idOut;
  int distance;
  while (i != -1) {
    idVisited[i] = 1;

    for(int link_id = 0; link_id < 4; link_id++) {   
      //printf("%d ", distanceNodes(infosNodes->nodes[i], infosNodes->nodes[infosNodes->nodes[i].link[j]]));
      int next_id = mapData->infosNodes->nodes[i].link[link_id];

      if(next_id == -1) {
        break;
      }
      else {
        distance = (int) itineraire_getValueChemin(mapData->infosNodes->nodes[i], mapData->infosNodes->nodes[next_id]);
        if (distances[i] + distance < distances[next_id]) { 
          distances[next_id] = distances[i] + distance; 
          previous[next_id] = &mapData->infosNodes->nodes[i]; 
        }
      }
    }

    i = -1;
    int distance_max = mapData->Xsplit * mapData->Ysplit;
    for(int k = 0; k < mapData->infosNodes->nbNoeud; k++) {
      if(!idVisited[k] && distance_max >= distances[k]) { 
        distance_max = distances[k];     
        i = k;   
      }
    }
  }
  mapData->infosNodes->shortPaths = previous;
}

int *itineraire_initVisitedArray(int size)
{
  int *array = malloc(sizeof(int) * size);
  itineraire_fillArray(array, size, 0);

  return array;
}

int *itineraire_initDistanceArray(int size)
{
  int *array = malloc(sizeof(int) * size);
  int total_cases = mapData->Xsplit * mapData->Ysplit;
  itineraire_fillArray(array, size, total_cases);

  return array;
}


void itineraire_fillArray(int* array, int size, int value)
{
  for(int i = 0; i < size; i++) {
    array[i] = value;
  }
}

double itineraire_getValueChemin(Node node_in, Node node_out)
{
  float distance = 0;
  if (node_in.x == node_out.x) {
    distance = fabs(node_in.y - node_out.y);
  } else if (node_in.y == node_out.y) {
    distance = fabs(node_in.x - node_out.x);
  } 
  Chemin* chemin = itineraire_getChemin(&node_in, &node_out);
  return distance + chemin->dead_monsters;
}

void itineraire_freeItiniraire(Itineraire* itineraire) {
  Etape* etapeFree;
  Etape* currentEtape = NULL;
  if(itineraire->next != NULL) {
    etapeFree = itineraire->next;
    currentEtape = itineraire->next->next;
    free(etapeFree);
  }
  while(currentEtape != NULL) {
    etapeFree = currentEtape;
    currentEtape = currentEtape->next;
    free(etapeFree);
  }
  free(itineraire);
}


int itineraire_initMonster(Monster* monster)
{
  itineraire_findShortestPath();
  Itineraire* itineraire = malloc(sizeof(Itineraire));
  itineraire->next = NULL;
  itineraire->nbEtape = 1;
  itineraire_addEtape(itineraire, &mapData->infosNodes->nodes[monster->idIn]);

  int idNode = monster->idIn;
  while(idNode != mapData->infosNodes->idOut) {  
    itineraire_addEtape(itineraire, mapData->infosNodes->shortPaths[idNode]);
    itineraire->nbEtape++;  
    idNode = mapData->infosNodes->shortPaths[idNode]->id;
  }
  monster->itineraire = itineraire;
}

// TODO: checker l'ambiguité des return
void itineraire_addEtape(Itineraire* itineraire, Node* node) {
  Etape* etape = malloc(sizeof(Etape));
  etape->node = node;
  etape->next = NULL;
  if(itineraire->next == NULL) {
    itineraire->next = etape;
    return 0;
  }
  Etape* currentEtape = itineraire->next;
  while (currentEtape->next != NULL) {  
    currentEtape = currentEtape->next;
  }
  currentEtape->next = etape;
  return 0;
  etape->next = itineraire->next;
  itineraire->next = etape;     
  return 0;
}

ListChemins* itineraire_initListChemins()
{
  ListChemins* listChemins = malloc(sizeof(listChemins));
  listChemins->nbChemin = 0;
  listChemins->next = NULL;
  for(int i = 0; i < mapData->infosNodes->nbNoeud; i++) {
    Node* node = &mapData->infosNodes->nodes[i];
    for(int j = 0; node->link[j] != -1 && j < 5; j++) {
      itineraire_checkExistChemin(listChemins, node, &mapData->infosNodes->nodes[node->link[j]]);
    }
  }
  return listChemins;
}

void itineraire_checkExistChemin(ListChemins* listChemins, Node* node_in, Node* node_out)
{
  if(listChemins->nbChemin == 0) {
    itineraire_addChemin(listChemins, node_in, node_out);
  } else {
    Chemin* currentChemin = listChemins->next;
    char exist = 0;
    while(currentChemin != NULL) {
      if(currentChemin->node_in->id == node_out->id && currentChemin->node_out->id == node_in->id) {
        exist = 1;
        break;
      } else if (currentChemin->node_in->id == node_in->id && currentChemin->node_out->id == node_out->id) {
        exist = 1;
        break;
      }
      currentChemin = currentChemin->next;
    }
    if(!exist) {
      itineraire_addChemin(listChemins, node_in, node_out);
    }
  }
}

void itineraire_addChemin(ListChemins* listChemins, Node* node_in, Node* node_out)
{
  itineraire_checkValidChemin(node_in, node_out);
  Chemin* new_chemin = malloc(sizeof(Chemin));
  new_chemin->node_in = node_in;
  new_chemin->node_out = node_out;
  new_chemin->dead_monsters = 0;
  new_chemin->next = NULL;
  if(listChemins->next == NULL) {
    listChemins->nbChemin++;
    listChemins->next = new_chemin;
  }
  else {
    Chemin* currentChemin = listChemins->next; 
    while(currentChemin->next != NULL) {
      currentChemin = currentChemin->next;
    }
    listChemins->nbChemin++;
    currentChemin->next = new_chemin;
  }
}

void itineraire_addValueChemin(Monster* monster) {
    Chemin* chemin = itineraire_getChemin(monster->itineraire->next->next->node, monster->itineraire->next->node);
    chemin->dead_monsters++;
}

void itineraire_removeValueChemin(Monster* monster) {
    Chemin* chemin = itineraire_getChemin(monster->itineraire->next->next->node, monster->itineraire->next->node);
    chemin->dead_monsters--;
}

Chemin* itineraire_getChemin(Node* node_in, Node* node_out) {
    Chemin* currentChemin = plateau->listChemins->next;
    char exist = 0;

    while(currentChemin != NULL) {
      if(currentChemin->node_in->id == node_in->id && currentChemin->node_out->id == node_out->id) {
        return currentChemin;
      } else if (currentChemin->node_in->id == node_out->id && currentChemin->node_out->id == node_in->id) {
        return currentChemin;
      }
      else currentChemin = currentChemin->next;
    }
}

void itineraire_freeListChemins() {
  Chemin* cheminFree;
  Chemin* currentChemin = NULL;
  if(plateau->listChemins->next != NULL) {
    cheminFree = plateau->listChemins->next;
    currentChemin = plateau->listChemins->next->next;
    free(cheminFree);
  }
  while(currentChemin != NULL) {
    cheminFree = currentChemin;
    currentChemin = currentChemin->next;
    free(cheminFree);
  }
}

int itineraire_checkValidChemin(Node* node_in, Node* node_out) {
  int x1 = floor(node_in->x);
  int y1 = floor(node_in->y);

  int x2 = floor(node_out->x);
  int y2 = floor(node_out->y);

  while(x1 != x2 || y1 != y2) {
    if(x1 - x2 < 0) {
      x1++;
    } else if (x1 - x2 > 0) {
      x1--;
    }

    if(y1 - y2 < 0) {
      y1++;
    } else if (y1 - y2 > 0) {
      y1--;
    }
    if(x1 != x2 || y1 != y2) {
      int cas = case_getCaseIndex(x1, y1);
      if(mapData->cases[cas] != CHEMIN) {
        return 1;
      }
    }
  }
  return 0;
}