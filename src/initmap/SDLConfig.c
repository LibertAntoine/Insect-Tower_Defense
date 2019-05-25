#include "SDLConfig.h"

void sdlConfig_initSDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    fprintf( stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
}

void sdlConfig_reshape(SDL_Window** surface, SDL_GLContext *GLcontext, unsigned int width, unsigned int height)
{

  SDL_Window* surface_temp = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  if(NULL == surface_temp) 
  {
    fprintf( stderr, "Erreur lors du redimensionnement de la fenetre.\n");
    exit(EXIT_FAILURE);
  }
  *surface = surface_temp;

  int window_width, window_height;
  SDL_GetWindowSize(*surface, &window_width, &window_height);

  if (*GLcontext == NULL) {
    *GLcontext = SDL_GL_CreateContext(*surface);
  }

  #ifdef _WIN32 
  if(glewInit() != 0)
  {
    fprintf( stderr, "Impossible d'initialiser Glew. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  #endif

  glViewport(0, 0, window_width, window_height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(1, plateau->Xsplit+1, plateau->Ysplit+1, 1);
}


void sdlConfig_initSon() {
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
  {
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
