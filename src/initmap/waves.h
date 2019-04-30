#ifndef WAVES_H_
#define WAVES_H_
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "monster.h"
#include "itd-file.h"

int deleteInArray(int* t, int monster, int nbMonster);
int moveWave(MapData* mapdata, Wave* currentWave);
int launchWaves(MapData* mapdata, float timer);

#endif