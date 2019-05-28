#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#ifdef _WIN32
  #include <GL/glew.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "structures.h"

#include "cases.h"
#include "itd-file.h"
#include "monster.h"
#include "display.h"
#include "waves.h"
#include "player.h"
#include "tour.h"
#include "itineraire.h"
#include "SDLConfig.h"
#include "projectile.h"
#include "gui.h"
#include "mouse.h"
#include "keyboard.h"
#include "sound.h"
#include "sprite.h"

Plateau *plateau = NULL;
Texture** textures = NULL;
Mix_Chunk** sound = NULL;

GUI *bodyGUI; //variable globale de l'interface
GUI *plateauGUI;
GUI *bottomGUI;
GUI *topGUI;

int main(int argc, char *argv[])
{
  /* Récuperation des informations itd/ppm */
  MapData* mapData = idt_load("level/level2.itd");
    
  /* Création du plateau */
  plateau = case_initPlateau(mapData);

  /* Calcul des chemins les plus courts */
  itineraire_findShortestPath(mapData->infosNodes);

  /* Définition de l'environnement SDL*/
  sdlConfig_initSDL();
  SDL_Window* surface;
  SDL_GLContext GLcontext = NULL;
  sdlConfig_reshape(&surface, &GLcontext, WINDOW_WIDTH, WINDOW_HEIGHT);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

  sprite_init();
  gui_init();
  sound_init();

  GLuint idGrid = glGenLists(1);
  display_gridList(idGrid);

  GLuint idMap = glGenLists(1);
  display_mapList(idMap);
  // Position X, Y en pixel ET en indice de case de la souris
  int pixelMouseX, pixelMouseY, caseMouseX, caseMouseY;

  Uint32 beginMomentLevel = SDL_GetTicks();
  Mix_PlayChannel(-1, sound[BEGINLEVEL], 0);

  /* Boucle principale */
  int loop = 1;
  int frameFPS = 0;
  Uint32 lastCheckFPS = beginMomentLevel;
  while(loop) {
    Uint32 startTime = SDL_GetTicks();

    /* Placer ici le code de dessin */
    glClear(GL_COLOR_BUFFER_BIT);

    // NOTE: display general GUI


    launchWaves(mapData, (SDL_GetTicks() - beginMomentLevel));

    if (plateau->play == TRUE) {
      monster_moveAll();
      tour_attackAll();
      projectile_moveAll();
    }

    display_window();
    display_game(plateauGUI, idMap, idGrid);
    
    /* Echange du front et du back buffer : mise a jour de la fenetre */
    SDL_GL_SwapWindow(surface);

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      /* L'utilisateur ferme la fenetre : */
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }

      if(e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE)) {
        loop = 0; 
        break;
      }

      Etat *joueur = plateau->joueur;
      TypeCase type = joueur->type;
      Action action = joueur->action;

      mouse_handlePosition();
      switch(e.type) {
        case SDL_MOUSEMOTION:
          break;

        case SDL_MOUSEBUTTONDOWN:
          mouse_handleClick();
          break;

        case SDL_WINDOWEVENT:
          if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
            sdlConfig_reshape(&surface, &GLcontext, e.window.data1, e.window.data2);
          }
          break;

        case SDL_KEYDOWN:
          keyboard_handleKeypress(&e);

        default:
          break;
      }
    }


    /* Calcul du temps ecoule */
    Uint32 elapsedTime = SDL_GetTicks() - startTime;

    /* Si trop peu de temps s'est ecoule, on met en pause le programme */
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }

    /* NOTE: Display FPS counter
    frameFPS++;
    Uint32 elapsedTimeFPS = SDL_GetTicks() - lastCheckFPS;
    if (elapsedTimeFPS >= 1000) {
      printf("FPS : %f\n", frameFPS / (elapsedTimeFPS / 1000.));
      frameFPS = 0;
      lastCheckFPS = SDL_GetTicks();
    }
    */
  }

  /* Liberation des ressources associees a la SDL */ 
  Mix_CloseAudio();
  SDL_Quit();
  return EXIT_SUCCESS;

}
