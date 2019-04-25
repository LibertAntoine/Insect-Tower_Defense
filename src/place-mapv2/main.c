#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Custom header files
#include "player.h"
#include "cases.h"
#include "display.h"
#include "tour.h"

static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "test";
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


void reshape(Plateau *plateau, SDL_Window** surface, SDL_GLContext *GLcontext, unsigned int width, unsigned int height) {
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
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, plateau->Xsplit, plateau->Ysplit, 0);
}


int main(int argc, char** argv) 
{
  /* Initialisation de la SDL */
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf( stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }

  int tmp_casesX = 10;
  int tmp_casesY = 10;

  Plateau plateau;
  case_initPlateau(&plateau, tmp_casesX, tmp_casesY);

  /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
  SDL_Window* surface;
  SDL_GLContext GLcontext = NULL;
  reshape(&plateau, &surface, &GLcontext, WINDOW_WIDTH, WINDOW_HEIGHT);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);



  GLuint idGrid = glGenLists(1);
  display_gridList(&plateau, idGrid);

  int total_cases = plateau.Xsplit * plateau.Ysplit;
  int *tours = calloc(total_cases, sizeof(Tour*));
  // NOTE: Verify that allocation worked



  Etat joueur;
  joueur.argent = 1000;
  joueur.action = ADD;
  joueur.type = LASER;


  int pixelMouseX;
  int pixelMouseY;

  int caseMouseX;
  int caseMouseY;


  int loop = 1;
  while(loop) 
  {
    Uint32 startTime = SDL_GetTicks();

    glClear(GL_COLOR_BUFFER_BIT);

    display_drawAllTowers(&plateau);
    glCallList(idGrid);



    /* Echange du front et du back buffer : mise a jour de la fenetre */
    SDL_GL_SwapWindow(surface);

    /* Boucle traitant les evenements */
    SDL_Event e;
    while(SDL_PollEvent(&e)) 
    {
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

      switch(e.type) 
      {
        case SDL_MOUSEBUTTONDOWN:
          SDL_GetMouseState(&pixelMouseX, &pixelMouseY);
          case_getCaseCoordFromPixels(&plateau, pixelMouseX, pixelMouseY, &caseMouseX, &caseMouseY, WINDOW_WIDTH, WINDOW_HEIGHT);
          printf("\n\nmouse X -> %d\nmouse Y -> %d\n", caseMouseX, caseMouseY);

          switch(joueur.action) {
            case ADD:
              if(case_isEmpty(&plateau, caseMouseX, caseMouseY)) {
                int case_type = case_getType(&plateau, caseMouseX, caseMouseY);
                if(player_acheteTour(&joueur, case_type)) {
                  printf("Ajout de tour avec succes\n");
                }
                else {
                  printf("Vous n'avez pas assez\n");
                }
              }
              printf("invoking add\n");
              break;
            case GETINFO:
              printf("invoking info\n");
              break;
            case REMOVE:
              printf("invoking remove\n");
              break;
          }
          break;

        case SDL_WINDOWEVENT:
          if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
            reshape(&plateau, &surface, &GLcontext, e.window.data1, e.window.data2);
          }
          break;

        case SDL_KEYDOWN:
          printf("Current ");
          player_afficherEtat(&joueur);
          printf(" // ");
          player_afficherAction(&joueur);
          printf("   --->    ");
          switch(e.key.keysym.sym) {
            case 'r':
              joueur.type = RADAR;
              break;
            case 'a':
              joueur.type = ARMEMENT;
              break;
            case 'c':
              joueur.type = CENTRALE;
              break;
            case 'm':
              joueur.type = MUNITION;
              break;

            case '1':
              joueur.type = LASER;
              break;
            case '2':
              joueur.type = MISSILE;
              break;

            case 'p':
              joueur.action = ADD;
              break;
            case 'i':
              joueur.action = GETINFO;
              break;
            case 'x':
              joueur.action = REMOVE;
              break;
          }
          player_afficherEtat(&joueur);
          printf(" // ");
          player_afficherAction(&joueur);
          printf("\n");

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
