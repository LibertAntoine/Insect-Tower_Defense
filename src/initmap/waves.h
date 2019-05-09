#ifndef WAVES_H_
#define WAVES_H_
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "monster.h"
#include "itd-file.h"


/**
 * @brief Décale le tableau à partir du monstre extrait de la liste d'attente d'une vague. Permet de garder tous les éléments disponible à gauche.
 * @param[out] TypeMonster* t réadapté.
 */
int wave_reduceWaveMonsterArray(TypeMonster* t, int monster_id, int monster_total);
int moveWave(MapData* mapdata, Wave* currentWave);
int launchWaves(MapData* mapdata, float timer);

#endif
