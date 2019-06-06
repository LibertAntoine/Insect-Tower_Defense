#ifndef PLAYER_H_
#define PLAYER_H_

#ifdef _WIN32
    #include <GL/glew.h>
    #define _USE_MATH_DEFINES
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif
#include <stdio.h>
#include <string.h>

#include "structures.h"
#include "tour.h"
#include "gui.h"
#include "cases.h"

// Functions
void player_checkTarifs();
Etat* player_init(int argent);
void player_afficherAction();
void player_afficherEtat();
int player_acheteConstruction(int caseX, int caseY);
void player_gagneArgent(int valeur);

void player_switchTowerType(TypeCase type);
void player_switchAction(Action action);
#endif //PLAYER_H_
