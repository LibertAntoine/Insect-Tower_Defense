#ifndef MONSTER_H_
#define MONSTER_H_

#include <stdio.h>


typedef struct Monster {
   int PDV;
   int strength;
   int speed;
} Monster;

Monster* createMonster(int PDV, int strength, int speed);
void attackMonster(Monster* monster, int domage);
void killMonster(Monster* monster);
#endif //MONSTER_H_