#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "structures.h"

#include "monster.h"
#include "tour.h"

int create_projectile(Tour* tour, Monster* monster, float degats);
int addToProjectiles(Projectile* projectile);
int moveAllProjectiles();
int moveProjectile(Projectile* projectile);
int deleteToProjectile(Projectile* projectile);
#endif //PROJECTILE_H_
