#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdio.h>
#include <string.h>

#include "tour.h"
#include "cases.h"




// Functions
void player_init();
void player_afficherAction();
void player_afficherEtat();
int player_acheteConstruction(int caseX, int caseY);

#endif //PLAYER_H_
