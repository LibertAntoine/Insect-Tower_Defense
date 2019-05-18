#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structures.h"
#include "SDLConfig.h"
#include "display.h"
#include "cases.h"
#include "GUI.h"

int Xsplit = 6;
int Ysplit = 5;

GUI *bodyGUI; //variable globale de l'interface

int main()
{
  sdlConfig_initSDL();
  SDL_Window* surface;
  SDL_GLContext GLcontext = NULL;
  sdlConfig_reshape(&surface, &GLcontext, WINDOW_WIDTH, WINDOW_HEIGHT);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

  Uint32 beginMomentLevel = SDL_GetTicks();

  gui_init();

  int loop = 1;
  while(loop) {
    Uint32 startTime = SDL_GetTicks();

    glClear(GL_COLOR_BUFFER_BIT);

    display_top();
    display_left();

    /* Interface Bottom */
    Div interfaceBottom;
    interfaceBottom.x = 0;
    interfaceBottom.y = 0;
    interfaceBottom.width = 800;
    interfaceBottom.height = 100;
    display_bottom(&interfaceBottom);

    display_game(Xsplit, Ysplit);


    SDL_GL_SwapWindow(surface);

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }

      if(e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE)) {
        loop = 0; 
        break;
      }
      if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        int caseX, caseY;

        /*div plateau infos*/
        Div interfacePlateau;
        interfacePlateau.x = 300;
        interfacePlateau.y = 100;
        interfacePlateau.width = 500;
        interfacePlateau.height = 400;

        if (mouse_inPlateau(mouseX, mouseY, &interfacePlateau)) {
          get_cases(&caseX, &caseY, mouseX, mouseY, &interfacePlateau);
          printf("%d %d\n", caseX, caseY);
        }

        // TODO click BTN
      }
    }




    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) 
    {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  SDL_Quit();

  return EXIT_SUCCESS;
}
