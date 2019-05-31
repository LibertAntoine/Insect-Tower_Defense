#include "tour.h"

ListTours* tour_initListTours()
{
  ListTours* listTours = malloc(sizeof(ListTours));
  listTours->nbTours = 0;
  listTours->next = NULL;
  return listTours;
}

int tour_getDegats(TypeCase type)
{
  return mapData->constructionData[type].degats;
}
int tour_getAlimentation(TypeCase type)
{
  return mapData->constructionData[type].alimentation;
}
int tour_getCadence(TypeCase type)
{
  return mapData->constructionData[type].cadence;
}
int tour_getRange(TypeCase type)
{
  return mapData->constructionData[type].range;
}
int tour_getPortee(TypeCase type)
{
  return mapData->constructionData[type].portee;
}
int tour_getPrixAchat(TypeCase type)
{
  return mapData->constructionData[type].valeur_achat;
}
int tour_getPrixRevente(TypeCase type)
{
  return mapData->constructionData[type].valeur_revente;
}

Tour *tour_create(TypeCase type, int index_case)
{
  Tour *new = malloc(sizeof(Tour));
  if (!new) {
    // TODO: Throw allocation error
  }
  int caseX, caseY;
  case_getCasePosition(index_case, &caseX, &caseY);

  new->type = type;
  new->armement = 0;
  new->centrale = 0;
  new->radar = 0;
  new->munition = 0;
  new->rechargement = 0;
  new->angle = rand()%360;
  new->next = NULL;
  new->targetMonster = NULL;
  new->x = caseX + 0.5;
  new->y = caseY + 0.5;
  new->time_tir = SDL_GetTicks();

  if (type == LASER || type == MISSILE) {
    addToListTour(new);
    plateau->listTours->nbTours++;
  }

  return new;
}


int addToListTour(Tour* tour)
{
  if(plateau->listTours->next == NULL) {
    plateau->listTours->next = tour;
    return 0;
  }
  Tour* currentTour = plateau->listTours->next;
  while (currentTour->next != NULL)
  {  
    currentTour = currentTour->next;
  }
  currentTour->next = tour;
  return 0;
}

/**
 * Retourne le nombre de batiments d'un certain type autour d'une tour spécifique
 * */
// TODO: Passer sur des portées en ligne droite
int tour_countBatiments(TypeCase type, int index_case)
{
  int Xsplit = mapData->Xsplit;
  int Ysplit = mapData->Ysplit;
  int total_cases = Xsplit * Ysplit;
  int range = mapData->constructionData[type].range;

  int counter = 0;

  for (int i = index_case - range*Xsplit; i <= index_case + range*Xsplit; i+=Xsplit) {
    if (i < 0 || i >= total_cases) {
      continue;
    }
    for (int j = i-range; j <= i+range; j++) {
      if (i/Xsplit != j/Xsplit || j < 0 || j >= total_cases) {
        continue;
      }

      if (plateau->cases[j] == type) {
        counter++;
      }
    }
  }

  return counter;
}

void tour_completeInfo(TypeCase type, int index_case)
{
  int counter_batiment = tour_countBatiments(type, index_case);
  Tour *tour = plateau->tours[index_case];
  
  switch (type) {
    case ARMEMENT:
      tour->armement = counter_batiment;
      break;
    case CENTRALE:
      tour->centrale = counter_batiment;
      break;
    case MUNITION:
      tour->munition = counter_batiment;
      break;
    case RADAR:
      tour->radar = counter_batiment;
      break;
  }
}

void tour_add(TypeCase type, int index_case)
{
  plateau->tours[index_case] = tour_create(type, index_case);

  Mix_PlayChannel(-1, sound[TOWER], 0);
  printf("%p", plateau->tours[index_case]);
  updateAllTower();
}

void tour_remove(Tour* tour)
{
  Tour* tour_list = plateau->listTours->next;
  if (tour_list == tour) {
    plateau->listTours->next = tour_list->next;
  }
  else {
    while (tour_list->next != tour){
      tour_list = tour_list->next;
    }
    tour_list->next = tour_list->next->next;
  }
  free(tour);
}

int updateAllTower() {
  Tour* currentTour = plateau->listTours->next;
  int index_case = -1; 
  while (currentTour != NULL) { 
    index_case = case_getCaseIndex(currentTour->x - 0.5, currentTour->y - 0.5);
    tour_completeInfo(RADAR, index_case);
    tour_completeInfo(CENTRALE, index_case);
    tour_completeInfo(ARMEMENT, index_case);
    tour_completeInfo(MUNITION, index_case);
    currentTour = currentTour->next;
  }
  return 0;
}

int tour_attackAll()
{
  Tour* currentTour = plateau->listTours->next;
  while (currentTour != NULL) {  
    tour_attaqueMonster(currentTour);
    currentTour = currentTour->next;
  }
  return 0;
}

float tour_calculDegats(Tour* tour)
{
  float degats_normaux = tour_getDegats(tour->type);
  int armements = tour->armement;
  float degats = degats_normaux + armements*(degats_normaux/4);

  return degats;
}

void tour_tire(Tour* tour)
{
  float degats = tour_calculDegats(tour);
  create_projectile(tour, tour->targetMonster, degats);

  tour->rechargement = tour_getCadence(tour->type);
  tour->time_tir = SDL_GetTicks();
}

float tour_calculCadence(Tour* tour)
{
  int entrepots = tour->munition;
  float cadence_normale = 1000.0 / tour_getCadence(tour->type);
  float cadence = cadence_normale + entrepots*(cadence_normale / 4);
  return 60000 / cadence;
}

Bool tour_checkAlimentation(Tour* tour)
{
  if (tour->centrale > 0) {
    return TRUE;
  }
  else return FALSE;
}

Bool tour_isLoaded(Tour* tour)
{
  Uint32 now = SDL_GetTicks();
  float cadence = tour_calculCadence(tour);
  if (now - tour->time_tir >= cadence) {
    return TRUE;
  }
  else return FALSE;
}

void tour_attaqueMonster(Tour* tour)
{
  tour_updateShootingAngle(tour);
  if (tour_checkAlimentation(tour) == TRUE) {
    if (tour_isLoaded(tour) == TRUE) {
      if (tour_lockTarget(tour) == TRUE) {
        tour_tire(tour);
      }
    }
  }
}

Bool tour_lockTarget(Tour* tour)
{
  if (tour_targetStillInRange(tour) == FALSE) {
    if(tour_findTarget(tour) == TRUE) return TRUE;
    else return FALSE;
  }
  else {
    return TRUE;
  }
}

float tour_calculPortee(Tour* tour)
{
  float normal_range = tour_getPortee(tour->type);
  int radars = tour->radar;
  float portee = normal_range + radars * (normal_range/4); // ajout de 25% de la portee normale par radar
  return portee;
}

Bool tour_findTarget(Tour* tour)
{
  tour->targetMonster = NULL;

  if(plateau->listMonsters->firstMonster == NULL) {
    return FALSE;
  }

  Monster* currentMonster = plateau->listMonsters->firstMonster;
  float current_monster_distance = 0;
  float portee = tour_calculPortee(tour);
  float shortest_monster_distance = pow(mapData->Xsplit, 2) + pow(mapData->Ysplit, 2);
  while (currentMonster != NULL)
  {  
    if(currentMonster->status == ALIVE) {
      current_monster_distance = pow(tour->x - currentMonster->x, 2) + pow(tour->y - currentMonster->y, 2);

      if (current_monster_distance <= portee) {
        if(current_monster_distance < shortest_monster_distance) {
          shortest_monster_distance = current_monster_distance;
          tour->targetMonster = currentMonster;
        }
      }
    }  
    currentMonster = currentMonster->next;
  }
  if (tour->targetMonster != NULL) return TRUE;
  else return FALSE;
}

Bool tour_targetStillInRange(Tour* tour)
{
  if (tour->targetMonster != NULL) {
    double distance = pow(abs(tour->x - tour->targetMonster->x), 2) + pow(abs(tour->y - tour->targetMonster->y), 2);
    double portee = tour_calculPortee(tour);

    if(tour->targetMonster->status == DEAD || distance > portee) {
      tour->targetMonster = NULL;
      return FALSE;
    }
    else return TRUE;
  }
  else return FALSE;
}

void tour_updateShootingAngle(Tour* tour)
{
  if (tour->targetMonster) {
    double hypo = sqrt(pow(tour->x - tour->targetMonster->x, 2) + pow(tour->y - tour->targetMonster->y, 2));
    double distance = tour->x - tour->targetMonster->x;
    double angle = acos(distance/hypo)* 180.0 / M_PI;
    tour->angle = angle;
  }
}

void tour_freeListTours(ListTours* listTours) {
  Tour* tourFree;
  Tour* currentTour = NULL;
  if(listTours->next != NULL) {
    tourFree = listTours->next;
    currentTour = listTours->next->next;
    free(tourFree);
  }
  while(currentTour != NULL) {
    tourFree = currentTour;
    currentTour = currentTour->next;
    free(tourFree);
  }
  free(listTours);
}
