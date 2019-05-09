#include "monster.h"

// TODO: fix bugs sur les balles qui ne tuent pas le monstre et le collent.

int initListMonsters()
{
  ListMonsters* listMonsters = malloc(sizeof(ListMonsters));
  DataMonsters** dataMonsters = malloc(sizeof(DataMonsters*) * 4);

  dataMonsters[SOLDER] = malloc(sizeof(DataMonsters));
  dataMonsters[HUGE_SOLDER] = malloc(sizeof(DataMonsters));
  dataMonsters[GERERAL] = malloc(sizeof(DataMonsters));
  dataMonsters[BOSS] = malloc(sizeof(DataMonsters));
  // TODO: Checker l'allocation

  listMonsters->monster_total = 0;
  listMonsters->firstMonster = NULL;

  // NOTE: Moins pratique le tableau de champs, mieux vaut faire des tableaux de structures
  //dataMonsters->PDV = malloc(sizeof(int)*4);
  //dataMonsters->strength = malloc(sizeof(int)*4);
  //dataMonsters->mass = malloc(sizeof(double)*4);

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

  listMonsters->dataMonsters = dataMonsters;

  plateau->listMonsters = listMonsters;
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


int monster_popMonster(InfosNodes* InfosNodes, TypeMonster type, int idIn) 
{
  Monster* monster = malloc(sizeof(Monster)); 
  // TODO: Checker l'allocation

  monster->PDV = plateau->listMonsters->dataMonsters[type]->PDV;
  monster->strength = plateau->listMonsters->dataMonsters[type]->strength;
  monster->mass = plateau->listMonsters->dataMonsters[type]->mass;
  monster->value = plateau->listMonsters->dataMonsters[type]->value;

  monster->next = NULL;
  monster->idIn = idIn;
  monster->type = type;
  monster->status = ALIVE;
  monster->orientation = HAUT;
  monster->x = InfosNodes->nodes[idIn].x;
  monster->y = InfosNodes->nodes[idIn].y;
  itineraire_initMonster(monster, InfosNodes);

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
  monster->status = DEAD;
  player_gagneArgent(plateau->listMonsters->dataMonsters[monster->type]->value);
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
  }
}



// TODO: Trouver à quoi sert cette fonction, semble inutilisée.
void get_itineraire(Monster* monster) 
{
  free(monster);
}

Orientation monster_moveDirection(Monster* monster)
{
  float difference_x = fabs(monster->itineraire->next->node->x - monster->x); 
  float difference_y = fabs(monster->itineraire->next->node->y - monster->y); 

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
  if (monster->itineraire->next == NULL) {
    // TODO: La partie est terminée.
    return 0;
  }

  /* Le monstre est sur un mouvement horizontal */
  if(monster_moveDirection(monster) == HORIZONTAL) {
    if(monster->itineraire->next->node->x - monster->x < 0) {
      monster->x = monster->x - 0.01/monster->mass;
      monster->orientation = GAUCHE;
    } else {
      monster->x = monster->x + 0.01/monster->mass;
      monster->orientation = DROITE;
    }   
  }

  /* Le monstre est sur un mouvement vertical */
  else if (monster_moveDirection(monster) == VERTICAL) {
    if(monster->itineraire->next->node->y - monster->y < 0) {
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

int moveAllMonster()
{
  Monster* currentMonster = plateau->listMonsters->firstMonster;

  while (currentMonster != NULL) {  
    moveMonster(currentMonster);
    currentMonster = currentMonster->next;
  }
  return 0;
}
