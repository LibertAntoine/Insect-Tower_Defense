#include "keyboard.h"

void keyboard_handleKeypress(SDL_Event *event)
{
  SDL_Keycode key = event->key.keysym.sym; 

  if(gameState == LEVELPLAY) {
    Etat *joueur = plateau->joueur;
    TypeCase type = joueur->type;
    Action action = joueur->action;
    switch(key) {
      case ' ':
        plateau->play = (plateau->play == TRUE) ? FALSE : TRUE;
        // NOTE: toggle play/pause
        break;
      case 'r':
        type = RADAR;
        break;
      case 'a':
        type = ARMEMENT;
        break;
      case 'c':
        type = CENTRALE;
        break;
      case 'm':
        type = MUNITION;
        break;

      case '1':
        type = LASER;
        break;
      case '2':
        type = MISSILE;
        break;

      case 'p':
        action = ADD;
        break;
      case 'i':
        action = GETINFO;
        break;
      case 'x':
        action = REMOVE;
        break;
        if (action != joueur->action) {
          player_switchAction(action);
        }

        if (type != joueur->type) {
          player_switchTowerType(type);
        }
      }
    } else if (gameState == MAINMENU) {
      switch(key) {
      case 'a':
        itd_actionMenu(LEVEL1_BTN);
        break;
      case 'z':
        itd_actionMenu(LEVEL2_BTN);
        break;
      case 'e':
        itd_actionMenu(LEVEL3_BTN);
        break;
      }
    } else if (gameState == LOSEMENU || gameState == WINMENU) {
      switch(key) {
      case 'a':
        itd_actionMenu(MAINMENU_BTN);
        break;
      case 'z':
        itd_actionMenu(REPLAY_BTN);
        break;
      }
    }


}

