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
      distance = valueChemin(infosNodes->nodes[i], infosNodes->nodes[next_id]);

      if(next_id == -1) {
        break;
      }
      else if (distances[i] + distance < distances[next_id]) { 
        distances[next_id] = distances[i] + distance; 
        previous[next_id] = &infosNodes->nodes[i]; 
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
  fill(array, size, 0);

  return array;
}

int *itineraire_initDistanceArray(int size)
{
  int *array = malloc(sizeof(int) * size);
  int total_cases = plateau->Xsplit * plateau->Ysplit;
  fill(array, size, total_cases);

  return array;
}


void fill(int* array, int size, int value)
{
  for(int i = 0; i < size; i++) {
    array[i] = value;
  }
}

double valueChemin(Node node_in, Node node_out)
{
  float distance = 0;
  if (node_in.x == node_out.x) {
    distance = fabs(node_in.y - node_out.y);
  } else if (node_in.y == node_out.y) {
    distance = fabs(node_in.x - node_out.x);
  } 
  Chemin* chemin = case_giveChemin(&node_in, &node_out);
  return distance + chemin->dead_monsters;
}


int itineraire_initMonster(Monster* monster, InfosNodes* infosNodes)
{
  Itineraire* itineraire = malloc(sizeof(Itineraire));
  itineraire->next = NULL;
  itineraire->nbEtape = 1;
  addToItineraire(itineraire, &infosNodes->nodes[monster->idIn]);

  int idNode = monster->idIn;
  while(idNode != infosNodes->idOut) {  
    addToItineraire(itineraire, infosNodes->shortPaths[idNode]);
    itineraire->nbEtape++;  
    idNode = infosNodes->shortPaths[idNode]->id;
  }
  monster->itineraire = itineraire;
}

int addToItineraire(Itineraire* itineraire, Node* node) {
  Etape* etape = malloc(sizeof(Etape));
  etape->node = node;
  etape->next = NULL;
  if(itineraire->next == NULL) {
    itineraire->next = etape;
    return 0;
  }
  Etape* currentEtape = itineraire->next;
  while (currentEtape->next != NULL)
  {  
    currentEtape = currentEtape->next;
  }
  currentEtape->next = etape;
  return 0;
  etape->next = itineraire->next;
  itineraire->next = etape;     
  return 0;
}
