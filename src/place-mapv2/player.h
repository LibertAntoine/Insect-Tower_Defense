#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdio.h>
#include <string.h>

#include "tour.h"
#include "cases.h"

enum Action {
  ADD,
  GETINFO,
  REMOVE
};

typedef struct Etat {
  enum TypeCase type;
  enum Action action;
  int argent;
} Etat;



// Functions
void player_afficherAction(Etat *joueur);

void player_afficherEtat(Etat *joueur);

int player_acheteTour(Etat *joueur, TypeCase type);

#endif //PLAYER_H_
