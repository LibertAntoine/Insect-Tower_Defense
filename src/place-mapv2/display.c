#include "display.h"

void display_gridList(Plateau *plateau, GLuint id)
{
  glNewList(id, GL_COMPILE);
  glColor3d(0,255,0);
  glLineWidth(3);

  for (int i=0; i<plateau->Xsplit; i++) {
    glBegin(GL_LINES);
    glVertex2d(i, 0);
    glVertex2d(i, plateau->Ysplit);
    glEnd();
  }
  glColor3d(255,255,0);
  for (int i=0; i<plateau->Ysplit; i++) {
    glBegin(GL_LINES);
    glVertex2d(0, i);
    glVertex2d(plateau->Xsplit, i);
    glEnd();
  }

  glColor3d(255,0,255);
  glPointSize(5);
  glBegin(GL_POINTS);
  for (int i=0; i<plateau->Xsplit*plateau->Ysplit; i++) {
    float centerY = i / plateau->Xsplit + 0.5;
    float centerX = i % plateau->Xsplit + 0.5;
    glVertex2f(centerX, centerY);
  }
  glEnd();
  glEndList();
}

void display_drawSingleTower(int X, int Y, TypeCase type)
{
  switch(type) {
    /*
    case CENTRALE:
      glColor3d(0,0,255);
      break;
    case TOWER_ACTIVE:
      glColor3d(0,255,0);
      break;
    case TOWER_INACTIVE:
      glColor3d(255,0,0);
      break;
     */
    default:
      glColor3d(0,0,0);
      break;
  }

  glBegin(GL_QUADS);
  glVertex2f(X+0.2,Y+0.2);
  glVertex2f(X+0.8,Y+0.2);
  glVertex2f(X+0.8,Y+0.8);
  glVertex2f(X+0.2,Y+0.8);
  glEnd();
  
}

void display_drawAllTowers(Plateau *plateau) 
{
  int total_cases = plateau->Xsplit * plateau->Ysplit;

  for (int i=0; i < total_cases; i++) {
    int Y = i / plateau->Xsplit;
    int X = i % plateau->Xsplit;

    TypeCase towerType = plateau->cases[i];
    display_drawSingleTower(X, Y, towerType);
  }
}
