#include <stdio.h>
#include <stdlib.h>

#include "monster.h"
#include "drawMonster.h"
#include "cases.h"

#ifdef WIN32
    #include <GL/glew.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif
#include <SDL/SDL.h>

extern int Xsplit;
extern int Ysplit;

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "Tower_defense";

/* Espace fenetre virtuelle */
static const float GL_VIEW_WIDTH = 200.;
static const float GL_VIEW_HEIGHT = 150.;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


    // Création de la fenêtre
    void reshape(SDL_Window* surface, unsigned int width, unsigned int height) {
        /* Create OpenGl context */

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        
        
        // Double Buffer
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


        surface = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
        if (NULL == surface) {
            fprintf(stderr, "[Error] SDL window is null\n");
        }

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, Xsplit, Ysplit, 0);
    }





int main(int argc, char const *argv[])
{

  /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) 
  {
    fprintf( stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }

  /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
  SDL_Window* surface;
  reshape(surface, WINDOW_WIDTH, WINDOW_HEIGHT);


    int total_cases = Xsplit*Ysplit;
    int cases[100];
    for (int i=0; i<Xsplit*Ysplit; i++) {
        cases[i] = 0;
    }

  int mouse[2];
  SDL_GetMouseState(mouse, mouse+1);


  int loop = 1;
  while(loop) 
  {
    /* Recuperation du temps au debut de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* Placer ici le code de dessin */
    glClear(GL_COLOR_BUFFER_BIT);
 


    int caseMouseX;
    int caseMouseY;
    case_getCaseCoordFromPixels(mouse[0], mouse[1], &caseMouseX, &caseMouseY, WINDOW_WIDTH, WINDOW_HEIGHT);


    glColor3d(255,0,0);
  glBegin(GL_QUADS);
  glVertex2f(0.2,0.2);
  glVertex2f(0.8,0.2);
  glVertex2f(0.8,0.8);
  glVertex2f(0.2,0.8);
  glEnd();

    //SDL_GL_SwapWindow(surface);

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
  }
        /* Redimensionnement fenetre */
        case SDL_WINDOWEVENT_RESIZED:
          reshape(surface, e.resize.w, e.resize.h);
          break;

  }
  /* Liberation des ressources associees a la SDL */

  SDL_Quit();

  return EXIT_SUCCESS;
}
