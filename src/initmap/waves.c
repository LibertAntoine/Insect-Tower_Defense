#include "waves.h"

// TODO: Clarifier le fonctionnement de la fonction. Ex: rendre les variables moins magiques.
int wave_reduceWaveMonsterArray(TypeMonster* t, int monster_id, int monster_total)
{
  int i = 0;
  int j = 0;

  for (int id = monster_id; id < monster_total; id++) {
    t[id] = t[id+1];
  }

  return 0;
}

int moveWave(MapData* mapdata, Wave* currentWave)
{
  srand(time(NULL));
   
  /* Pas de monstre restant dans la vague */
  if(currentWave->monster_total == 0) {
    return 0;
  }
  else if (currentWave->nextMonster_timer + (sin(rand()) * currentWave->random) > 0) {
    currentWave->nextMonster_timer -= 1.0/60.0;
    return 0;
  }
  /* On pop un monstre */
  else {
    int monster_id = rand()%(currentWave->monster_total);
    int entrance_num = rand()%(mapdata->infosNodes->entrance_total);
    int entrance_id = mapdata->infosNodes->idEntrees[entrance_num];
    TypeMonster monster_type = currentWave->monsters[monster_id];

    wave_reduceWaveMonsterArray(currentWave->monsters, monster_id, currentWave->monster_total);

    currentWave->monster_total--;
    monster_popMonster(mapdata->infosNodes, monster_type, entrance_id);
    currentWave->nextMonster_timer = currentWave->freq_pop;
    return 0;
  }
}

int launchWaves(MapData* mapdata, float timer) {
  int restMonster = 0;

  Wave* currentWave = malloc(sizeof(Wave));
  // TODO: Vérifier l'allocation.

  currentWave = mapdata->listWaves->next;

  while(currentWave != NULL) {
    restMonster = restMonster + currentWave->monster_total;
    if(currentWave->timeBegin * 1000 < timer) {
      moveWave(mapdata, currentWave);
    }
    currentWave = currentWave->next;
  }

  /* La vague est terminée */
  if(restMonster == 0) {
    return 1;
  }
  return 0;
}
