#include <SDL2/SDL.h>

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

Plateau *plateau = NULL;

int main(int argc, char *argv[])
{
  /* Récuperation des informations idt/ppm */
  MapData* mapData = itd_initMapData();
  idt_load("level3.itd", mapData);
  
  /* Création du plateau */
  case_initPlateau(mapData);

  /* Calcul des chemins les plus courts */
  itineraire_findShortestPath(mapData->infosNodes);

  /* Définition de l'environnement SDL*/
  sdlConfig_initSDL();
  SDL_Window* surface;
  SDL_GLContext GLcontext = NULL;
  sdlConfig_reshape(&surface, &GLcontext, WINDOW_WIDTH, WINDOW_HEIGHT);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

  GLuint idGrid = glGenLists(1);
  display_gridList(idGrid);

  GLuint idMap = glGenLists(1);
  display_mapList(idMap);
  // Position X, Y en pixel ET en indice de case de la souris
  int pixelMouseX, pixelMouseY, caseMouseX, caseMouseY;

  Uint32 beginMomentLevel = SDL_GetTicks();


  /* Boucle principale */
  int loop = 1;
  while(loop) 
  {
    /* Recuperation du temps au debut de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* Placer ici le code de dessin */

    glClear(GL_COLOR_BUFFER_BIT);

    /* Affichage de la grille du plateau */
    glCallList(idMap);
    glCallList(idGrid);

    /* Affichage des tours */
    display_drawBoard();

    launchWaves(mapData, (SDL_GetTicks() - beginMomentLevel));

    moveAllMonster();
    attackAllTower();
    moveAllProjectiles();
    display_drawAllMonsters();
    display_drawAllProjectiles();
    
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

      Etat *joueur = &(plateau->joueur);
      TypeCase type = joueur->type;
      Action action = joueur->action;

      switch(e.type) 
      {
        case SDL_MOUSEBUTTONDOWN:
          SDL_GetMouseState(&pixelMouseX, &pixelMouseY);
          case_getCaseCoordFromPixels(pixelMouseX, pixelMouseY, &caseMouseX, &caseMouseY, WINDOW_WIDTH, WINDOW_HEIGHT);
          printf("\n\nmouse X -> %d\nmouse Y -> %d\n", caseMouseX, caseMouseY);


          switch(plateau->joueur.action) {
            case ADD:
              printf("invoking add\n");
              if(case_isConstructible(caseMouseX, caseMouseY)) {
                //int case_type = case_getType(caseMouseX, caseMouseY);
                printf("Porte monaie : %d \n", plateau->joueur.argent);
                if (player_acheteConstruction(caseMouseX, caseMouseY)) {
                  printf("Ajout de tour avec succes, -%d\n", tour_getPrixAchat(case_getType(caseMouseX, caseMouseY)));
                  printf("Porte monaie : %d \n", plateau->joueur.argent);
                }
                else {
                  printf("Vous n'avez pas assez\n");
                }
              }
              else {
                printf("This place is not available\n");
              }
              break;


            case GETINFO:
              case_printInfos(caseMouseX, caseMouseY);
              break;


            case REMOVE:
              printf("invoking remove\n");

              if (case_isUserPlaced(caseMouseX, caseMouseY)) {
                printf("Suppression de tour avec succes, +%d\n", tour_getPrixRevente(case_getType(caseMouseX, caseMouseY)));
                case_removeConstruction(caseMouseX, caseMouseY);
                printf("Porte monaie : %d \n", plateau->joueur.argent);
              }
              else {
                printf("You can only remove your buildings\n");
              }
              break;
          }
          break;

        case SDL_WINDOWEVENT:
          if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
            sdlConfig_reshape(&surface, &GLcontext, e.window.data1, e.window.data2);
          }
          break;

        case SDL_KEYDOWN:
          switch(e.key.keysym.sym) {
            case 'r':
              type = RADAR;
              break;
            case 'a':
              type = ARMEMENT;
              break;
            case 'c':
              type = CENTRALE;
              break;
            case 'm':
              type = MUNITION;
              break;

            case '1':
              type = LASER;
              break;
            case '2':
              type = MISSILE;
              break;

            case 'p':
              action = ADD;
              break;
            case 'i':
              action = GETINFO;
              break;
            case 'x':
              action = REMOVE;
              break;
          }
          if (action != joueur->action) {
            printf("Changing action ");
            player_afficherAction();
            printf(" --> ");
            joueur->action = action;
            player_afficherAction();
            printf("\n");
          }
          if (type != joueur->type) {
            printf("Changing tower type ");
            player_afficherEtat();
            printf(" --> ");
            joueur->type = type;
            player_afficherEtat();
            printf("\n");
          }

          break;

        default:
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
