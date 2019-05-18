#include "display.h"

void display_boardGrid(int Xsplit, int Ysplit)
{
  glColor3f(0,0,1);
  glBegin(GL_LINES);
  for (int i = 1; i < Xsplit; i++) {
    glVertex2f(i, 0);
    glVertex2f(i, 5);
  }
  for (int i = 1; i < Ysplit; i++) {
    glVertex2f(0, i);
    glVertex2f(6, i);
  }
  glEnd();
}

void display_game(int Xsplit, int Ysplit)
{
  // glViewport lowerleft corner from bottom left, + shift x , y
  glViewport(300, 100, 500, 400);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 6, 5, 0);
  glMatrixMode(GL_MODELVIEW);

  glColor3f(1,1,1);


  //FOND
  glBegin(GL_QUADS);
  glVertex2f(0, 0);
  glVertex2f(0, 5);
  glVertex2f(6, 5);
  glVertex2f(6,0);
  glEnd();

  display_boardGrid(Xsplit, Ysplit);

  glViewport(0, 0, 800, 600);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 800, 600, 0);
  glMatrixMode(GL_MODELVIEW);
}

void display_top()
{
  glColor3f(1,1,0);

  glBegin(GL_QUADS);
  glVertex2f(0,0);
  glVertex2f(0,100);
  glVertex2f(800,100);
  glVertex2f(800,0);
  glEnd();
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

void display_towerbtns(Div *bottom)
{
  /* balancer dans une fonction */
  glViewport(bottom->x, bottom->y, bottom->width, bottom->height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, bottom->width, bottom->height, 0);
  glMatrixMode(GL_MODELVIEW);

  glColor3f(1,0,0);
  glPushMatrix();
  glTranslatef(700, 50, 0);
  glBegin(GL_QUADS);
  glVertex2f(-25,-25);
  glVertex2f(25,-25);
  glVertex2f(25, 25);
  glVertex2f(-25, 25);
  glEnd();
  glPopMatrix();


  glViewport(0, 0, 800, 600);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 800, 600, 0);
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

void display_setDrawingZone(GUI *section)
{
  int position_x = 0;
  int position_y = 0;
  gui_getAbsolutePosistionXY(section, &position_x, &position_y);

  glViewport(position_x, bodyGUI->dimensions->height - position_y - section->dimensions->height, section->dimensions->width, section->dimensions->height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(0, section->dimensions->width, section->dimensions->height, 0);
  glMatrixMode(GL_MODELVIEW);
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

void display_bottom(Div *bottom)
{
  glColor3f(1,0,1);

  display_drawZoneBasedOnGUI(bodyGUI->childen);

  /*
  glBegin(GL_QUADS);
  glVertex2f(0,500);
  glVertex2f(0,600);
  glVertex2f(800,600);
  glVertex2f(800,500);
  glEnd();

  display_towerbtns(bottom);
  */
}
