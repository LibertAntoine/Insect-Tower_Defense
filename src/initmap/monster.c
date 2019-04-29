#include "monster.h"


ListMonsters* initListMonsters()
{
    ListMonsters* listMonsters = malloc(sizeof(ListMonsters));
    DataMonsters* dataMonsters = malloc(sizeof(DataMonsters));
    listMonsters->nbMonsters = 0;
    listMonsters->firstMonster = NULL;

    dataMonsters->PDV = malloc(sizeof(int)*4);
    dataMonsters->strength = malloc(sizeof(int)*4);
    dataMonsters->mass = malloc(sizeof(double)*4);

    dataMonsters->PDV[SOLDER] = 1;
    dataMonsters->strength[SOLDER] = 1;
    dataMonsters->mass[SOLDER] = 1.0;

    dataMonsters->PDV[HUGE_SOLDER] = 2;
    dataMonsters->strength[HUGE_SOLDER] = 2;
    dataMonsters->mass[HUGE_SOLDER] = 2.0;

    dataMonsters->PDV[GERERAL] = 1;
    dataMonsters->strength[GERERAL] = 1;
    dataMonsters->mass[GERERAL] = 1.0;

    dataMonsters->PDV[BOSS] = 1;
    dataMonsters->strength[BOSS] = 1;
    dataMonsters->mass[BOSS] = 1.0;
    
    listMonsters->dataMonsters = dataMonsters;
    
    return listMonsters;
}

int addToList(ListMonsters* listmonsters, Monster* monster) {
    
    if(listmonsters->firstMonster == NULL) {
        listmonsters->firstMonster = monster;
        return 0;
    }
    Monster* currentMonster = listmonsters->firstMonster;
    while (currentMonster->next != NULL)
        {  
            currentMonster = currentMonster->next;
        }
    currentMonster->next = monster;
    return 0;
}


int createMonster(ListMonsters* listmonsters, InfosNodes* InfosNodes, int type, int idIn) 
{
    
    Monster* monster = malloc(sizeof(Monster)); 
    monster->PDV = listmonsters->dataMonsters->PDV[type];
    monster->strength = listmonsters->dataMonsters->strength[type];
    monster->mass = listmonsters->dataMonsters->mass[type];
    monster->next = NULL;
    monster->idIn = idIn;
    monster->type = type;
    monster->orientation = HAUT;
    monster->x = InfosNodes->nodes[idIn].x;
    monster->y = InfosNodes->nodes[idIn].y;
    initItineraire(monster, InfosNodes);
    addToList(listmonsters, monster);
    listmonsters->nbMonsters++;
    return 0;
}

void attackMonster(Monster* monster, int damage) 
{
    monster->PDV = monster->PDV - damage;
    if(monster->PDV <= 0) {
        killMonster(monster);
    }
}

void killMonster(Monster* monster) 
{
    free(monster);
}

void get_itineraire(Monster* monster) 
{
    free(monster);
}

int moveMonster(Monster* monster) {
    if (monster->itineraire->next == NULL) {
        return 0;
    }
    
    if(monster->itineraire->next->node->x - monster->x > 0.01 || monster->itineraire->next->node->x-monster->x < -0.01) {
        if(monster->itineraire->next->node->x - monster->x < 0) {
            monster->x = monster->x - 0.01/monster->mass;
            monster->orientation = DROITE;
        } else {
            monster->x = monster->x + 0.01/monster->mass;
        }   monster->orientation = GAUCHE;
    } else if (monster->itineraire->next->node->y - monster->y > 0.01 || monster->itineraire->next->node->y - monster->y < -0.01) {
        if(monster->itineraire->next->node->y - monster->y < 0) {
            monster->y = monster->y - 0.01/monster->mass;
            monster->orientation = HAUT;
        } else {
            monster->y = monster->y + 0.01/monster->mass;
            monster->orientation = BAS;
        }
    } else {
        Etape* etape = monster->itineraire->next;
        monster->itineraire->next = monster->itineraire->next->next;
        free(etape);
        moveMonster(monster);   
    }
    return 0;
}

int moveAllMonster(ListMonsters* listmonsters) {
    
    if(listmonsters->firstMonster == NULL) {
        return 0;
    }
    Monster* currentMonster = listmonsters->firstMonster;
    while (currentMonster != NULL)
    {  
        moveMonster(currentMonster);
        currentMonster = currentMonster->next;
        
    }
    return 0;
}