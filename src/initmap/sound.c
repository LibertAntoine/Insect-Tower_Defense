#include "sound.h"

void sound_init()
{
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
    printf("%s", Mix_GetError());
  }

  gameData->sound = malloc(sizeof(Mix_Music*)*10);
  if (!gameData->sound) {
    printf("ERROR ALLOC : sound");
    exit(CHK_ERROR_ALLOC);
  }

  Mix_Music *musique;
  musique = Mix_LoadMUS("sound/musique.wav");
  Mix_PlayMusic(musique, -1);

  Mix_AllocateChannels(10);
  Mix_Chunk *son;

  son = Mix_LoadWAV("sound/addTower.wav");
  gameData->sound[TOWER] = son;

    son = Mix_LoadWAV("sound/addCentrale.wav");
  gameData->sound[CENTRAL] = son;
  
  son = Mix_LoadWAV("sound/projectile.wav");
  gameData->sound[PROJECTILE] = son;

  son = Mix_LoadWAV("sound/monsterSolder.wav");
  gameData->sound[SOLD] = son;

  son = Mix_LoadWAV("sound/monsterGeneral.wav");
  gameData->sound[GENE] = son;

  son = Mix_LoadWAV("sound/monsterHuge_Solder.wav");
  gameData->sound[HSOLD] = son;

  son = Mix_LoadWAV("sound/monsterBoss.wav");
  gameData->sound[BOS] = son;

  son = Mix_LoadWAV("sound/beginLevel.wav");
  gameData->sound[BEGINLEVEL] = son;

  son = Mix_LoadWAV("sound/levelLose.wav");
  gameData->sound[LOSELEVEL] = son;

  son = Mix_LoadWAV("sound/levelWin.wav");
  gameData->sound[WINLEVEL] = son;

}
