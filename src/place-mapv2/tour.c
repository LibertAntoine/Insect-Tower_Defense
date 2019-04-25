#include "tour.h"

ConstructionData buildTypes[6];

buildTypes[LASER].type = LASER;
buildTypes[LASER].degats = 1;
buildTypes[LASER].alimentation = 1;
buildTypes[LASER].cadence = 2;
buildTypes[LASER].portee = 1;
buildTypes[LASER].valeur_achat = 200;
buildTypes[LASER].valeur_revente = 100;

buildTypes[MISSILE].type = MISSILE;
buildTypes[MISSILE].degats = 2;
buildTypes[MISSILE].alimentation = 1;
buildTypes[MISSILE].cadence = 1;
buildTypes[MISSILE].portee = 1;
buildTypes[MISSILE].valeur_achat = 300;
buildTypes[MISSILE].valeur_revente = 150;

buildTypes[RADAR].type = RADAR;
buildTypes[RADAR].degats = 0;
buildTypes[RADAR].alimentation = 0;
buildTypes[RADAR].cadence = 0;
buildTypes[RADAR].portee = 1;
buildTypes[RADAR].valeur_achat = 400;
buildTypes[RADAR].valeur_revente = 200;

buildTypes[ARMEMENT].type = ARMEMENT;
buildTypes[ARMEMENT].degats = 1;
buildTypes[ARMEMENT].alimentation = 0;
buildTypes[ARMEMENT].cadence = 0;
buildTypes[ARMEMENT].portee = 0;
buildTypes[ARMEMENT].valeur_achat = 400;
buildTypes[ARMEMENT].valeur_revente = 200;

buildTypes[CENTRALE].type = CENTRALE;
buildTypes[CENTRALE].degats = 0;
buildTypes[CENTRALE].alimentation = 1;
buildTypes[CENTRALE].cadence = 0;
buildTypes[CENTRALE].portee = 0;
buildTypes[CENTRALE].valeur_achat = 400;
buildTypes[CENTRALE].valeur_revente = 200;

buildTypes[MUNITION].type = MUNITION;
buildTypes[MUNITION].degats = 0;
buildTypes[MUNITION].alimentation = 0;
buildTypes[MUNITION].cadence = 1;
buildTypes[MUNITION].portee = 0;
buildTypes[MUNITION].valeur_achat = 400;
buildTypes[MUNITION].valeur_revente = 200;

int tour_getPrix(TypeCase type)
{
  return buildTypes[type].valeur_achat;
}


