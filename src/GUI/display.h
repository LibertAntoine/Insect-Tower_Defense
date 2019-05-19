#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <GL/gl.h>
#include <GL/glu.h>

#include "GUI.h"
#include "cases.h"
#include "structures.h"


void display_boardGrid(int Xsplit, int Ysplit);
void display_game(GUI *plateau, int Xsplit, int Ysplit);
void display_top();
void display_left();
void display_bottom();
void display_grid(int Xsplit, int Ysplit);

void display_drawSingleButton(Button *button);
void display_drawZoneBasedOnGUI(GUI *section);
void display_setDrawingZone(GUI *section);
#endif //DISPLAY_H_

