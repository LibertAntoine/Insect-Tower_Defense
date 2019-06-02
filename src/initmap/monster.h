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


/**
 * add the monster of the listMonster
 * param[in] monster to add
 */
int addToList(Monster* monster);


/**
 * Print the dataInfos of the monster
 * param[in] monster to print
 */
void monster_printInfos(Monster *monster);

/**
 * Create a new monster and add it to the list
 * param[in] the type of the new monster
 * param[in] the id of the entree for this monster
 */
int monster_popMonster(TypeMonster type, int idIn);

/**
 * Affect dommage of the monster
 * param[in] the projectile its affect dommages
 */
void monster_attack(Projectile* projectile);

/**
 * Delete monster of the listMonster
 * param[in] monster to delete
 */
void monster_removeFromList(Monster* monster);

/**
 * Change the status of the monster ALIVE->DEAD
 * param[in] monster to kill
 */
void monster_kill(Monster* monster);

/**
 * Move the monster on the map in fonction of its mass
 * param[in] monster to move
 */
int moveMonster(Monster* monster);

/**
 * Change the risk index of the path where is the monster
 * param[in] monster to delete
 */
void monster_delete(Monster* monster);

/**
 * Free the list of monsters
 * param[in] list to free
 */
void monster_freeListMonsters(ListMonsters* listMonsters);

/**
 * Free a monster
 * param[in] monster to free
 */
void monster_freeMonster(Monster* monster);

/**
 * Change the orientation of the monster in fonction of move
 * param[in] monster to change
 */
Orientation monster_moveDirection(Monster* monster);

/**
 * Check the list of monsters and move each of it.
 */
int monster_moveAll();
#endif //MONSTER_H_
