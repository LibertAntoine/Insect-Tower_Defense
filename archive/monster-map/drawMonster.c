#include "drawMonster.h"

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

  glBegin(GL_TRIANGLES);
  glVertex2f(X+0.5,Y+0.2);
  glVertex2f(X+0.2,Y+0.8);
  glVertex2f(X+0.8,Y+0.8);
  glEnd();
  
}