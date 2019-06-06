#ifndef MOUSE_H_
#define MOUSE_H_

#ifdef _WIN32
  #include <GL/glew.h>
#else
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif
#include <SDL/SDL.h>

#include "structures.h"
#include "cases.h"
#include "gui.h"
#include "monster.h"

void mouse_handleClick();
GUI *mouse_getSection();
int mouse_isWithinSection(GUI *section);
Button *mouse_GUIbutton(GUI *section);
int mouse_isWithinButton(Button *button, GUI *section);

void mouse_handleButtonClick(Button *button);
void mouse_handleMotion();

void mouse_checkIfMonster();
void mouse_handlePosition();
#endif //MOUSE_H_
