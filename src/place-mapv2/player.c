#include "player.h"

void player_afficherAction(Etat *joueur)
{
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

void player_afficherEtat(Etat *joueur)
{
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

int player_acheteTour(Etat *joueur, TypeCase type)
{
  int prix = tour_getPrix(type);
  if (joueur->argent < prix) {
    return 0;
  }
  else {
    joueur->argent -= prix;
    return 1;
  }
}
