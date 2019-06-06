#include "sprite.h"

TextureName sprite_getTextureNameFromButtonName(ButtonName button_name)
{
  TextureName texture_name;
  switch(button_name) {
    case LASER_BTN:
      texture_name = LASER_TEX;
      break;
    case MISSILE_BTN:
      texture_name = MISSILE_TEX;
      break;
    case RADAR_BTN:
      texture_name = RADAR_TEX;
      break;
    case ARMEMENT_BTN:
      texture_name = ARMEMENT_TEX;
      break;
    case CENTRALE_BTN:
      texture_name = CENTRALE_TEX;
      break;
    case MUNITION_BTN:
      texture_name = MUNITION_TEX;
      break;
    case ADD_BTN:
      texture_name = ADD_TEX;
      break;
    case GETINFO_BTN:
      texture_name = GETINFO_TEX;
      break;
    case REMOVE_BTN:
      texture_name = REMOVE_TEX;
      break;
    case PAUSE_BTN:
      texture_name = PAUSE_TEX;
      break;
  }
  return texture_name;
}

Texture* sprite_importTexture(char image_path[], int totalX, int totalY)
{
  GLint internalFormat = GL_RGB;
  GLenum format = GL_RGB;

  if (strstr(image_path, ".png") != NULL) {
    internalFormat = GL_RGBA;
    format = GL_RGBA;
  }

  Texture* new_texture = malloc(sizeof(Texture));
  if (!new_texture) {
    printf("ERROR ALLOC : new_texture");
    exit(CHK_ERROR_ALLOC);
  }
  SDL_Surface* texture_surface = IMG_Load(image_path);
if(!texture_surface) {
    printf("IMG_Load: %s\n", IMG_GetError());
    // handle error
}
  new_texture->sprite_totalX = totalX;
  new_texture->sprite_totalY = totalY;

  GLuint texture_id;
  glGenTextures(1, &texture_id);
  new_texture->texture_id = texture_id;

  glBindTexture(GL_TEXTURE_2D, new_texture->texture_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, texture_surface->w, texture_surface->h, 0, format, GL_UNSIGNED_BYTE, texture_surface->pixels);

  // NOTE: Unbinding
  glBindTexture(GL_TEXTURE_2D, 0);

  return new_texture;
}

void sprite_init()
{
  gameData->textures = calloc(41, sizeof(Texture*));

  gameData->textures[SOLDER_TEX] = sprite_importTexture("images/sprite-entities/cafard.png", 2, 1); 
  gameData->textures[HUGE_SOLDER_TEX] = sprite_importTexture("images/sprite-entities/punaise.png", 2, 1); 
  gameData->textures[BOSS_TEX] = sprite_importTexture("images/sprite-entities/gendarme.png", 2, 1); 
  gameData->textures[GERERAL_TEX] = sprite_importTexture("images/sprite-entities/larve.png", 2, 1); 

  gameData->textures[CENTRALE_TEX] = sprite_importTexture("images/tests/food.png", 1, 1); 
  gameData->textures[RADAR_TEX] = sprite_importTexture("images/tests/gem1.png", 1, 1); 
  gameData->textures[ARMEMENT_TEX] = sprite_importTexture("images/tests/gem2.png", 1, 1); 
  gameData->textures[MUNITION_TEX] = sprite_importTexture("images/tests/gem3.png", 1, 1); 

  gameData->textures[MISSILE_TEX] = sprite_importTexture("images/sprite-entities/puceron.png", 1, 1); 
  gameData->textures[LASER_TEX] = sprite_importTexture("images/sprite-entities/mouche.png", 1, 1); 

  gameData->textures[ADD_TEX] = sprite_importTexture("images/tests/add.png", 1, 1); 
  gameData->textures[REMOVE_TEX] = sprite_importTexture("images/tests/delete.png", 1, 1); 
  gameData->textures[GETINFO_TEX] = sprite_importTexture("images/tests/info.png", 1, 1); 

  gameData->textures[PAUSE_TEX] = sprite_importTexture("images/tests/pause.png", 1, 1); 
  gameData->textures[PLAY_TEX] = sprite_importTexture("images/tests/play.png", 1, 1); 
  gameData->textures[SPLASH_TEX] = sprite_importTexture("images/sprite_splash.png", 1, 1); 
  gameData->textures[BUTTON_TEX] = sprite_importTexture("images/sprite_Button.png", 1, 1); 

  gameData->textures[PLANK_TEX] = sprite_importTexture("images/tests/plank.png", 1, 1); 
  gameData->textures[PLUS_TEX] = sprite_importTexture("images/tests/plus.png", 1, 1); 
  gameData->textures[TARGET_TEX] = sprite_importTexture("images/tests/target.png", 1, 1); 
  gameData->textures[MONEY_TEX] = sprite_importTexture("images/tests/money.png", 1, 1); 
  gameData->textures[POINTER_TEX] = sprite_importTexture("images/tests/hand.png", 1, 1); 
  gameData->textures[SHIELD_TEX] = sprite_importTexture("images/tests/shield.png", 1, 1); 
  gameData->textures[DAMAGE_TEX] = sprite_importTexture("images/tests/explosion.png", 1, 1); 
  gameData->textures[CADENCE_TEX] = sprite_importTexture("images/tests/munition.png", 1, 1); 
  gameData->textures[SPEED_TEX] = sprite_importTexture("images/tests/speed.png", 1, 1); 
  gameData->textures[LIFE_TEX] = sprite_importTexture("images/tests/heart.png", 1, 1); 
  gameData->textures[FOOD_TEX] = sprite_importTexture("images/tests/cookie.png", 1, 1); 

  gameData->textures[TERRAIN_1_TEX] = sprite_importTexture("images/sprite-world/terrain1.png", 1, 1); 
  gameData->textures[TERRAIN_2_TEX] = sprite_importTexture("images/sprite-world/terrain2.png", 1, 1); 
  gameData->textures[TERRAIN_3_TEX] = sprite_importTexture("images/sprite-world/terrain3.png", 1, 1); 
  gameData->textures[TERRAIN_4_TEX] = sprite_importTexture("images/sprite-world/terrain4.png", 1, 1); 
  gameData->textures[TERRAIN_5_TEX] = sprite_importTexture("images/sprite-world/terrain5.png", 1, 1); 
  gameData->textures[CHEMIN_1_TEX] = sprite_importTexture("images/sprite-world/chemin1.png", 1, 1); 
  gameData->textures[CHEMIN_2_TEX] = sprite_importTexture("images/sprite-world/chemin2.png", 1, 1); 
  gameData->textures[CHEMIN_3_TEX] = sprite_importTexture("images/sprite-world/chemin3.png", 1, 1); 

  gameData->textures[REINE_TEX] = sprite_importTexture("images/sprite-world/arrivee-reine.png", 1, 1); 

  gameData->textures[MAINMENU_TEX] = sprite_importTexture("images/sprite-gui/MainMenu.jpg", 1, 1); 
  gameData->textures[LOSEMENU_TEX] = sprite_importTexture("images/sprite-gui/LoseMenu.jpg", 1, 1); 
  gameData->textures[WINMENU_TEX] = sprite_importTexture("images/sprite-gui/WinMenu.jpg", 1, 1); 

  gameData->textures[WOODPLANKS_TEX] = sprite_importTexture("images/sprite-gui/wood_planks.jpg", 1, 1); 
}

SpriteTexture* sprite_loadSprite(TextureName texture_name, int loop_duration, Bool loop)
{
  SpriteTexture *new_sprite = calloc(1, sizeof(SpriteTexture));
  //TODO: check alloc

  new_sprite->loop_duration = loop_duration;
  new_sprite->last_frame = 0;
  new_sprite->loop = loop;

  new_sprite->sprite_numX = -1;
  new_sprite->sprite_numY = 0;
  new_sprite->texture_name = texture_name;

  new_sprite->translate_x = 0;
  new_sprite->translate_y = 0;

  return new_sprite;
}

void sprite_displayFixedTextureText(TextureText* texture_texte)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_texte->texture_id);

  glBegin(GL_QUADS);
  glTexCoord2f(0, 1);
  glVertex2f(0,0.5);
  glTexCoord2f(0, 0);
  glVertex2f(0,-0.5);
  glTexCoord2f(1, 0);
  glVertex2f(1,-0.5);
  glTexCoord2f(1, 1);
  glVertex2f(1,0.5);

  glEnd();

  glDisable(GL_BLEND);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}

void sprite_updateFPS(float FPS)
{
  char counter[20];
  int FPS_i = (int) FPS;
  sprintf(counter, "%d", FPS_i);
  int length = strlen(counter);
  counter[length] = ' ';
  counter[length+1] = 'F';
  counter[length+2] = 'P';
  counter[length+3] = 'S';
  gameData->FPS = display_loadTextureText(counter);
}

void sprite_displayFixedTexture(TextureName texture_name)
{
  Texture* texture = gameData->textures[texture_name];
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture->texture_id);

  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);

  glTexCoord2f(0, 1./texture->sprite_totalY);
  glVertex2f(-0.5,0.5);
  glTexCoord2f(1./texture->sprite_totalX, 1./texture->sprite_totalY);
  glVertex2f(0.5,0.5);
  glTexCoord2f(1./texture->sprite_totalX, 0);
  glVertex2f(0.5,-0.5);
  glTexCoord2f(0, 0);
  glVertex2f(-0.5,-0.5);
  glEnd();

  glDisable(GL_BLEND);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}

void sprite_displaySprite(SpriteTexture* sprite)
{
  Texture* currentTexture = gameData->textures[sprite->texture_name];

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, currentTexture->texture_id);

  if (sprite->loop == TRUE && plateau->play == TRUE) {
    sprite_updateSprite(sprite);
  }

  float x_shift = 1. / currentTexture->sprite_totalX;
  float y_shift = 1. / currentTexture->sprite_totalY;

  sprite_translateTexture(sprite);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);

  glTexCoord2f(0, y_shift);
  glVertex2f(-0.5,0.5);
  glTexCoord2f(x_shift, y_shift);
  glVertex2f(0.5,0.5);
  glTexCoord2f(x_shift, 0);
  glVertex2f(0.5,-0.5);
  glTexCoord2f(0, 0);
  glVertex2f(-0.5,-0.5);
  glEnd();

  glDisable(GL_BLEND);

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

  glMatrixMode(GL_TEXTURE);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
}

void sprite_updateSprite(SpriteTexture* sprite)
{
  Uint32 now = SDL_GetTicks();
  Texture* texture = gameData->textures[sprite->texture_name];

  if (now - sprite->last_frame >= sprite->loop_duration / (texture->sprite_totalX * texture->sprite_totalY)) {
    sprite->sprite_numX++;

    if (sprite->sprite_numX >= gameData->textures[sprite->texture_name]->sprite_totalX) {
      sprite->sprite_numX = 0;
      sprite->sprite_numY++;

      if (sprite->sprite_numY >= gameData->textures[sprite->texture_name]->sprite_totalY) {
        sprite->sprite_numX = 0;
        sprite->sprite_numY = 0;
      }
    }

    float shift_x = 1. / gameData->textures[sprite->texture_name]->sprite_totalX;
    float shift_y = 1. / gameData->textures[sprite->texture_name]->sprite_totalY;

    sprite->translate_x = shift_x * sprite->sprite_numX;
    sprite->translate_y = shift_y * sprite->sprite_numY;

    sprite->last_frame = now;
  }
}

void sprite_translateTexture(SpriteTexture* sprite)
{
  glMatrixMode(GL_TEXTURE);
  glLoadIdentity();

  glTranslatef(sprite->translate_x, sprite->translate_y, 0);

  glMatrixMode(GL_MODELVIEW);
}
