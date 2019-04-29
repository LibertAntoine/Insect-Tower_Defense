#include "drawMonster.h"


void display_gridList(GLuint id)
{
  glNewList(id, GL_COMPILE);
  glColor3d(0,255,0);
  glLineWidth(3);

  for (int i=0; i<Xsplit; i++) {
    glBegin(GL_LINES);
    glVertex2d(i, 0);
    glVertex2d(i, Ysplit);
    glEnd();
  }
  glColor3d(255,255,0);
  for (int i=0; i<Ysplit; i++) {
    glBegin(GL_LINES);
    glVertex2d(0, i);
    glVertex2d(Xsplit, i);
    glEnd();
  }

  glColor3d(255,0,255);
  glPointSize(5);
  glBegin(GL_POINTS);
  for (int i=0; i<Xsplit*Ysplit; i++) {
    float centerY = i / Xsplit + 0.5;
    float centerX = i % Xsplit + 0.5;
    glVertex2f(centerX, centerY);
  }
  glEnd();
  glEndList();
}

void display_drawSingleMonster(int X, int Y, TypeCase type)
{
  switch(type) {
    case SOLDER:
      glColor3d(0,0,255);
      break;
    case FIRST_SOLDER:
      glColor3d(0,255,0);
      break;
    case GENERAL:
      glColor3d(255,0,0);
      break;
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