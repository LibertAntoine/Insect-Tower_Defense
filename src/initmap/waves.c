#include "waves.h"

int deleteInArray(int* t, int monster, int nbMonster) {
  int i = 0;
  int j = 0;
    for(i=0; i<5; i++ ) {
      if( t[i]==monster) {
        for(j=i; j < nbMonster; j++) {
          if( j < nbMonster-1) {
            t[j] = t[j+1];
          } else {
            t[j] = 0;
          }
        }
      }
    }
    return 0;
}

int moveWave(ListMonsters* listMonsters, MapData* mapdata, Wave* currentWave) {
  srand(time(NULL));
   
  if(currentWave->nbMonster == 0) {
    return 0;
  } else if (currentWave->nextMonster+(sin(rand())*currentWave->random) > 0 ) {
    currentWave->nextMonster = currentWave->nextMonster - 1.0/60.0;
    return 0;
  } else {
     
    int selectMonster = rand()%(currentWave->nbMonster);
    int selectIn = rand()%(mapdata->infosNodes->nbEntrees);
    int selectIdIn = mapdata->infosNodes->idEntrees[selectIn];
    int selectType = currentWave->monsters[selectMonster];
    deleteInArray(currentWave->monsters, selectMonster, currentWave->nbMonster);
    currentWave->nbMonster--;
    createMonster(listMonsters, mapdata->infosNodes, selectType, selectIdIn);
    currentWave->nextMonster = currentWave->freq;
    return 0;
  }
}

int launchWaves(ListMonsters* listMonsters, MapData* mapdata, Wave* currentWave, float timer) {
  int restMonster = 0;
  while(currentWave->next != NULL) {
    
    restMonster = restMonster + currentWave->nbMonster;
    if(currentWave->timeBegin*1000 < timer) {
      moveWave(listMonsters, mapdata, currentWave);
    }
    currentWave = currentWave->next;
  }
  if(restMonster == 0) {
    return 1;
  }
  return 0;
}
