#ifdef WIN32
    #include <GL/glew.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>

#include <math.h>

#include "draw.h"


/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 600;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "TD04";

/* Espace fenetre virtuelle */
static const float GL_VIEW_WIDTH = 200.;
static const float GL_VIEW_HEIGHT = 200.;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;


int main(int argc, char** argv) {


    if (-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "[Error] SDL not init\n");
        return EXIT_FAILURE;
    }


    /* Create OpenGl context */
	SDL_Window* surface;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	
	
    // Double Buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    float pi = M_PI;

	surface = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (NULL == surface) {
        fprintf(stderr, "[Error] SDL window is null\n");
        return EXIT_FAILURE;
    }

    printf("Glu version %s\n", gluGetString(GLU_VERSION));

	SDL_GLContext contexteOpenGL = SDL_GL_CreateContext(surface);


glewInit();

    GLuint idLogo = glGenLists(1);
    glNewList(idLogo, GL_COMPILE);
    SDL_Surface* image = IMG_Load("doc/logo_imac.jpg");
    if(image == NULL) {
        printf("[Error] Logo not init\n");
    }
    glEndList();



    glViewport(0, 0,  WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(
        -GL_VIEW_WIDTH / 2, GL_VIEW_WIDTH / 2, 
        -GL_VIEW_HEIGHT / 2, GL_VIEW_HEIGHT / 2);


    glGenTextures(1, &idLogo);
    glBindTexture(GL_TEXTURE_2D, idLogo);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(
    GL_TEXTURE_2D , 0, GL_RGB,
    image->w, image->h, 0,
    GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    
    /* Main loop */
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
    

	

    const Uint32 TARGET_FRAMERATE_MS = 1000 / 60;
    int loop = 1;
    while (loop) {   
        Uint32 startTime = SDL_GetTicks();

        glClear(GL_COLOR_BUFFER_BIT);

    
        glPushMatrix();

        glScalef(100.,100.,0.);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, idLogo);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f( 0.5 , -0.5);
            glTexCoord2f(0,0);
            glVertex2f( 0.5 , 0.5);
            glTexCoord2f(0,1);
            glVertex2f( -0.5 , 0.5);
            glTexCoord2f(1,1);
            glVertex2f( -0.5 , -0.5);
            glTexCoord2f(1,0);
            glVertex2f( 0.5 , -0.5);
          glEnd(); 
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

        
                   

        /* Update window */
        SDL_GL_SwapWindow(surface);
        
        /* Handle events 
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
            
            switch (e.type) {
                case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    break;

                default:
                    break;
            }
        }

        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Pause the program if the framerate is too low */
        /*if (elapsedTime < TARGET_FRAMERATE_MS) 
        {
            SDL_Delay(TARGET_FRAMERATE_MS - elapsedTime);
        }
*/
        
    }
    
    SDL_FreeSurface(image);
    glDeleteTextures(1, &idLogo);
    SDL_Quit();

    return EXIT_SUCCESS;
}
