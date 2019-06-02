#include "sound.h"

void sound_init()
{
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
    printf("%s", Mix_GetError());
  }

  sound = malloc(sizeof(Mix_Music*)*10);

  Mix_Music *musique;
  musique = Mix_LoadMUS("sound/musique.wav");
  Mix_PlayMusic(musique, -1);

  Mix_AllocateChannels(10);
  Mix_Chunk *son;

  son = Mix_LoadWAV("sound/addTower.wav");
  sound[TOWER] = son;

    son = Mix_LoadWAV("sound/addCentrale.wav");
  sound[CENTRAL] = son;
  
  son = Mix_LoadWAV("sound/projectile.wav");
  sound[PROJECTILE] = son;

  son = Mix_LoadWAV("sound/monsterSolder.wav");
  sound[SOLD] = son;

  son = Mix_LoadWAV("sound/monsterGeneral.wav");
  sound[GENE] = son;

  son = Mix_LoadWAV("sound/monsterHuge_Solder.wav");
  sound[HSOLD] = son;

  son = Mix_LoadWAV("sound/monsterBoss.wav");
  sound[BOS] = son;

  son = Mix_LoadWAV("sound/beginLevel.wav");
  sound[BEGINLEVEL] = son;

  son = Mix_LoadWAV("sound/levelLose.wav");
  sound[LOSELEVEL] = son;

  son = Mix_LoadWAV("sound/levelWin.wav");
  sound[WINLEVEL] = son;

}
