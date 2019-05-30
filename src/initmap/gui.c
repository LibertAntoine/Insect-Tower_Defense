#include "gui.h"

ButtonName gui_getButtonNameFromAction(Action action)
{
  ButtonName button_name;
  switch(action) {
    case GETINFO:
      button_name = GETINFO_BTN;
      break;
    case ADD:
      button_name = ADD_BTN;
      break;
    case REMOVE:
      button_name = REMOVE_BTN;
      break;
  }
  return button_name;
}

ButtonName gui_getButtonNameFromTypeCase(TypeCase type)
{
  ButtonName button_name;
  switch(type) {
    case LASER:
      button_name = LASER_BTN;
      break;
    case MISSILE:
      button_name = MISSILE_BTN;
      break;
    case RADAR:
      button_name = RADAR_BTN;
      break;
    case ARMEMENT:
      button_name = ARMEMENT_BTN;
      break;
    case CENTRALE:
      button_name = CENTRALE_BTN;
      break;
    case MUNITION:
      button_name = MUNITION_BTN;
      break;
  }
  return button_name;
}

Display gui_getTowerButtonState(TypeCase type)
{
  ButtonName button_name = gui_getButtonNameFromTypeCase(type);
  Button *currentButton = buttonGUI->buttons;
  while (currentButton->name != button_name) {
    currentButton = currentButton->next;
  }
  return currentButton->display;
}

void gui_changeTowerButtonState(TypeCase type, Display state)
{
  ButtonName button_name = gui_getButtonNameFromTypeCase(type);
  Button *currentButton = buttonGUI->buttons;
  while (currentButton->name != button_name) {
    if (currentButton->next == NULL) {
      return;
    }
    currentButton = currentButton->next;
  }
  currentButton->display = state;
}

void gui_changeActionButtonState(Action action, Display state)
{
  ButtonName button_name = gui_getButtonNameFromAction(action);
  Button *currentButton = buttonGUI->buttons;
  while (currentButton->name != button_name) {
    currentButton = currentButton->next;
  }
  currentButton->display = state;
}

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
  dimensions->width = WINDOW_WIDTH;
  dimensions->height = WINDOW_HEIGHT;
  bodyGUI->dimensions = dimensions;


  topGUI = gui_addChildren(HEADER, 0, 0, bodyGUI->dimensions->width, 40, bodyGUI);
  gui_addButton(topGUI, 600, 20, 25, 25, PAUSE_BTN, CLICKED);

  plateauGUI = gui_addChildren(PLATEAU, 0, 40, bodyGUI->dimensions->width, 600, bodyGUI);

  bottomGUI = gui_addChildren(FOOTER, 0, 640, bodyGUI->dimensions->width, 160, bodyGUI);

  infoGUI = gui_addChildren(INFO_SECTION, 0, 0, 350, bottomGUI->dimensions->height, bottomGUI);

  buttonGUI = gui_addChildren(TOWER_BUTTONS_SECTION, 500, 0, 300, bottomGUI->dimensions->height, bottomGUI);

  gui_addButton(buttonGUI, 20, 30, 25, 25, LASER_BTN, CLICKED);
  gui_addButton(buttonGUI, 70, 30, 25, 25, MISSILE_BTN, ACTIVE);

  gui_addButton(buttonGUI, 20, 70, 25, 25, ARMEMENT_BTN, ACTIVE);
  gui_addButton(buttonGUI, 70, 70, 25, 25, MUNITION_BTN, ACTIVE);
  gui_addButton(buttonGUI, 20, 120, 25, 25, RADAR_BTN, ACTIVE);
  gui_addButton(buttonGUI, 70, 120, 25, 25, CENTRALE_BTN, ACTIVE);

  gui_addButton(buttonGUI, 150, 30, 25, 25, ADD_BTN, CLICKED);
  gui_addButton(buttonGUI, 150, 50, 25, 25, GETINFO_BTN, ACTIVE);
  gui_addButton(buttonGUI, 150, 70, 25, 25, REMOVE_BTN, ACTIVE);


  mainMenuGUI = calloc(1, sizeof(GUI));
  mainMenuGUI->name = MAIN;
  Div *dimensions_main = calloc(1, sizeof(Div));
  dimensions_main->width = WINDOW_WIDTH;
  dimensions_main->height = WINDOW_HEIGHT;
  mainMenuGUI->dimensions = dimensions_main;
  gui_addButton(mainMenuGUI, 400, 400, 250, 25, LEVEL1_BTN, ACTIVE);
  gui_addButton(mainMenuGUI, 400, 450, 250, 25, LEVEL2_BTN, ACTIVE);
  gui_addButton(mainMenuGUI, 400, 500, 250, 25, LEVEL3_BTN, ACTIVE);

  endMenuGUI = calloc(1, sizeof(GUI));
  endMenuGUI->name =LOSEMENU ;
  Div *dimensions_end = calloc(1, sizeof(Div));
  dimensions_end->width = WINDOW_WIDTH;
  dimensions_end->height = WINDOW_HEIGHT;
  endMenuGUI->dimensions = dimensions_main;
  gui_addButton(endMenuGUI, 400, 400, 250, 25, MAINMENU_BTN, ACTIVE);
  gui_addButton(endMenuGUI, 400, 450, 250, 25, REPLAY_BTN, ACTIVE);
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
  Button *new_button = calloc(1, sizeof(Button));

  Div *dimensions = calloc(1, sizeof(Div));
  dimensions->x = x;
  dimensions->y = y;
  dimensions->width = width;
  dimensions->height = height;
  new_button->dimensions = dimensions;

  new_button->name = name;
  new_button->display = display_mode;
  new_button->next = section->buttons;

  section->buttons = new_button;
}
