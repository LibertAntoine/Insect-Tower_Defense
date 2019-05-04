#include "tour.h"

void tour_initConstructionData()
{
  plateau->constructionData[LASER].type = LASER;
  plateau->constructionData[LASER].degats = 1;
  plateau->constructionData[LASER].alimentation = 1;
  plateau->constructionData[LASER].cadence = 2;
  plateau->constructionData[LASER].portee = 2;
  plateau->constructionData[LASER].valeur_achat = 200;
  plateau->constructionData[LASER].valeur_revente = 100;

  plateau->constructionData[MISSILE].type = MISSILE;
  plateau->constructionData[MISSILE].degats = 2;
  plateau->constructionData[MISSILE].alimentation = 1;
  plateau->constructionData[MISSILE].cadence = 1;
  plateau->constructionData[MISSILE].portee = 1;
  plateau->constructionData[MISSILE].valeur_achat = 300;
  plateau->constructionData[MISSILE].valeur_revente = 150;

  plateau->constructionData[RADAR].type = RADAR;
  plateau->constructionData[RADAR].degats = 0;
  plateau->constructionData[RADAR].alimentation = 0;
  plateau->constructionData[RADAR].cadence = 0;
  plateau->constructionData[RADAR].portee = 1;
  plateau->constructionData[RADAR].range = 2;
  plateau->constructionData[RADAR].valeur_achat = 400;
  plateau->constructionData[RADAR].valeur_revente = 200;

  plateau->constructionData[ARMEMENT].type = ARMEMENT;
  plateau->constructionData[ARMEMENT].degats = 1;
  plateau->constructionData[ARMEMENT].alimentation = 0;
  plateau->constructionData[ARMEMENT].cadence = 0;
  plateau->constructionData[ARMEMENT].portee = 0;
  plateau->constructionData[ARMEMENT].range = 2;
  plateau->constructionData[ARMEMENT].valeur_achat = 400;
  plateau->constructionData[ARMEMENT].valeur_revente = 200;

  plateau->constructionData[CENTRALE].type = CENTRALE;
  plateau->constructionData[CENTRALE].degats = 0;
  plateau->constructionData[CENTRALE].alimentation = 1;
  plateau->constructionData[CENTRALE].cadence = 0;
  plateau->constructionData[CENTRALE].portee = 2;
  plateau->constructionData[CENTRALE].range = 2;
  plateau->constructionData[CENTRALE].valeur_achat = 400;
  plateau->constructionData[CENTRALE].valeur_revente = 200;

  plateau->constructionData[MUNITION].type = MUNITION;
  plateau->constructionData[MUNITION].degats = 0;
  plateau->constructionData[MUNITION].alimentation = 0;
  plateau->constructionData[MUNITION].cadence = 1;
  plateau->constructionData[MUNITION].portee = 0;
  plateau->constructionData[MUNITION].range = 2;
  plateau->constructionData[MUNITION].valeur_achat = 400;
  plateau->constructionData[MUNITION].valeur_revente = 200;
}

int tour_getDegats(TypeCase type)
{
  return plateau->constructionData[type].degats;
}
int tour_getAlimentation(TypeCase type)
{
  return plateau->constructionData[type].alimentation;
}
int tour_getCadence(TypeCase type)
{
  return plateau->constructionData[type].cadence;
}
int tour_getRange(TypeCase type)
{
  return plateau->constructionData[type].range;
}
int tour_getPortee(TypeCase type)
{
  return plateau->constructionData[type].portee;
}
int tour_getPrixAchat(TypeCase type)
{
  return plateau->constructionData[type].valeur_achat;
}
int tour_getPrixRevente(TypeCase type)
{
  return plateau->constructionData[type].valeur_revente;
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
  new->next = NULL;
  new->lastMonster = NULL;
  new->x = caseX + 0.5;
  new->y = caseY + 0.5;

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
int tour_countBatiments(TypeCase type, int index_case)
{
  int Xsplit = plateau->Xsplit;
  int Ysplit = plateau->Ysplit;
  int total_cases = Xsplit * Ysplit;
  int range = plateau->constructionData[type].range;

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
  printf("%p", plateau->tours[index_case]);
  updateAllTower();
}

int updateAllTower() {
    Tour* currentTour = plateau->listTours->next;
    int index_case = -1; 
    while (currentTour != NULL)
        { 
          index_case = case_getCaseIndex(currentTour->x - 1.5, currentTour->y - 1.5);
          tour_completeInfo(RADAR, index_case);
          tour_completeInfo(CENTRALE, index_case);
          tour_completeInfo(ARMEMENT, index_case);
          tour_completeInfo(MUNITION, index_case);
          currentTour = currentTour->next;
        }
    return 0;
}



int attackAllTower()
{
    Tour* currentTour = plateau->listTours->next;
    while (currentTour != NULL)
        {  
          attackTour(currentTour);
          currentTour = currentTour->next;
        }
    return 0;
}


int attackTour(Tour* tour) {
  if(tour->lastMonster != NULL) {
    refindMonster(tour);
  } else {
    findMonster(tour);
  }
  if (tour->munition != 0 && tour->armement != 0) {
    if(tour->rechargement < 0 && tour->lastMonster != NULL) {
      printf("lol");
      create_projectile(tour, tour->lastMonster);
      tour->rechargement = 2/tour->munition;
    } else {
      if (tour->rechargement >= 0) {
        tour->rechargement = tour->rechargement - 1.0/60.0;
      }
    }
  }

}
