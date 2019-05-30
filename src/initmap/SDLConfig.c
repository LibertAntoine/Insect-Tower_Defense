#include "SDLConfig.h"

void sdlConfig_initSDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
  {
    fprintf( stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
}

void sdlConfig_reshape(SDL_Window** surface, SDL_GLContext *GLcontext, unsigned int width, unsigned int height)
{

  SDL_Window* surface_temp = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  SDL_ShowCursor(SDL_DISABLE);

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

  #ifdef _WIN32 
  if(glewInit() != 0)
  {
    fprintf( stderr, "Impossible d'initialiser Glew. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
  #endif

  glViewport(0, 0, window_width, window_height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(1, window_width, window_height, 1);
}
