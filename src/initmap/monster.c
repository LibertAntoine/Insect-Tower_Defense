#include "monster.h"


int initListMonsters()
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
    
    plateau->listMonsters = listMonsters;
}

int addToList(Monster* monster) {
    
    if(plateau->listMonsters->firstMonster == NULL) {
        plateau->listMonsters->firstMonster = monster;
        return 0;
    }
    Monster* currentMonster = plateau->listMonsters->firstMonster;
    while (currentMonster->next != NULL)
        {  
            currentMonster = currentMonster->next;
        }
    currentMonster->next = monster;
    return 0;
}


int createMonster(InfosNodes* InfosNodes, int type, int idIn) 
{
    
    Monster* monster = malloc(sizeof(Monster)); 
    monster->PDV = plateau->listMonsters->dataMonsters->PDV[type];
    monster->strength = plateau->listMonsters->dataMonsters->strength[type];
    monster->mass = plateau->listMonsters->dataMonsters->mass[type];
    monster->next = NULL;
    monster->idIn = idIn;
    monster->type = type;
    monster->status = ALIVE;
    monster->orientation = HAUT;
    monster->x = InfosNodes->nodes[idIn].x;
    monster->y = InfosNodes->nodes[idIn].y;
    initItineraire(monster, InfosNodes);
    addToList(monster);
    plateau->listMonsters->nbMonsters++;
    return 0;
}

void attackMonster(Projectile* projectile) 
{
    projectile->cible->PDV = projectile->cible->PDV - projectile->damage;
    if(projectile->cible->PDV <= 0) {
        killMonster(projectile->cible);
    }
}

void killMonster(Monster* monster) 
{
    monster->status = DEAD;
    deleteToList(monster);
}

int deleteToList(Monster* monster) {
    printf("kill");
    if(plateau->listMonsters->firstMonster == monster) {
        plateau->listMonsters->firstMonster = plateau->listMonsters->firstMonster->next;
    } else { 
        Monster* currentMonster = plateau->listMonsters->firstMonster;
        while (currentMonster->next != monster)
        {  
            currentMonster = currentMonster->next; 
        }
        currentMonster->next = currentMonster->next->next;
    }
    return 0;
}



void get_itineraire(Monster* monster) 
{
    free(monster);
}

int moveMonster(Monster* monster) {
    if (monster->itineraire->next == NULL) {
        return 0;
    }
    
    if(monster->itineraire->next->node->x - monster->x > 0.01 || monster->itineraire->next->node->x - monster->x < -0.01) {
        if(monster->itineraire->next->node->x - monster->x < 0) {
            monster->x = monster->x - 0.01/monster->mass;
            monster->orientation = GAUCHE;
        } else {
            monster->x = monster->x + 0.01/monster->mass;
            monster->orientation = DROITE;
        }   
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

int moveAllMonster() {
    
    if(plateau->listMonsters->firstMonster == NULL) {
        return 0;
    }
    Monster* currentMonster = plateau->listMonsters->firstMonster;
    while (currentMonster != NULL)
    {  
        moveMonster(currentMonster);
        currentMonster = currentMonster->next;
        
    }
    return 0;
}

int findMonster(Tour* tour) {
    
    if(plateau->listMonsters->firstMonster == NULL) {
        tour->lastMonster = NULL;
        return 0;
    }
    
    Monster* currentMonster = plateau->listMonsters->firstMonster;
    double distance = 0;
    double distanceMin = plateau->Xsplit*plateau->Ysplit;
    while (currentMonster != NULL)
    {  
        distance = sqrt(pow(abs(tour->x - currentMonster->x), 2) + pow(abs(tour->y - currentMonster->y), 2));
        //printf("%lf -- ", distance);
        //printf("%d -- ", tour->radar);
        if(distance < distanceMin && distance <= tour->radar) {
            distanceMin = distance;
            tour->lastMonster = currentMonster;
        }
        currentMonster = currentMonster->next;   
    }
    return 0;
}

int refindMonster(Tour* tour) {
    double distance = 0;
    if(tour->lastMonster->status == DEAD || sqrt(pow(abs(tour->x - tour->lastMonster->x), 2) + pow(abs(tour->y - tour->lastMonster->y), 2)) > tour->radar) {
        tour->lastMonster = NULL;
    }
    return 0;
}