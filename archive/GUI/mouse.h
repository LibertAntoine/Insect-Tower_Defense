#ifndef MOUSE_H_
#define MOUSE_H_

#include <SDL2/SDL.h>

#include "structures.h"
#include "cases.h"
#include "GUI.h"

void mouse_handleClick();
GUI *mouse_getSection();
int mouse_isWithinSection(GUI *section);
Button *mouse_GUIbutton(GUI *section);
int mouse_isWithinButton(Button *button, GUI *section);


#endif //MOUSE_H_

