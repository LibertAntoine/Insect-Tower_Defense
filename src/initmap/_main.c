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

#include "cases.h"
#include "itd-file.h"
#include "monster.h"
#include "display.h"
#include "waves.h"
#include "player.h"
#include "tour.h"
#include "itineraire.h"


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

void reshape(SDL_Window** surface, SDL_GLContext *GLcontext, unsigned int width, unsigned int height) {



}

int main(int argc, char *argv[])
{

    MapData* mapData = itd_initMapData();
    
    idt_load("level2.itd", mapData);
    
    case_initPlateau(mapData);
    
    getShortPath(mapData->infosNodes);
    
    ListMonsters* listMonsters = initListMonsters();

  

    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    fprintf( stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }



 /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
      SDL_Window* surface = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  if(NULL == surface) 
  { 
    fprintf( stderr, "Erreur lors du redimensionnement de la fenetre.\n");
    exit(EXIT_FAILURE);
  }

  SDL_GLContext GLcontext = SDL_GL_CreateContext(surface);

  #ifdef _WIN32 
  if(glewInit() != 0)
  {
    fprintf( stderr, "Impossible d'initialiser Glew. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  #endif

  glViewport(0, 0, WINDOW_WIDTH , WINDOW_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(1, plateau->Xsplit+1, plateau->Ysplit+1, 1);








  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

  GLuint idGrid = glGenLists(1);
  display_gridList(idGrid);

  int pixelMouseX;
  int pixelMouseY;

  int caseMouseX;
  int caseMouseY;

Uint32 beginMomentLevel = SDL_GetTicks();


/* Boucle principale */
  int loop = 1;
  while(loop) 
  {
    /* Recuperation du temps au debut de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* Placer ici le code de dessin */
    glClear(GL_COLOR_BUFFER_BIT);

   display_drawBoard();
    glCallList(idGrid);

    launchWaves(listMonsters, mapData, mapData->listWaves->next, (SDL_GetTicks() - beginMomentLevel));

    moveAllMonster(listMonsters);
    
    display_drawAllMonsters(listMonsters);
    
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
            reshape(&surface, &GLcontext, e.window.data1, e.window.data2);
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
