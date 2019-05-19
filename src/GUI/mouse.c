#include "mouse.h"

void mouse_handleClick()
{
  int caseX, caseY;

  GUI *current_section = mouse_getSection();

  if (current_section->name == PLATEAU) {
    get_cases(&caseX, &caseY, plateauGUI->dimensions);
    printf("%d %d\n", caseX, caseY);
  }
  if (current_section->name == FOOTER) {
    int buttonClicked = mouse_GUIbutton(current_section);
    printf("%d\n", buttonClicked);
  }
}

int mouse_GUIbutton(GUI *section)
{
  Button *current_button = section->buttons;
  while (current_button) {
    if (mouse_isWithinButton(current_button, section)) {
      // NOTE: We could return which button we're at
      return 1;
    }
    else current_button = current_button->next;
  }
  return 0;
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
  Div button_div;
  button_div.x = button->dimensions->x;
  button_div.y = button->dimensions->y;
  button_div.width = button->dimensions->width;
  button_div.height = button->dimensions->height;
  gui_getAbsoluteDimensionsButton(section, &button_div);

  return mouse_isWithinArea(&button_div);
}

int mouse_isWithinSection(GUI *section)
{
  int X = 0;
  int Y = 0;
  gui_getAbsoluteCoordinates(section, &X, &Y);

  Div div = {X, Y, section->dimensions->width, section->dimensions->height};
  return mouse_isWithinArea(&div);
}

