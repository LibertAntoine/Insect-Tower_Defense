#include "player.h"

Etat* player_init(int argent)
{
  Etat *joueur = malloc(sizeof(Etat));

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
    return 1;
  }
}

void player_gagneArgent(int valeur)
{
  Etat *joueur = plateau->joueur;
  joueur->argent += valeur;
}

void player_switchAction(Action action)
{
  Etat *joueur = plateau->joueur;
  printf("Changing action ");
  player_afficherAction();
  gui_changeActionButtonState(joueur->action, INACTIVE);
  printf(" --> ");
  joueur->action = action;
  gui_changeActionButtonState(joueur->action, ACTIVE);
  player_afficherAction();
  printf("\n");
}

void player_switchTowerType(TypeCase type)
{
  Etat *joueur = plateau->joueur;
  printf("Changing tower type ");
  player_afficherEtat();
  gui_changeTowerButtonState(joueur->type, INACTIVE);
  printf(" --> ");
  joueur->type = type;
  gui_changeTowerButtonState(joueur->type, ACTIVE);
  player_afficherEtat();
  printf("\n");
}
