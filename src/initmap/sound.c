#include "sound.h"

void sound_init()
{
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
    printf("%s", Mix_GetError());
  }

  sound = malloc(sizeof(Mix_Music*)*10);

  Mix_Music *musique;
  musique = Mix_LoadMUS("sound/musique.mp3");
  Mix_PlayMusic(musique, -1);

  Mix_AllocateChannels(10);
  Mix_Chunk *son;

  son = Mix_LoadWAV("sound/addTower.wav");
  sound[TOWER] = son;
  
  son = Mix_LoadWAV("sound/projectile.wav");
  sound[PROJECTILE] = son;

  son = Mix_LoadWAV("sound/monsterDie.wav");
  sound[MONSTERKILL] = son;

  son = Mix_LoadWAV("sound/beginLevel.wav");
  sound[BEGINLEVEL] = son;

  son = Mix_LoadWAV("sound/levelLose.wav");
  sound[LOSELEVEL] = son;

  son = Mix_LoadWAV("sound/levelWIN.wav");
  sound[WINLEVEL] = son;

}
