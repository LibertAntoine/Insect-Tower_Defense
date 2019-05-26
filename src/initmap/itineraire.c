#include "itineraire.h"

// TODO: Décrire le fonctionnement. Docummentation Doxygen, essayer de simplifier la lecture de la fonction.
int itineraire_findShortestPath(InfosNodes* infosNodes)
{
  if (infosNodes->idOut > infosNodes->nbNoeud -1 || infosNodes->idOut < 0) {
    return 0;
  }

  int *idVisited = itineraire_initVisitedArray(infosNodes->nbNoeud);
  int *distances = itineraire_initDistanceArray(infosNodes->nbNoeud);

  distances[infosNodes->idOut] = 0;

  Node** previous = malloc(sizeof(Node*) * infosNodes->nbNoeud);
  // TODO: Vérifier l'allocation dynamique

  int i = infosNodes->idOut;
  int distance;
  while (i != -1) {
    idVisited[i] = 1;

    for(int link_id = 0; link_id < 4; link_id++) {   
      //printf("%d ", distanceNodes(infosNodes->nodes[i], infosNodes->nodes[infosNodes->nodes[i].link[j]]));
      int next_id = infosNodes->nodes[i].link[link_id];

      if(next_id == -1) {
        break;
      }
      else {
        distance = (int) itineraire_getValueChemin(infosNodes->nodes[i], infosNodes->nodes[next_id]);
        if (distances[i] + distance < distances[next_id]) { 
          distances[next_id] = distances[i] + distance; 
          previous[next_id] = &infosNodes->nodes[i]; 
        }
      }
    }

    i = -1;
    int distance_max = plateau->Xsplit * plateau->Ysplit;
    for(int k = 0; k < infosNodes->nbNoeud; k++) {
      if(!idVisited[k] && distance_max >= distances[k]) { 
        distance_max = distances[k];     
        i = k;   
      }
    }
  }
  infosNodes->shortPaths = previous;
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
  int total_cases = plateau->Xsplit * plateau->Ysplit;
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


int itineraire_initMonster(Monster* monster, InfosNodes* infosNodes)
{
  Itineraire* itineraire = malloc(sizeof(Itineraire));
  itineraire->next = NULL;
  itineraire->nbEtape = 1;
  itineraire_addEtape(itineraire, &infosNodes->nodes[monster->idIn]);

  int idNode = monster->idIn;
  while(idNode != infosNodes->idOut) {  
    itineraire_addEtape(itineraire, infosNodes->shortPaths[idNode]);
    itineraire->nbEtape++;  
    idNode = infosNodes->shortPaths[idNode]->id;
  }
  monster->itineraire = itineraire;
}

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

void itineraire_checkChemin(MapData* mapData)
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
  plateau->listChemins = listChemins;
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
