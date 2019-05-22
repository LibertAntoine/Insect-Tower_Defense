#include "display.h"

// TODO: fix circle range bugs.
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

void display_drawTriangle(int fillMode)
{
  glPolygonMode(GL_FRONT_AND_BACK, fillMode);

  glBegin(GL_TRIANGLES);
  glVertex2f(0, -0.3);
  glVertex2f(0.3, 0.3);
  glVertex2f(-0.3, 0.3); 
  glEnd();
}

void display_drawTargetRange(int caseX, int caseY, int range)
{
  glPushMatrix();
  glTranslatef(caseX, caseY, 0);
  glTranslatef(0.5,0.5,0);
  glScalef(2, 2, 1);
  glScalef(range, range, 1);
  glColor3f(1,1,1);
  display_drawCircle(GL_LINE);
  glPopMatrix();
}

void display_drawSingleMonster(Monster* monster)
{
  if (monster->type == SOLDER) {
    if(monster->status == ALIVE) {
      glColor3f(0,0,0.5);
    } else {
      glColor3f(0,0,0);
    }
  } else if (monster->type == HUGE_SOLDER) {
    if(monster->status == ALIVE) {
      glColor3f(1,1,1);
    } else {
      glColor3f(0,0,0);
    }
  } else if (monster->type == GERERAL) {
    if(monster->status == ALIVE) {
      glColor3f(0,1,0);
    } else {
      glColor3f(0,0,0);
    }
  } else if (monster->type == BOSS) {
    if(monster->status == ALIVE) {
      glColor3f(0,1,1);
    } else {
      glColor3f(0,0,0);
    }
  }


  float angle = 0;
  if (monster->orientation == HAUT) {
    angle = 0;
  } else if (monster->orientation == BAS) {
    angle = 180;
  } else if (monster->orientation == GAUCHE) {
    angle = -90;
  } else if (monster->orientation == DROITE) {
    angle = 90;
  }
  // TODO: Debug mauvais PDV.
  float PDV = monster->PDV;
  float maxPDV = plateau->listMonsters->dataMonsters[monster->type]->PDV;
  float percentPDV = 1 / maxPDV * PDV;
  glPushMatrix();
  glTranslatef(monster->x, monster->y, 0);

  glPushMatrix();
  glRotatef(angle, 0, 0, 1);
  display_drawTriangle(GL_FILL);
  glPopMatrix();

  if(monster->status == ALIVE) {
      glPushMatrix();
      glScalef(0.8, 0.3, 1);
      glTranslatef(0, 0.9, 0);
      display_drawMonsterLife(percentPDV);
      glPopMatrix();
  }
  glPopMatrix();
}

void display_drawMonsterLife(float PDV)
{
  glPushMatrix();
  glScalef(1,0.5,1);
  glColor3f(1,0,0);
  display_drawSquare(GL_FILL);
  glColor3f(0,1,0);
  glTranslatef(-((1-PDV)/2),0,0);
  glScalef(PDV,1,1);
  display_drawSquare(GL_FILL);
  glPopMatrix();
}

int display_drawAllMonsters() {
  if(plateau->listMonsters->firstMonster == NULL) {
    return 0;
  }

  Monster* currentMonster = plateau->listMonsters->firstMonster;
  while (currentMonster != NULL) {  
      display_drawSingleMonster(currentMonster);
      display_drawItineraire(currentMonster);
      currentMonster = currentMonster->next;
  }
  return 0;

}


int display_drawAllProjectiles() {
  if(plateau->listProjectiles->next == NULL) {
    return 0;
  }
  Projectile* currentProjectile = plateau->listProjectiles->next;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  while (currentProjectile != NULL) {  
    display_drawSingleProjectile(currentProjectile);
    currentProjectile = currentProjectile->next;

  }
  return 0;
}

void display_drawSingleProjectile(Projectile* projectile) {
  glColor3d(255,0,255);

  glBegin(GL_TRIANGLES);
  glVertex2f(projectile->x, projectile->y-0.1);
  glVertex2f(projectile->x+0.1, projectile->y+0.1);
  glVertex2f(projectile->x-0.1, projectile->y+0.1); 
  glEnd();

}

void display_mapList(GLuint id)
{
  glNewList(id, GL_COMPILE);

  /*
     glPushMatrix();
     glColor3f(1,0,1);
     glTranslatef(1.5, 1.5, 0);
     display_drawCircle(GL_FILL);
     glPopMatrix();
   */

  for (int index_case=0; index_case < plateau->Xsplit*plateau->Ysplit; index_case++) {
    int caseX;
    int caseY;
    case_getCasePosition(index_case, &caseX, &caseY);
    TypeCase type = case_getType(caseX, caseY);

    switch (type) {
      case CHEMIN:
        glColor3f(1,0,1);
        break;
      case NOEUD:
        glColor3f(1,0,0);
        break;
      case ENTREE:
        glColor3d(0,0,1);
        break;
      case SORTIE:
        glColor3f(0,1,0);
        break;
      default:
        glColor3f(0,0,0);
        break;
    }

    glPushMatrix();
    glTranslatef(caseX, caseY, 0);
    glTranslatef(1.5, 1.5, 0);
    display_drawSquare(GL_FILL);
    glPopMatrix();

  }

  glEndList();
}

void display_gridList(GLuint id)
{
  glNewList(id, GL_COMPILE);
  glColor3d(0,255,0);
  glLineWidth(3);

  for (int i=0; i<plateau->Xsplit; i++) {
    glBegin(GL_LINES);
    glVertex2d(i+1, 1);
    glVertex2d(i+1, plateau->Ysplit+1);
    glEnd();
  }
  glColor3d(255,255,0);
  for (int i=0; i<plateau->Ysplit; i++) {
    glBegin(GL_LINES);
    glVertex2d(1, i+1);
    glVertex2d(plateau->Xsplit+1, i+1);
    glEnd();
  }

  glColor3d(255,0,255);
  glPointSize(5);
  glBegin(GL_POINTS);
  for (int i=0; i<plateau->Xsplit*plateau->Ysplit; i++) {
    float centerY = i / plateau->Xsplit + 1.5;
    float centerX = i % plateau->Xsplit + 1.5;
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
    //display_drawSquare(GL_FILL);
  }
  else if (type == TERRAIN) {
    glColor3d(0,0,0);
    //display_drawSquare(GL_FILL);
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

/*
   void display_drawAllTowers()
   {
   int total_cases = plateau->Xsplit * plateau->Ysplit;

   for (int i=0; i < total_cases; i++) {
   int Y = i / plateau->Xsplit;
   int X = i % plateau->Xsplit;

   TypeCase towerType = plateau->cases[i];
   display_drawSingleTower(X, Y, towerType);
   }
   }
 */

void display_drawAllTargetRanges()
{
  int total_cases = plateau->Xsplit * plateau->Ysplit;

  for (int index_case=0; index_case < total_cases; index_case++) {
    TypeCase type = plateau->cases[index_case];
    GeneralType generalType = case_getGeneralConstructionType(type);
    if (generalType == OTHER) {
      continue;
    }
    int caseY, caseX;
    case_getCasePosition(index_case, &caseX, &caseY);
    glPushMatrix();

    int range = 0;
    switch (generalType) {
      case BATIMENT:
        range = tour_getRange(type);
        break;
      case TOUR:
        // TODO: Faire en sorte d'allonger la portée grâce au nombre de radars connectés 
        range = tour_getPortee(type);
        break;
    }
    display_drawTargetRange(caseX, caseY, range);
    glPopMatrix();

  }
}

void display_drawBoard()
{
  int total_cases = plateau->Xsplit * plateau->Ysplit;

  for (int index_case=0; index_case < total_cases; index_case++) {
    int caseY, caseX;
    case_getCasePosition(index_case, &caseX, &caseY);
    TypeCase type = plateau->cases[index_case];

    display_drawSingleTower(caseX, caseY, type);
  }
  display_drawAllTargetRanges();
}

void display_drawItineraire(Monster* monster)
{
  glColor3f(1,1,1);
  glBegin(GL_LINES);
  glVertex2f(monster->x, monster->y);
  glVertex2f(monster->itineraire->next->next->node->x, monster->itineraire->next->next->node->y);

  Etape* currentEtape = monster->itineraire->next->next;
  while(currentEtape->next != NULL) {
    glVertex2f(currentEtape->node->x, currentEtape->node->y);
    glVertex2f(currentEtape->next->node->x, currentEtape->next->node->y);
    currentEtape = currentEtape->next;
  }
  glEnd();
}
