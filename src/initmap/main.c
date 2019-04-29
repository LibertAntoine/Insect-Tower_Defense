#include <SDL2/SDL.h>

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "short-path-algo.h"
#include "cases.h"
#include "ppm-loader.h"
#include "itd-file.h"
#include "drawMonster.h"
#include "monster.h"



extern Plateau* plateau;

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "test";

/* Espace fenetre virtuelle */
static const float GL_VIEW_WIDTH = 200.;
static const float GL_VIEW_HEIGHT = 150.;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

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






void reshape(SDL_Window** surface, SDL_GLContext *GLcontext, unsigned int width, unsigned int height) {
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

  glViewport(0, 0, window_width, window_height);
  //glViewport(0, -window_height, window_width, window_height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(1, plateau->Xsplit +1 , plateau->Ysplit +1, 1);
}

int main(int argc, char *argv[])
{

    MapData* mapData = itd_initMapData();
    
    idt_load("level2.itd", mapData);
    case_initPlateau(mapData);
    getShortPath(mapData->infosNodes);
    ListMonsters* listMonsters = initListMonsters();

    createMonster(listMonsters, mapData->infosNodes, SOLDER, 2);


  Uint32 beginMomentLevel = SDL_GetTicks();


    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    fprintf( stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }

  #ifdef _WIN32 
  if(glewInit() == 0)
  {
    fprintf( stderr, "Impossible d'initialiser Glew. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  #endif

 /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
  SDL_Window* surface;
  SDL_GLContext GLcontext = NULL;
  reshape(&surface, &GLcontext, WINDOW_WIDTH, WINDOW_HEIGHT);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);


/* Boucle principale */
  int loop = 1;
  while(loop) 
  {
    /* Recuperation du temps au debut de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* Placer ici le code de dessin */
    glClear(GL_COLOR_BUFFER_BIT);

    launchWaves(listMonsters, mapData, mapData->listWaves->next, (SDL_GetTicks() - beginMomentLevel));

    moveAllMonster(listMonsters);
    display_drawMonsters(listMonsters);
    /* Echange du front et du back buffer : mise a jour de la fenetre */
    SDL_GL_SwapWindow(surface);

  SDL_Event e;
    while(SDL_PollEvent(&e)) 
    {
      /* L'utilisateur ferme la fenetre : */
      if(e.type == SDL_QUIT) 
      {
        loop = 0;
        break;
      }

      if(e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
      {
        loop = 0; 
        break;
      }

    }
    
    /* Calcul du temps ecoule */
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    /* Si trop peu de temps s'est ecoule, on met en pause le programme */
    if(elapsedTime < FRAMERATE_MILLISECONDS) 
    {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  /* Liberation des ressources associees a la SDL */ 
  SDL_Quit();

  return EXIT_SUCCESS;

}
