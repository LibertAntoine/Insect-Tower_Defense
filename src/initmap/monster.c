#include "monster.h"
/*
DataMonsters** monster_initDataMonster()
{
  DataMonsters** dataMonsters = malloc(sizeof(DataMonsters*) * 4);

  dataMonsters[SOLDER] = malloc(sizeof(DataMonsters));
  dataMonsters[HUGE_SOLDER] = malloc(sizeof(DataMonsters));
  dataMonsters[GERERAL] = malloc(sizeof(DataMonsters));
  dataMonsters[BOSS] = malloc(sizeof(DataMonsters));

  dataMonsters[SOLDER]->PDV = 1;
  dataMonsters[SOLDER]->strength = 1;
  dataMonsters[SOLDER]->mass = 1.0;
  dataMonsters[SOLDER]->value = 1.0;

  dataMonsters[HUGE_SOLDER]->PDV = 2;
  dataMonsters[HUGE_SOLDER]->strength = 2;
  dataMonsters[HUGE_SOLDER]->mass = 2.0;
  dataMonsters[HUGE_SOLDER]->value = 2.0;

  dataMonsters[GERERAL]->PDV = 3;
  dataMonsters[GERERAL]->strength = 1;
  dataMonsters[GERERAL]->mass = 1.0;
  dataMonsters[GERERAL]->value = 1.0;

  dataMonsters[BOSS]->PDV = 4;
  dataMonsters[BOSS]->strength = 1;
  dataMonsters[BOSS]->mass = 1.0;
  dataMonsters[BOSS]->value = 1.0;

  return dataMonsters;
}
*/
ListMonsters* monster_initListMonster()
{
  ListMonsters* listMonsters = malloc(sizeof(ListMonsters));
  // TODO: Checker l'allocation
  listMonsters->monster_total = 0;
  listMonsters->firstMonster = NULL;

  return listMonsters;
}

int addToList(Monster* monster)
{
  if(plateau->listMonsters->firstMonster == NULL) {
    plateau->listMonsters->firstMonster = monster;
    return 0;
  }

  Monster* currentMonster = plateau->listMonsters->firstMonster;
  while (currentMonster->next != NULL) {  
    currentMonster = currentMonster->next;
  }
  currentMonster->next = monster;
  return 0;
}

void monster_printInfos(Monster *monster)
{
  TypeMonster type = monster->type;
  char name[20];
  switch (type) {
    case SOLDER:
      strcpy(name, "solder");
      break;
    case HUGE_SOLDER:
      strcpy(name, "huge_solder");
      break;
    case GERERAL:
      strcpy(name, "gereral");
      break;
    case BOSS:
      strcpy(name, "boss");
      break;
  }

  printf("Monstre : %s\n", name);
  printf("PDV : %f/%f\n", monster->PDV, mapData->dataMonsters[type].PDV);
  printf("vitesse : %f\n", mapData->dataMonsters[type].mass);
  printf("Position x %lf | y %lf\n", monster->x, monster->y);
}

int monster_popMonster(TypeMonster type, int idIn) 
{
  Monster* monster = malloc(sizeof(Monster)); 
  // TODO: Checker l'allocation

  if (type == SOLDER) {
    monster->sprite_texture = sprite_loadSprite(SOLDER_TEX, 900, TRUE);
  }
  else if (type == HUGE_SOLDER) {
    monster->sprite_texture = sprite_loadSprite(HUGE_SOLDER_TEX, 700, TRUE);
  }
  else if (type == BOSS) {
    monster->sprite_texture = sprite_loadSprite(BOSS_TEX, 2700, TRUE);
  }
  else if (type == GERERAL) {
    monster->sprite_texture = sprite_loadSprite(GERERAL_TEX, 1800, TRUE);
  }

  monster->PDV = mapData->dataMonsters[type].PDV;
  monster->strength = mapData->dataMonsters[type].strength;
  monster->mass = mapData->dataMonsters[type].mass;
  monster->value = mapData->dataMonsters[type].value;

  monster->next = NULL;
  monster->idIn = idIn;
  monster->type = type;
  monster->status = ALIVE;
  monster->decomposition = 10;
  monster->orientation = HAUT;
  monster->x = mapData->infosNodes->nodes[idIn].x;
  monster->y = mapData->infosNodes->nodes[idIn].y;
  itineraire_initMonster(monster);

  addToList(monster);
  plateau->listMonsters->monster_total++;
  return 0;
}

void monster_attack(Projectile* projectile) 
{
  printf("attack\n\n");
  projectile->cible->PDV = projectile->cible->PDV - projectile->damage;
  if(projectile->cible->PDV <= 0) {
    monster_kill(projectile->cible);
  }
}

void monster_kill(Monster* monster) 
{
  Mix_PlayChannel(-1, sound[MONSTERKILL], 0);

  monster->status = DEAD;
  free(monster->sprite_texture);
  monster->sprite_texture = sprite_loadSprite(SPLASH_TEX, 0, FALSE); 
  monster->decomposition = 1; 
  player_gagneArgent(mapData->dataMonsters[monster->type].value);
  itineraire_addValueChemin(monster);
}

void monster_delete(Monster* monster) 
{
  itineraire_removeValueChemin(monster);
  monster_removeFromList(monster);
}

void monster_removeFromList(Monster* monster)
{
  Monster* monster_from_list = plateau->listMonsters->firstMonster;
  if (monster_from_list == monster) {
    plateau->listMonsters->firstMonster = monster_from_list->next;
  }

  else {
    while (monster_from_list->next != monster) {
      monster_from_list = monster_from_list->next;
    }
    monster_from_list->next = monster_from_list->next->next;
    monster_freeMonster(monster);
  }
}

void monster_freeListMonsters(ListMonsters* listMonsters) {
  Monster* monsterFree;
  Monster* currentMonster = NULL;
  if(listMonsters->firstMonster != NULL) {
    Monster* currentMonster;
    monsterFree = listMonsters->firstMonster;
    currentMonster = listMonsters->firstMonster->next;
    monster_freeMonster(monsterFree);
  }
  while(currentMonster != NULL) {
    monsterFree = currentMonster;
    currentMonster = currentMonster->next;
    monster_freeMonster(monsterFree);
  }
  free(listMonsters);
}

void monster_freeMonster(Monster* monster) {
  itineraire_freeItiniraire(monster->itineraire);
  free(monster->sprite_texture);
  free(monster);
}

Orientation monster_moveDirection(Monster* monster)
{
  float difference_x = fabs(monster->itineraire->next->next->node->x - monster->x); 
  float difference_y = fabs(monster->itineraire->next->next->node->y - monster->y); 

  if (difference_x > 0.01) {
    return HORIZONTAL;
  }
  else if (difference_y > 0.01) {
    return VERTICAL;
  }
  else {
    return IMMOBILE;
  }
}

int moveMonster(Monster* monster)
{

  // NOTE: Le monstre a atteint l'arrivée.
  if (monster->itineraire->next->next == NULL) {
    case_freePlateau();
    Mix_PlayChannel(-1, sound[LOSELEVEL], 0);
    gameState = LOSEMENU;
    return 0;
  }

  /* Le monstre est sur un mouvement horizontal */
  if(monster_moveDirection(monster) == HORIZONTAL) {
    if(monster->itineraire->next->next->node->x - monster->x < 0) {
      monster->x = monster->x - 0.01/monster->mass;
      monster->orientation = GAUCHE;
    } else {
      monster->x = monster->x + 0.01/monster->mass;
      monster->orientation = DROITE;
    }   
  }

  /* Le monstre est sur un mouvement vertical */
  else if (monster_moveDirection(monster) == VERTICAL) {
    if(monster->itineraire->next->next->node->y - monster->y < 0) {
      monster->y = monster->y - 0.01/monster->mass;
      monster->orientation = HAUT;
    } else {
      monster->y = monster->y + 0.01/monster->mass;
      monster->orientation = BAS;
    }
  }

  /* Le monstre est sur un noeud, il passe au suivant */
  else {
    Etape* etape = monster->itineraire->next;
    monster->itineraire->next = monster->itineraire->next->next;
    free(etape);
    moveMonster(monster);   
  }
  return 0;
}

int monster_moveAll()
{
  Monster* currentMonster = plateau->listMonsters->firstMonster;
  Bool noLifeMonster = TRUE;
  while (currentMonster != NULL) {  
    if(currentMonster->status == DEAD) {
      currentMonster->decomposition -= 1.0/320.0;
    } else {
      noLifeMonster = FALSE;
      moveMonster(currentMonster);
      if(gameState == LOSEMENU) {
        return 0;
      }
    }

    if(currentMonster->decomposition < 0) {
      Monster* deadMonster = currentMonster;
      currentMonster = currentMonster->next;
      monster_delete(deadMonster);
    } else {
      currentMonster = currentMonster->next;
    }


  }
  if(noLifeMonster == TRUE) {
   return 1;
  }
  return 0;
}
