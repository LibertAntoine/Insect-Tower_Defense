#include <stdio.h>
#include <stdlib.h>
#include "monster.h"


int main(int argc, char const *argv[])
{
    Monster* monster = createMonster(10, 10);
    attackMonster(monster, 12);
    
    system("PAUSE");
    return 0;
}
