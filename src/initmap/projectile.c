#include "projectile.h"

ListProjectiles* projectile_initListProjectiles()
{
  ListProjectiles* listProjectiles = malloc(sizeof(ListProjectiles));
  if (!listProjectiles) {
    printf("ERROR ALLOC : listProjectiles");
    exit(CHK_ERROR_ALLOC);
  }
  listProjectiles->nbProjectile = 0;
  listProjectiles->next = NULL;

  return listProjectiles;
}

int create_projectile(Tour* tour, Monster* monster, float degats) {
  Projectile* projectile = malloc(sizeof(Projectile));
  if (!projectile) {
    printf("ERROR ALLOC : projectile");
    exit(CHK_ERROR_ALLOC);
  }
  projectile->cible = monster;
  projectile->x = tour->x;
  projectile->y = tour->y;
  projectile->damage = degats;
  projectile->next = NULL;

  addToProjectiles(projectile);
  Mix_PlayChannel(-1, gameData->sound[PROJECTILE], 0);
  plateau->listProjectiles->nbProjectile++;
}


int addToProjectiles(Projectile* projectile) {
  if(plateau->listProjectiles->next == NULL) {
    plateau->listProjectiles->next = projectile;
    return 0;
  }
  Projectile* currentProjectile = plateau->listProjectiles->next;
  while (currentProjectile->next != NULL)
  {  
    currentProjectile = currentProjectile->next;
  }
  currentProjectile->next = projectile;
  return 0;
}

int projectile_moveAll() {
  if(plateau->listProjectiles->next == NULL) {
    return 0;
  }

  Projectile* currentProjectile = plateau->listProjectiles->next;
  int status;
  Projectile* projectileDelete;

  while (currentProjectile != NULL) {  
    projectileDelete = currentProjectile;

    if(currentProjectile->cible->status == DEAD) {
      currentProjectile = currentProjectile->next;
      deleteToProjectile(projectileDelete);
    } else {
      status = moveProjectile(currentProjectile);
      currentProjectile = currentProjectile->next;
      if(status == 1) {
        deleteToProjectile(projectileDelete);
      }  
    }

  }
  return 0;
}

int moveProjectile(Projectile* projectile) {
  if(projectile->cible->x - projectile->x > 0.15 || projectile->cible->x - projectile->x < -0.15) {
    if(projectile->cible->x - projectile->x < 0) {
      projectile->x = projectile->x - 0.15;

    } else {
      projectile->x = projectile->x + 0.15;
    }   
  }
  if (projectile->cible->y - projectile->y > 0.15 || projectile->cible->y - projectile->y < -0.15) {
    if(projectile->cible->y - projectile->y < 0) {
      projectile->y = projectile->y - 0.15;
    } else {
      projectile->y = projectile->y + 0.15;
    }
  }
  
  if (!(projectile->cible->x - projectile->x > 0.15 || projectile->cible->x - projectile->x < -0.15)) {
    if (!(projectile->cible->y - projectile->y > 0.15 || projectile->cible->y - projectile->y < -0.15)) {
      monster_attack(projectile);
      return 1;
    }
  }
  return 0;
}

int deleteToProjectile(Projectile* projectile) {
  if(plateau->listProjectiles->next == projectile) {
    plateau->listProjectiles->next = plateau->listProjectiles->next->next;
  } else { 
    Projectile* currentProjectile = plateau->listProjectiles->next;
    while (currentProjectile->next != projectile)
    {  
      currentProjectile = currentProjectile->next; 
    }
    currentProjectile->next = currentProjectile->next->next;
  }
  plateau->listProjectiles->nbProjectile--;
  free(projectile);
  return 0;
}

void projectile_freeListProjectiles(ListProjectiles* listProjectiles) {
  Projectile* projectileFree;
  Projectile* currentProjectile = NULL;
  if(listProjectiles->next != NULL) {
    projectileFree = listProjectiles->next;
    currentProjectile = listProjectiles->next->next;
    free(projectileFree);
  }
  while(currentProjectile != NULL) {
    projectileFree = currentProjectile;
    currentProjectile = currentProjectile->next;
    free(projectileFree);
  }
  free(listProjectiles);
}
