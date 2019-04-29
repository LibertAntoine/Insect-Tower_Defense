#ifndef WAVES_H_
#define WAVES_H_


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "monster.h"
#include "itd-file.h"

int deleteInArray(int* t, int monster, int nbMonster);
int moveWave(ListMonsters* listMonsters, MapData* mapdata, Wave* currentWave);
int launchWaves(ListMonsters* listMonsters, MapData* mapdata, Wave* currentWave, float timer);

#endif