#include "GUI.h"

GUI *gui_addChildren(SectionName name, int x, int y, int width, int height, GUI *parent)
{
  Div *dimensions = calloc(1, sizeof(Div));
  dimensions->x = x;
  dimensions->y = y;
  dimensions->width = width;
  dimensions->height = height;

  GUI *new = calloc(1, sizeof(GUI));
  new->parent = parent;
  new->childen = NULL;
  new->name = name;
  new->dimensions = dimensions;
  new->next = parent->childen;
  parent->childen = new;
  return new;
}

void gui_init()
{
  bodyGUI = calloc(1, sizeof(GUI));
  // TODO: check alloc

  bodyGUI->name = BODY;

  Div *dimensions = calloc(1, sizeof(Div));
  dimensions->x = 0;
  dimensions->y = 0;
  dimensions->width = 800;
  dimensions->height = 600;

  bodyGUI->dimensions = dimensions;
  bodyGUI->parent = NULL;
  bodyGUI->next = NULL;
  bodyGUI->childen = NULL;
  bodyGUI->buttons = NULL;

  bottomGUI = gui_addChildren(FOOTER, 0, 500, 800, 100, bodyGUI);
  gui_addButton(bottomGUI, 700, 50, 25, 35, LASER, INACTIVE);
  gui_addButton(bottomGUI, 600, 50, 25, 35, MISSILE, INACTIVE);

  topGUI = gui_addChildren(HEADER, 0, 0, 800, 100, bodyGUI);
  gui_addButton(topGUI, 600, 50, 45, 35, PAUSE, INACTIVE);

  plateauGUI = gui_addChildren(PLATEAU, 300, 100, 500, 400, bodyGUI);
}

void gui_getAbsoluteDimensionsButton(GUI *section, Div *button)
{
  int button_x = 0;
  int button_y = 0;
  gui_getAbsoluteCoordinates(section, &button_x, &button_y);

  button->x = button_x + button->x - button->width / 2;
  button->y = button_y + button->y - button->height / 2;
}

void gui_getAbsoluteCoordinates(GUI *section, int *X, int *Y)
{
  if (section->parent == NULL) {
    return 1;
  }
  else {
    *X += section->dimensions->x;
    *Y += section->dimensions->y;
    gui_getAbsoluteCoordinates(section->parent, X, Y);
  }
}

void gui_addButton(GUI *section, int x, int y, int width, int height, ButtonName name, Display display_mode)
{
  Button *new = calloc(1, sizeof(Button));

  Div *dimensions = calloc(1, sizeof(Div));
  dimensions->x = x;
  dimensions->y = y;
  dimensions->width = width;
  dimensions->height = height;
  new->dimensions = dimensions;

  new->name = name;
  new->display = display_mode;
  new->next = section->buttons;

  section->buttons = new;
}
