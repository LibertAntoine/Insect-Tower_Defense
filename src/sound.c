#include "sound.h"

void sound_init()
{
  Mix_Init(MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
    printf("%s", Mix_GetError());
  }

  gameData->sound = malloc(sizeof(Mix_Chunk*)*20);
  if (!gameData->sound) {
    printf("ERROR ALLOC : sound");
    exit(CHK_ERROR_ALLOC);
  }

  Mix_Music *musique;
  musique = Mix_LoadMUS("sound/musique.mp3");
  Mix_PlayMusic(musique, -1);

  Mix_AllocateChannels(16);
  Mix_Chunk *son;

  son = Mix_LoadWAV("sound/addTower.ogg");
  gameData->sound[TOWER] = son;

  son = Mix_LoadWAV("sound/addCentrale.ogg");
  gameData->sound[CENTRAL] = son;
  
  son = Mix_LoadWAV("sound/projectile.ogg");
  gameData->sound[PROJECTILE] = son;

  son = Mix_LoadWAV("sound/monsterSolder.ogg");
  gameData->sound[SOLD] = son;

  son = Mix_LoadWAV("sound/monsterGeneral.ogg");
  gameData->sound[GENE] = son;

  son = Mix_LoadWAV("sound/monsterHuge_Solder.ogg");
  gameData->sound[HSOLD] = son;

  son = Mix_LoadWAV("sound/monsterBoss.ogg");
  gameData->sound[BOS] = son;

  son = Mix_LoadWAV("sound/beginLevel.ogg");
  gameData->sound[BEGINLEVEL] = son;

  son = Mix_LoadWAV("sound/levelLose.ogg");
  gameData->sound[LOSELEVEL] = son;

  son = Mix_LoadWAV("sound/levelWin.ogg");
  gameData->sound[WINLEVEL] = son;

  son = Mix_LoadWAV("sound/snap.ogg");
  gameData->sound[SNAP] = son;

  son = Mix_LoadWAV("sound/hit-wood.ogg");
  gameData->sound[HITWOOD] = son;

  son = Mix_LoadWAV("sound/bleep.ogg");
  gameData->sound[BLEEP] = son;

  son = Mix_LoadWAV("sound/error.ogg");
  gameData->sound[ERROR] = son;
}
