#include "monster.h"


Monster* createMonster(int PDV, int strength, int speed) 
{
    Monster* monster = (Monster*) malloc(sizeof(Monster)); 
    monster->PDV = PDV;
    monster->strength = strength;
    monster->speed = speed;
    return monster;
}

void attackMonster(Monster* monster, int domage) 
{
    monster->PDV = monster->PDV - domage;
    if(monster->PDV <= 0) {
        killMonster(monster);
    }
}

void killMonster(Monster* monster) 
{
    free(monster);
}
