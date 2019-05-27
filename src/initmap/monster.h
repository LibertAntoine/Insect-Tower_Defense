#ifndef MONSTER_H_
#define MONSTER_H_

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL_mixer.h>

#include "structures.h"

#include "cases.h"
#include "tour.h"
#include "tour.h"
#include "projectile.h"
#include "itineraire.h"
#include "sprite.h"

ListMonsters* monster_initListMonster();
DataMonsters** monster_initDataMonster();

int addToList(Monster* monster);

void monster_printInfos(Monster *monster);

int monster_popMonster(InfosNodes* InfosNodes, TypeMonster type, int idIn);
void monster_attack(Projectile* projectile);
void monster_removeFromList(Monster* monster);
void monster_kill(Monster* monster);
int moveMonster(Monster* monster);
void monster_delete(Monster* monster);
Orientation monster_moveDirection(Monster* monster);

/**
 * @brief Parcours la liste de montre afin d'en demander le déplacement.
 */
int monster_moveAll();
#endif //MONSTER_H_
