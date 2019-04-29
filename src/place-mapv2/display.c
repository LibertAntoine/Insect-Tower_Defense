#include "display.h"

void display_drawCircle(int fillMode)
{
  float angleStep = 2 * M_PI / 360;
  float angleCurrent = 0;

  glPolygonMode(GL_FRONT_AND_BACK, fillMode);

  glBegin(GL_POLYGON);

  while(angleCurrent < 2 * M_PI) {
    glVertex2f(0.5 * cos(angleCurrent), 0.5 * sin(angleCurrent));
    angleCurrent += angleStep;
  }
  glEnd();
}

void display_drawSquare(int fillMode)
{
  glPolygonMode(GL_FRONT_AND_BACK, fillMode);

    glBegin(GL_QUADS);
    glVertex2f(-0.5,0.5);
    glVertex2f(0.5,0.5);
    glVertex2f(0.5,-0.5);
    glVertex2f(-0.5,-0.5);
    glEnd();
}

void display_drawRange(int caseX, int caseY, int range)
{
  glPushMatrix();
  glTranslatef(caseX, caseY, 0);
  glTranslatef(0.5,0.5,0);
  glScalef(2, 2, 1);
  glScalef(range, range, 1);
  glColor3f(1,1,1);
  display_drawCircle(GL_LINE);
  //display_drawCircle(GL_FILL);
  glPopMatrix();
}

void display_gridList(GLuint id)
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

void display_drawSingleTower(int caseX, int caseY, TypeCase type)
{
  glPushMatrix();
  glTranslatef(caseX, caseY, 0);
  glTranslatef(0.5,0.5,0);
  int index_case = case_getCaseIndex(caseX, caseY);
  GeneralType generalType = case_getGeneralConstructionType(type);
  if (type == CHEMIN) {
    glColor3d(0,0,0);
    display_drawSquare(GL_FILL);
  }
  else if (type == TERRAIN) {
    glColor3d(0,0,0);
    display_drawSquare(GL_FILL);
  }
  else {
    switch (type) {
      case LASER:
        glColor3f(0,1,0);
        break;
      case MISSILE:
        glColor3f(1,0,0);
        break;
      case ARMEMENT:
        glColor3f(1,0,0);
        break;
      case MUNITION:
        glColor3d(1,1,0);
        break;
      case RADAR:
        glColor3f(0,0,1);
        break;
      case CENTRALE:
        glColor3f(0,1,0);
        break;
    }
    switch (generalType) {
      case BATIMENT:
        display_drawSquare(GL_FILL);
        break;
      case TOUR:
        display_drawCircle(GL_FILL);
        break;
    }
  }

  glPopMatrix();
}

void display_drawRanges()
{
  int total_cases = plateau->Xsplit * plateau->Ysplit;

  for (int index_case=0; index_case < total_cases; index_case++) {
    TypeCase type = plateau->cases[index_case];
    GeneralType generalType = case_getGeneralConstructionType(type);
    if (generalType == OTHER) {
      continue;
    }
    int caseY = index_case / plateau->Xsplit;
    int caseX = index_case % plateau->Xsplit;
    glPushMatrix();

    int range = 0;
    switch (generalType) {
      case BATIMENT:
        range = tour_getRange(type);
        break;
      case TOUR:
        // TODO: Make range being longer depending on connctions to radars
        range = tour_getPortee(type);
        break;
    }
    display_drawRange(caseX, caseY, range);
    glPopMatrix();

  }
}

void display_drawBoard()
{
  int total_cases = plateau->Xsplit * plateau->Ysplit;

  for (int index_case=0; index_case < total_cases; index_case++) {
    int caseY = index_case / plateau->Xsplit;
    int caseX = index_case % plateau->Xsplit;

    TypeCase type = plateau->cases[index_case];

    display_drawSingleTower(caseX, caseY, type);
  }
  display_drawRanges();
}
