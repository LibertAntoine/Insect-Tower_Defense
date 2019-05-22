#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structures.h"
#include "SDLConfig.h"
#include "animation.h"

int main()
{
  sdlConfig_initSDL();
  SDL_Window* surface;
  SDL_GLContext GLcontext = NULL;
  sdlConfig_reshape(&surface, &GLcontext, WINDOW_WIDTH, WINDOW_HEIGHT);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

  Uint32 beginMomentLevel = SDL_GetTicks();

  SpriteImage *skeleton_image = animation_loadSprite("sprite.png", 9, 4, 200);

  SpriteTexture* skeleton = animation_loadTexture(skeleton_image);

  int loop = 1;
  while(loop) {
    Uint32 startTime = SDL_GetTicks();

    glClearColor(1,0,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    animation_displaySprite(skeleton);

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
        // mouse click
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

