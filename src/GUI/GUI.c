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

  bodyGUI->name = MAIN;

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

  gui_addChildren(FOOTER, 0, 500, 800, 100, bodyGUI);
  gui_addButton(bodyGUI->childen, 700, 50, 25, 35, TOUR, INACTIVE);
}

void gui_getAbsolutePosistionXY(GUI *section, int *x, int *y)
{
  if (section->parent == NULL) return 1;
  else {
    *x += section->dimensions->x;
    *y += section->dimensions->y;
    gui_getAbsolutePosistionXY(section->parent, x, y);
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

  new->next = NULL;

  section->buttons = new;
}
