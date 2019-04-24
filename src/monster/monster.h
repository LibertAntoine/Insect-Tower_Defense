#ifndef MONSTERS_H_
#define MONSTERS_H_

#include <stdio.h>

typedef struct Monster {
   int PDV;
   int strength; 
} Monster;

Monster* createMonster(int PDV, int strength);
void attackMonster(Monster* monster, int domage);
void killMonster(Monster* monster);
#endif //MONSTER_H_