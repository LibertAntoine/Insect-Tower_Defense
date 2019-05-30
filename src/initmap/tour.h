#ifndef TOUR_H_
#define TOUR_H_
#pragma once

#include <SDL2/SDL_mixer.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "structures.h"

#include "cases.h"
#include "projectile.h"

// Functions
void tour_updateShootingAngle(Tour* tour);
ListTours* tour_initListTours();
void tour_initConstructionData();
int tour_getDegats(TypeCase type);
int tour_getAlimentation(TypeCase type);
int tour_getCadence(TypeCase type);
int tour_getRange(TypeCase type);
int tour_getPortee(TypeCase type);
int tour_getPrixAchat(TypeCase type);
int tour_getPrixRevente(TypeCase type);
Tour *tour_create(TypeCase type, int index_case);
int tour_countBatiments(TypeCase type, int index_case);
void tour_completeInfo(TypeCase type, int index_case);
void tour_add(TypeCase type, int index_case);
int addToListTour(Tour* tour);
int updateAllTower();
int tour_attackAll();

void tour_tire(Tour* tour);
void tour_recharge(Tour* tour);
Bool tour_checkAlimentation(Tour* tour);
void tour_attaqueMonster(Tour* tour);
Bool tour_lockTarget(Tour* tour);
Bool tour_findTarget(Tour* tour);
Bool tour_isLoaded(Tour* tour);
Bool tour_targetStillInRange(Tour* tour);

float tour_calculCadence(Tour* tour);
float tour_calculDegats(Tour* tour);
float tour_calculPortee(Tour* tour);
void tour_remove(Tour* tour);
void tour_freeListTours(ListTours* listTours);

#endif //TOUR_H_
