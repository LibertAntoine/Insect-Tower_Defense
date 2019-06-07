#include "player.h"

Etat* player_init(int argent)
{
  Etat *joueur = malloc(sizeof(Etat));
  if (!joueur) {
    printf("ERROR ALLOC : joueur");
    exit(CHK_ERROR_ALLOC);
  }

  joueur->argent = argent;
  joueur->action = ADD;
  joueur->type = LASER;

  return joueur;
}

void player_afficherAction()
{
  Etat *joueur = plateau->joueur;
  char mode[20];
  switch(joueur->action) {
    case ADD:
      strcpy(mode, "add");
      break;
    case GETINFO:
      strcpy(mode, "getinfo");
      break;
    case REMOVE:
      strcpy(mode, "remove");
      break;
  }
  printf("%s", mode);
}

void player_afficherEtat()
{
  Etat *joueur = plateau->joueur;
  char mode[20];
  switch(joueur->type) {
    case RADAR:
      strcpy(mode,"radar");
      break;
    case ARMEMENT:
      strcpy(mode,"armement");
      break;
    case CENTRALE:
      strcpy(mode,"centrale");
      break;
    case MUNITION:
      strcpy(mode,"munition");
      break;

    case LASER:
      strcpy(mode,"laser");
      break;
    case MISSILE:
      strcpy(mode,"missile");
      break;
  }
  printf("%s", mode);
}

int player_acheteConstruction(int caseX, int caseY)
{
  Etat *joueur = plateau->joueur;

  int prix = tour_getPrixAchat(joueur->type);
  if (joueur->argent < prix) {
    return 0;
  }
  else {
    joueur->argent -= prix;
    case_addConstruction(caseX, caseY);
    player_checkTarifs();
    return 1;
  }
}

void player_checkTarifs()
{
  if (plateau->idListMoney != GL_INVALID_VALUE) {
    glDeleteLists(plateau->idListMoney, 1);
  }
  plateau->idListMoney = GL_INVALID_VALUE;
  for (TypeCase i = LASER; i <= MUNITION; i++) {
    if (mapData->constructionData[i].valeur_achat > plateau->joueur->argent) {
      if (gui_getTowerButtonState(i) == CLICKED) {
        gui_changeTowerButtonState(i+1, CLICKED);
      }
      gui_changeTowerButtonState(i, DISABLED);
    }
    else {
      if (plateau->joueur->type == i) {
        gui_changeTowerButtonState(i, CLICKED);
      }
      else {
        gui_changeTowerButtonState(i, ACTIVE);
      }
    }
  }
}

void player_gagneArgent(int valeur)
{
  Etat *joueur = plateau->joueur;
  joueur->argent += valeur;
  player_checkTarifs();
}

void player_switchAction(Action action)
{
  Mix_PlayChannel(-1, gameData->sound[HITWOOD], 0);
  Etat *joueur = plateau->joueur;
  printf("Changing action ");
  player_afficherAction();
  gui_changeActionButtonState(joueur->action, ACTIVE);
  printf(" --> ");
  joueur->action = action;
  gui_changeActionButtonState(joueur->action, CLICKED);
  player_afficherAction();
  printf("\n");
}

void player_switchTowerType(TypeCase type)
{
  Mix_PlayChannel(-1, gameData->sound[HITWOOD], 0);
  Etat *joueur = plateau->joueur;
  printf("Changing tower type ");
  player_afficherEtat();
  gui_changeTowerButtonState(joueur->type, ACTIVE);
  printf(" --> ");
  joueur->type = type;
  gui_changeTowerButtonState(joueur->type, CLICKED);
  player_afficherEtat();
  printf("\n");
}
