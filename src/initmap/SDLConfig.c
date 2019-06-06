#include "SDLConfig.h"

void sdlConfig_initSDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    fprintf( stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
}

void sdlConfig_reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
{

  SDL_Surface* surface_temp = SDL_SetVideoMode(width, height, 8, SDL_OPENGL);
  SDL_ShowCursor(SDL_DISABLE);

  if(NULL == surface_temp) 
  {
    fprintf( stderr, "Erreur lors du redimensionnement de la fenetre.\n");
    exit(EXIT_FAILURE);
  }
  *surface = surface_temp;

  /*
  if (*GLcontext == NULL) {
    *GLcontext = SDL_GL_CreateContext(*surface);
  }
  */

  SDL_WM_SetCaption(WINDOW_TITLE, NULL);

  #ifdef _WIN32 
  if(glewInit() != 0)
  {
    fprintf( stderr, "Impossible d'initialiser Glew. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  #endif

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(1, width, height, 1);
}
