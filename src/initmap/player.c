#include "player.h"

void player_init()
{
  plateau->joueur.argent = 10000;
  plateau->joueur.action = ADD;
  plateau->joueur.type = LASER;
}

void player_afficherAction()
{
  Etat *joueur = &(plateau->joueur);
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
  Etat *joueur = &(plateau->joueur);
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
  Etat *joueur = &(plateau->joueur);

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
  Etat *joueur = &(plateau->joueur);
  joueur->argent += valeur;
}
