#ifndef DISPLAY_H_
#define DISPLAY_H_

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include "cases.h"

/**
 * @brief Génère la grille visuelle du plateau (séparations et centres ce chaque case)
 * @param[out] Liste d'affichage OpenGL.
 */
void display_gridList(GLuint id);
void display_drawSingleTower(int X, int Y, TypeCase type);
void display_drawAllTowers(int cases[]);

#endif //DISPLAY_H_

