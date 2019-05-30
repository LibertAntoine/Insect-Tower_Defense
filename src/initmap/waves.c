#include "waves.h"

int wave_reduceWaveMonsterArray(int monster_id)
{
  for (int id = monster_id; id < plateau->currentWave.monster_total; id++) {
    plateau->currentWave.monsters[id] = plateau->currentWave.monsters[id+1];
  }

  return 0;
}

int moveWave()
{
  srand(time(NULL));
   
  /* Pas de monstre restant dans la vague */
  if(plateau->currentWave.monster_total == 0) {
    if(plateau->currentWave.next != NULL) {
      if(plateau->currentWave.timeBeforeNext >= 0) {
        plateau->currentWave.timeBeforeNext -= 1.0/60.0;
        return 0;
      } else {
        TypeMonster* tmp = malloc(sizeof(TypeMonster)*plateau->currentWave.next->monster_total);
        memcpy(tmp , plateau->currentWave.next->monsters, sizeof(TypeMonster)*plateau->currentWave.next->monster_total);
        plateau->currentWave = *plateau->currentWave.next;
        plateau->currentWave.monsters = tmp;
        return 0;
      }
    } else {
      /* Fin des vagues de monstres */
      return 1;
    }
  }
  else if (plateau->currentWave.nextMonster_timer + (sin(rand()) * plateau->currentWave.random) > 0) {
    plateau->currentWave.nextMonster_timer -= 1.0/60.0;
    return 0;
  }
  /* On pop un monstre */
  else {
    int monster_id = rand()%(plateau->currentWave.monster_total);
    int entrance_num = rand()%(mapData->infosNodes->entrance_total);
    int entrance_id = mapData->infosNodes->idEntrees[entrance_num];
    TypeMonster monster_type = plateau->currentWave.monsters[monster_id];

    wave_reduceWaveMonsterArray(monster_id);

    plateau->currentWave.monster_total--;
    monster_popMonster(monster_type, entrance_id);
    plateau->currentWave.nextMonster_timer = plateau->currentWave.freq_pop;
    return 0;
  }
}

void wave_freeListWaves() {
  Wave* waveFree;
  Wave* currentWave = NULL;
  if(mapData->listWaves->next != NULL) {
    waveFree = mapData->listWaves->next;
    currentWave = mapData->listWaves->next->next;
    free(waveFree);
  }
  while(currentWave->next != NULL) {
    waveFree = currentWave;
    currentWave = currentWave->next;
    free(waveFree);
  }
  free(mapData->listWaves);
}
