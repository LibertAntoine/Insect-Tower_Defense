#ifndef DRAW_MONSTER_H_
#define DRAW_MONSTER_H_

#include <stdio.h>
#include <stdlib.h>
#include "cases.h"
#include "monster.h"

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

void display_drawSingleMonster(Monster* monster);
int display_drawMonsters(ListMonsters* listmonsters);

#endif //DRAW_MONSTER_H_