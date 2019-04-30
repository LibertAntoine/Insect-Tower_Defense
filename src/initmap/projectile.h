#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "monster.h"
#include "tour.h"


typedef struct Monster Monster;
typedef struct Tour Tour;

typedef enum ProjectileType {
    LAS,
    MIS
} ProjectileType;

typedef struct Projectile Projectile;
struct Projectile {
  Monster* cible;
  ProjectileType type;
  int damage;
  double x;
  double y;
  Projectile* next;
};

typedef struct ListProjectiles {
    int nbProjectile;
    Projectile* next;
} ListProjectiles;


int create_projectile(Tour* tour, Monster* monster);
int addToProjectiles(Projectile* projectile);
int moveAllProjectiles();
int moveProjectile(Projectile* projectile);
int deleteToProjectile(Projectile* projectile);
#endif //PROJECTILE_H_
