#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cases.h"
#include "display.h"

extern int Xsplit;
extern int Ysplit;

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
  gluOrtho2D(0, Xsplit, Ysplit, 0);
}


int main(int argc, char** argv) 
{
  /* Initialisation de la SDL */
  if(SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    fprintf( stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }

  /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
  SDL_Window* surface;
  SDL_GLContext GLcontext = NULL;
  reshape(&surface, &GLcontext, WINDOW_WIDTH, WINDOW_HEIGHT);

  int mouse[2];
  SDL_GetMouseState(mouse, mouse+1);

  GLuint idGrid = glGenLists(1);
  display_gridList(idGrid);

  int total_cases = Xsplit*Ysplit;
  int cases[total_cases];
  for (int i=0; i<Xsplit*Ysplit; i++) {
    cases[i] = 0;
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

  /* Boucle principale */
  int loop = 1;
  while(loop) 
  {
    /* Recuperation du temps au debut de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* Placer ici le code de dessin */
    glClear(GL_COLOR_BUFFER_BIT);

    display_drawAllTowers(cases);
    glCallList(idGrid);

    int caseMouseX;
    int caseMouseY;
    case_getCaseCoordFromPixels(mouse[0], mouse[1], &caseMouseX, &caseMouseY, WINDOW_WIDTH, WINDOW_HEIGHT);
    display_drawSingleTower(caseMouseX, caseMouseY, CENTRALE);

    /* Echange du front et du back buffer : mise a jour de la fenetre */
    SDL_GL_SwapWindow(surface);

    /* Boucle traitant les evenements */
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

      switch(e.type) 
      {
        case SDL_MOUSEBUTTONDOWN:
          SDL_GetMouseState(mouse, mouse+1);

          if (case_isEmpty(caseMouseX, caseMouseY, cases)) {
            printf("mouse X -> %d\nmouse Y -> %d\n\n", caseMouseX, caseMouseY);
            if (e.button.button == SDL_BUTTON_LEFT) {
              case_addTower(caseMouseX, caseMouseY, cases, TOWER_INACTIVE);
            }
            else if (e.button.button == SDL_BUTTON_RIGHT) {
              case_addTower(caseMouseX, caseMouseY, cases, CENTRALE);
            }
            int central_range = 2;
            case_activateAllTowers(cases, central_range);
          }
          break;

        case SDL_MOUSEMOTION:
          SDL_GetMouseState(mouse, mouse+1);
          printf("mouse X -> %d\nmouse Y -> %d\n\n", mouse[0], mouse[1]);

          break;

        case SDL_WINDOWEVENT:
          if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
            reshape(&surface, &GLcontext, e.window.data1, e.window.data2);
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
