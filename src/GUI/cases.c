#include "cases.h"

void get_cases(int *caseX, int *caseY, Div *plateau)
{
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);

  int Xsplit = 6;
  int Ysplit = 5;

  int RmouseX = mouseX - plateau->x;
  int RmouseY = mouseY - plateau->y;

  int stepX = plateau->width / Xsplit;
  int stepY = plateau->height / Ysplit;

  printf("%d %d\n", RmouseX, RmouseY);

  if (RmouseX >= 0 && RmouseY >= 0) {
    if (RmouseX <= plateau->width && RmouseY <= plateau->height) {
      // on est bien dans le plateau,
      *caseX = RmouseX / stepX;
      *caseY = RmouseY / stepY;
    }
  }
}
