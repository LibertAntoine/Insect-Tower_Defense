#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "structures.h"
#include "SDLConfig.h"

int main()
{
  sdlConfig_initSDL();
  SDL_Window* surface;
  SDL_GLContext GLcontext = NULL;
  sdlConfig_reshape(&surface, &GLcontext, WINDOW_WIDTH, WINDOW_HEIGHT);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

  Uint32 beginMomentLevel = SDL_GetTicks();


  SDL_Surface* sprite = IMG_Load("image.ppm");
  GLuint sprite_texture;
  glGenTextures(1, &sprite_texture);

  glBindTexture(GL_TEXTURE_2D, sprite_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sprite->w, sprite->h, 0, GL_RGB, GL_UNSIGNED_BYTE, sprite->pixels);
  glBindTexture(GL_TEXTURE_2D, 0);


  int loop = 1;
  while(loop) {
    Uint32 startTime = SDL_GetTicks();

    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    /* Allow alpha channel
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    */

    glColor4f(0,1,0, 0.5);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sprite_texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(0, 0);
    glTexCoord2f(1, 0);
    glVertex2f(400, 0);
    glTexCoord2f(1, 1);
    glVertex2f(400, 300);
    glTexCoord2f(0, 1);
    glVertex2f(0, 300);
    glEnd();

    //glDisable(GL_ALPHA_TEST);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

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

