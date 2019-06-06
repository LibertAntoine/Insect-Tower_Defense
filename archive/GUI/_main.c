#ifdef _WIN32
  #include <GL/glew.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

#include <SDL2/SDL.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structures.h"
#include "SDLConfig.h"
#include "display.h"
#include "cases.h"
#include "GUI.h"
#include "mouse.h"

int Xsplit = 6;
int Ysplit = 5;

GUI *bodyGUI; //variable globale de l'interface
GUI *plateauGUI;
GUI *bottomGUI;
GUI *topGUI;

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

    display_bottom();

    display_game(plateauGUI, Xsplit, Ysplit);


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
        mouse_handleClick();
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
