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
int wave_reduceWaveMonsterArray(int monster_id);
int moveWave();
void wave_freeListWaves();


#endif
