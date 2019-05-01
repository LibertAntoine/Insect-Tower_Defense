#include "display.h"

void display_gridList(GLuint id)
{
  glNewList(id, GL_COMPILE);
  // ---

  glColor3d(0,255,0);
  glLineWidth(3);

  for (int column=0; column<Xsplit; column++) {
    glBegin(GL_LINES);
    glVertex2d(column, 0);
    glVertex2d(column, Ysplit);
    glEnd();
  }
  glColor3d(255,255,0);
  for (int line=0; line<Ysplit; line++) {
    glBegin(GL_LINES);
    glVertex2d(0, line);
    glVertex2d(Xsplit, line);
    glEnd();
  }

  /* Déssine les points au centre des cases */
  glColor3d(255,0,255);
  glPointSize(5);
  glBegin(GL_POINTS);
  for (int index_case=0; index_case<Xsplit*Ysplit; index_case++) {
    float centerY = index_case / Xsplit + 0.5;
    float centerX = index_case % Xsplit + 0.5;
    glVertex2f(centerX, centerY);
  }
  glEnd();

  // ---
  glEndList();
}

void display_drawSingleTower(int X, int Y, TypeCase type)
{
  switch(type) {
    case CENTRALE:
      glColor3d(0,0,255);
      break;
    case TOWER_ACTIVE:
      glColor3d(0,255,0);
      break;
    case TOWER_INACTIVE:
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

void display_drawAllTowers(int cases[]) 
{
  int total_cases = Xsplit*Ysplit;

  for (int i=0; i < total_cases; i++) {
    int Y = i / Xsplit;
    int X = i % Xsplit;

    TypeCase towerType = cases[i];
    display_drawSingleTower(X, Y, towerType);
  }
}

