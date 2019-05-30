#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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
GameState gameState = MAINMENU;
Uint32 beginMomentLevel = NULL;
MapData* mapData = NULL;

GUI *bodyGUI; //variable globale de l'interface
GUI *plateauGUI;
GUI *bottomGUI;
GUI *topGUI;
GUI *infoGUI;
GUI *buttonGUI;
GUI *buttonGUI;
GUI *mainMenuGUI; 
GUI *endMenuGUI; 

DefaultList **default_list = NULL;

int main(int argc, char *argv[])
{

  /* Définition de l'environnement SDL*/
  sdlConfig_initSDL();
  SDL_Window* surface;
  SDL_GLContext GLcontext = NULL;
  sdlConfig_reshape(&surface, &GLcontext, WINDOW_WIDTH, WINDOW_HEIGHT);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

  gui_init();
  sprite_init();
  sound_init();

  // Position X, Y en pixel ET en indice de case de la souris
  int pixelMouseX, pixelMouseY, caseMouseX, caseMouseY;

  /* Boucle principale */
  int loop = 1;
  int frameFPS = 0;
  Uint32 lastCheckFPS = beginMomentLevel;
  while(loop) {
    Uint32 startTime = SDL_GetTicks();

    /* Placer ici le code de dessin */
    glClear(GL_COLOR_BUFFER_BIT);

    if(gameState == LEVELPLAY) {
      // NOTE: display general GUI
      display_window();
      display_game(plateauGUI, mapData->idMap, mapData->idGrid);
      if (plateau->play == TRUE) {
        
        tour_attackAll();
        projectile_moveAll();
        moveWave();
        if(monster_moveAll() == 1 && plateau->currentWave.next == NULL) {
          if(plateau->currentWave.monster_total == 0) {
            case_freePlateau();
            Mix_PlayChannel(-1, sound[WINLEVEL], 0);
            gameState = WINMENU;
          }
        }
      }

    } else if (gameState == MAINMENU) {
      display_mainMenu();
    } else if (gameState == LOSEMENU) {
      display_endMenu();
    } else if (gameState == WINMENU) {
      display_endMenu();
    }

    display_showCursor();

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
      if(gameState == LEVELPLAY) {
        Etat *joueur = plateau->joueur;
        TypeCase type = joueur->type;
        Action action = joueur->action;
      }

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













                  
