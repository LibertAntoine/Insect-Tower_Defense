#include "drawMonster.h"

void display_drawSingleMonster(Monster* monster)
{
  if (monster->type = SOLDER) {
    glColor3d(0,0,255);
  } else if (monster->type = HUGE_SOLDER) {
    glColor3d(255,0,0);
  } else if (monster->type = GERERAL) {
    glColor3d(0,255,0);
  } else if (monster->type = BOSS) {
    glColor3d(0,255,255);
  }

  glBegin(GL_TRIANGLES);
  if (monster->orientation == HAUT) {
      glVertex2f(monster->x, monster->y-0.3);
      glVertex2f(monster->x+0.3, monster->y+0.3);
      glVertex2f(monster->x-0.3, monster->y+0.3); 
  } else if (monster->orientation == BAS) {
      glVertex2f(monster->x, monster->y+0.3);
      glVertex2f(monster->x-0.3, monster->y-0.3);
      glVertex2f(monster->x+0.3, monster->y-0.3); 
  } else if (monster->orientation == GAUCHE) {
      glVertex2f(monster->x-0.3, monster->y);
      glVertex2f(monster->x+0.3, monster->y+0.3);
      glVertex2f(monster->x+0.3, monster->y-0.3); 
  } else if (monster->orientation == DROITE) {
      glVertex2f(monster->x+0.3, monster->y);
      glVertex2f(monster->x-0.3, monster->y+0.3);
      glVertex2f(monster->x-0.3, monster->y-0.3); 
  }
  glEnd();
  
}

int display_drawMonsters(ListMonsters* listmonsters) {
    if(listmonsters->firstMonster == NULL) {
        return 0;
    }
    Monster* currentMonster = listmonsters->firstMonster;
    while (currentMonster != NULL)
    {  
        display_drawSingleMonster(currentMonster);
        currentMonster = currentMonster->next;
        
    }
    return 0;

}
