#include "mouse.h"

void mouse_handlePosition()
{
  GUI *current_section = mouse_getSection();

  if (current_section->name == PLATEAU) {
    //printf("%f x %f y\n", casex_f, casey_f);

    int casex;
    int casey;
    get_casesi(&casex, &casey, plateauGUI->dimensions);

    TypeCase currentCase_type = case_getType(casex, casey);

    //TODO: Si sur chemin :
    if (currentCase_type == CHEMIN || currentCase_type == NOEUD) {
      mouse_checkIfMonster();
    }
    else if (plateau->monster_hover) {
      plateau->monster_hover = NULL;
    }
  }
}

void mouse_checkIfMonster()
{
  float casex_f;
  float casey_f;
  get_casesf(&casex_f, &casey_f, plateauGUI->dimensions);

  Monster* currentMonster = plateau->listMonsters->firstMonster;
  while (currentMonster) {
    if (casex_f <= currentMonster->x + 0.5 && casex_f >= currentMonster->x - 0.5) {
      if (casey_f <= currentMonster->y + 0.5 && casey_f >= currentMonster->y - 0.5) {
        // NOTE: getting proper infos
        //monster_printInfos(currentMonster);
        break;
      }
    }
    currentMonster = currentMonster->next;
  }

  plateau->monster_hover = currentMonster;
}

void mouse_handleButtonClick(ButtonName button_name)
{
  Etat *joueur = &(plateau->joueur);
  TypeCase type = joueur->type;
  Action action = joueur->action;

  switch (button_name) {
    case PAUSE_BTN:
      plateau->play = (plateau->play == TRUE) ? FALSE : TRUE;
      break;
    case RADAR_BTN:
      type = RADAR;
      break;
    case ARMEMENT_BTN:
      type = ARMEMENT;
      break;
    case CENTRALE_BTN:
      type = CENTRALE;
      break;
    case MUNITION_BTN:
      type = MUNITION;
      break;

    case LASER_BTN:
      type = LASER;
      break;
    case MISSILE_BTN:
      type = MISSILE;
      break;

    case ADD_BTN:
      action = ADD;
      break;
    case GETINFO_BTN:
      action = GETINFO;
      break;
    case REMOVE_BTN:
      action = REMOVE;
      break;
  }

  if (action != joueur->action) {
    player_switchAction(action);
  }

  if (type != joueur->type) {
    player_switchTowerType(type);
  }
}

void mouse_handleClick()
{
  GUI *current_section = mouse_getSection();

  if (current_section->name == PLATEAU) {
    int casex, casey;
    float casex_f, casey_f;
    get_casesi(&casex, &casey, plateauGUI->dimensions);
    get_casesf(&casex_f, &casey_f, plateauGUI->dimensions);
    printf("%d %d\n", casex, casey);
    printf("%f %f\n", casex_f, casey_f);
    case_handleAction(casex, casey);
  }
  Button *buttonClicked = mouse_GUIbutton(current_section);
  if (buttonClicked) {
    mouse_handleButtonClick(buttonClicked->name);
    printf("%d\n", buttonClicked->name +1);
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


