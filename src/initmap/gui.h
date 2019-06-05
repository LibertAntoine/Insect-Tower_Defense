#ifndef GUI_H_
#define GUI_H_

#include <stdlib.h>

#include "SDLConfig.h"
#include "structures.h"

Display gui_getTowerButtonState(TypeCase type);
ButtonName gui_getButtonNameFromTypeCase(TypeCase type);
void gui_changeActionButtonState(Action action, Display state);
void gui_changeTowerButtonState(TypeCase type, Display state);
GUI *gui_addChildren(SectionName name, int x, int y, int width, int height, GUI *parent, TextureName texture_name, Bool display_texture);
void gui_init();
void gui_getAbsoluteCoordinates(GUI *section, int *X, int *Y);
void gui_addButton(GUI *section, int x, int y, int width, int height, ButtonName name, Display display_mode, TextureName texture_name, Bool display_texture);
void gui_getAbsoluteDimensionsButton(GUI *section, Div *button);

#endif //GUI_H_

