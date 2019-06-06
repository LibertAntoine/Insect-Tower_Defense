#include "mouse.h"

void mouse_handleClick()
{

  GUI *current_section = mouse_getSection();

  if (current_section->name == PLATEAU) {
    int caseX, caseY;
    float caseX_f, caseY_f;
    get_casesi(&caseX, &caseY, plateauGUI->dimensions);
    get_casesf(&caseX_f, &caseY_f, plateauGUI->dimensions);
    printf("%d %d\n", caseX, caseY);
    printf("%f %f\n", caseX_f, caseY_f);
  }
  if (current_section->name == FOOTER) {
    Button *buttonClicked = mouse_GUIbutton(current_section);
    if (buttonClicked) printf("%d\n", buttonClicked->name +1);
  }
  if (current_section->name == HEADER) {
    Button *buttonClicked = mouse_GUIbutton(current_section);
    if (buttonClicked) printf("%d\n", buttonClicked->name +1);
  }
}

Button *mouse_GUIbutton(GUI *section)
{
  Button *current_button = section->buttons;
  while (current_button) {
    if (mouse_isWithinButton(current_button, section)) {
      return current_button;
    }
    else current_button = current_button->next;
  }
  return NULL;
}

GUI *mouse_getSection()
{
  GUI *current_section = bodyGUI;
  while (current_section) {
    if (mouse_isWithinSection(current_section)) {
      if (current_section->childen != NULL) {
        current_section = current_section->childen;
      }
      else {
        return current_section;
      }
    }
    else {
      if (current_section->next == NULL) {
        return current_section->parent;
      }
      else current_section = current_section->next;
    }
  }
}

int mouse_isWithinArea(Div *dimensions)
{
  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);

  int relative_mouseX = mouseX - dimensions->x;
  int relative_mouseY = mouseY - dimensions->y;

  if (relative_mouseX >= 0 && relative_mouseY >= 0) {
    if (relative_mouseX <= dimensions->width && relative_mouseY <= dimensions->height) {
      return 1;
    }
  }
  return 0;
}

int mouse_isWithinButton(Button *button, GUI *section)
{
  Div div;
  div.x = button->dimensions->x;
  div.y = button->dimensions->y;
  div.width = button->dimensions->width;
  div.height = button->dimensions->height;

  gui_getAbsoluteDimensionsButton(section, &div);

  return mouse_isWithinArea(&div);
}

int mouse_isWithinSection(GUI *section)
{
  int X = 0;
  int Y = 0;
  gui_getAbsoluteCoordinates(section, &X, &Y);

  Div div = {X, Y, section->dimensions->width, section->dimensions->height};
  return mouse_isWithinArea(&div);
}

