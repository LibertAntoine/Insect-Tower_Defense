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
  float PDV = monster->PDV;
  float maxPDV = plateau->listMonsters->dataMonsters[monster->type]->PDV;
  float percentPDV = 1 / maxPDV * PDV;
  glPushMatrix();
  glTranslatef(monster->x, monster->y, 0);

  glPushMatrix();
  glRotatef(angle, 0, 0, 1);
  display_drawTriangle(GL_FILL);
  glPopMatrix();

  // NOTE: affiche la vie que si le monstre est vivant et qu'il a subi des dommages
  if(monster->status == ALIVE && percentPDV < 1) {
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

int display_drawAllMonsters()
{
  if(plateau->listMonsters->firstMonster == NULL) {
    return 0;
  }

  Monster* currentMonster = plateau->listMonsters->firstMonster;
  while (currentMonster != NULL) {  
      display_drawSingleMonster(currentMonster);
      if (plateau->monster_hover == currentMonster) {
        display_drawItineraire(currentMonster);
      }
      currentMonster = currentMonster->next;
  }
  return 0;
}


int display_drawAllProjectiles()
{
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

void display_drawSingleProjectile(Projectile* projectile)
{
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
  if(monster->itineraire->next->next != NULL) {
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
}

void display_setDrawingZone(GUI *section)
{
  int X = 0;
  int Y = 0;
  gui_getAbsoluteCoordinates(section, &X, &Y);

  glViewport(X, bodyGUI->dimensions->height - Y - section->dimensions->height, section->dimensions->width, section->dimensions->height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(0, section->dimensions->width, section->dimensions->height, 0);
  glMatrixMode(GL_MODELVIEW);
}

void display_drawZoneBasedOnGUI(GUI *section)
{
  display_setDrawingZone(section);

  glBegin(GL_QUADS);
  glVertex2f(0, 0);
  glVertex2f(0, section->dimensions->height);
  glVertex2f(section->dimensions->width, section->dimensions->height);
  glVertex2f(section->dimensions->width, 0);
  glEnd();

  glColor3f(1,0,0);
  Button *button = section->buttons;
  while (button != NULL) {
    display_drawSingleButton(button);
    button = button->next;
  }

  display_setDrawingZone(bodyGUI);
}

void display_drawSingleButton(Button *button)
{
  int half_width = button->dimensions->width / 2;
  int half_height = button->dimensions->height / 2;

  glPushMatrix();
  glTranslatef(button->dimensions->x, button->dimensions->y, 0);

  glBegin(GL_QUADS);
  glVertex2f(-half_width,-half_height);
  glVertex2f(half_width,-half_height);
  glVertex2f(half_width, half_height);
  glVertex2f(-half_width, half_height);
  glEnd();

  glPopMatrix();
}

void display_top()
{
  glColor3f(1,1,0);
  display_drawZoneBasedOnGUI(topGUI);
}

void display_bottom()
{
  glColor3f(1,0,1);

  display_drawZoneBasedOnGUI(bottomGUI);
}

void display_left()
{
  glColor3f(1,0,0);
  glBegin(GL_QUADS);
  glVertex2f(0,100);
  glVertex2f(0,500);
  glVertex2f(300,500);
  glVertex2f(300,100);
  glEnd();

}

void display_window()
{
    display_top();
    display_left();
    display_bottom();
}

void display_game(GUI *plateau_gui, GLuint idMap, GLuint idGrid)
{
  // TODO: mettre des valeurs dynamiques
  glViewport(300, 100, 500, 400);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(1, plateau->Xsplit+1, plateau->Ysplit+1, 1);
  glMatrixMode(GL_MODELVIEW);

  glCallList(idMap);
  glCallList(idGrid);

  display_drawBoard();

  display_drawAllMonsters();
  display_drawAllProjectiles();

  glViewport(0, 0, 800, 600);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 800, 600, 0);
  glMatrixMode(GL_MODELVIEW);
}
