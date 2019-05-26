#ifndef MOUSE_H_
#define MOUSE_H_

#include <SDL2/SDL.h>

#include "structures.h"
#include "cases.h"
#include "gui.h"
#include "monster.h"

void mouse_handleClick();
GUI *mouse_getSection();
int mouse_isWithinSection(GUI *section);
Button *mouse_GUIbutton(GUI *section);
int mouse_isWithinButton(Button *button, GUI *section);

void mouse_handleButtonClick(ButtonName button_name);
void mouse_handleMotion();

void mouse_checkIfMonster();
void mouse_handlePosition();
#endif //MOUSE_H_
