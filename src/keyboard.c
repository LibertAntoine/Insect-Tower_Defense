#include "keyboard.h"

void keyboard_handleKeypress(SDL_Event *event)
{
  SDLKey key = event->key.keysym.sym; 

  if(gameData->gameState == LEVELPLAY) {
    Etat *joueur = plateau->joueur;
    TypeCase type = joueur->type;
    Action action = joueur->action;
    switch(key) {
      case ' ':
        // NOTE: toggle play/pause
        plateau->play = (plateau->play == TRUE) ? FALSE : TRUE;
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

      case 'v':
        type = LASER;
        break;
      case 'b':
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
    }
    if (action != joueur->action) {
      player_switchAction(action);
    }

    if (type != joueur->type) {
      player_switchTowerType(type);
    }
  } 
}

