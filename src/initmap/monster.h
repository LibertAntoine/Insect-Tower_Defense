#ifndef MONSTER_H_
#define MONSTER_H_

#include <stdio.h>
#include <math.h>

#include "structures.h"

#include "cases.h"
#include "tour.h"
#include "projectile.h"
#include "itineraire.h"

int initListMonsters();
int addToList(Monster* monster);

int monster_popMonster(InfosNodes* InfosNodes, TypeMonster type, int idIn);
void monster_attack(Projectile* projectile);
void monster_removeFromList(Monster* monster);
void monster_kill(Monster* monster);
int moveMonster(Monster* monster);
Orientation monster_moveDirection(Monster* monster);

/**
 * @brief Parcours la liste de montre afin d'en demander le déplacement.
 */
int moveAllMonster();
#endif //MONSTER_H_
