#ifndef GUI_H_
#define GUI_H_

#include <stdlib.h>

#include "structures.h"

//extern GUI *bodyGUI;

GUI *gui_addChildren(SectionName name, int x, int y, int width, int height, GUI *parent);
void gui_init();
void gui_getAbsoluteCoordinates(GUI *section, int *X, int *Y);
void gui_addButton(GUI *section, int x, int y, int width, int height, ButtonName name, Display display_mode);
void gui_getAbsoluteDimensionsButton(GUI *section, Div *button);

#endif //GUI_H_
