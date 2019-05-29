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
  Texture* new_texture = malloc(sizeof(Texture));
  SDL_Surface* texture_surface = IMG_Load(image_path);
  new_texture->sprite_totalX = totalX;
  new_texture->sprite_totalY = totalY;

  GLuint texture_id;
  glGenTextures(1, &texture_id);
  new_texture->texture_id = texture_id;

  glBindTexture(GL_TEXTURE_2D, new_texture->texture_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_surface->w, texture_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_surface->pixels);
  // NOTE: Unbinding
  glBindTexture(GL_TEXTURE_2D, 0);

  return new_texture;
}

void sprite_init()
{
  textures = calloc(17, sizeof(Texture*));

  textures[SOLDER_TEX] = sprite_importTexture("images/sprite_A.png", 4, 1); 
  textures[HUGE_SOLDER_TEX] = sprite_importTexture("images/sprite_B2.png", 2, 1); 
  textures[BOSS_TEX] = sprite_importTexture("images/sprite_C.png", 4, 1); 
  textures[GERERAL_TEX] = sprite_importTexture("images/sprite_D.png", 3, 1); 
  textures[CENTRALE_TEX] = sprite_importTexture("images/tests/abeille.png", 1, 1); 
  textures[RADAR_TEX] = sprite_importTexture("images/tests/coccinelle.png", 1, 1); 
  textures[ARMEMENT_TEX] = sprite_importTexture("images/tests/guepe.png", 1, 1); 
  textures[MUNITION_TEX] = sprite_importTexture("images/tests/punaise.png", 1, 1); 

  textures[MISSILE_TEX] = sprite_importTexture("images/tests/sauterelle.png", 1, 1); 
  textures[LASER_TEX] = sprite_importTexture("images/tests/bizarre.png", 1, 1); 

  textures[ADD_TEX] = sprite_importTexture("images/tests/add.png", 1, 1); 
  textures[REMOVE_TEX] = sprite_importTexture("images/tests/delete.png", 1, 1); 
  textures[GETINFO_TEX] = sprite_importTexture("images/tests/info.png", 1, 1); 

  textures[PAUSE_TEX] = sprite_importTexture("images/tests/pause.png", 1, 1); 
  textures[PLAY_TEX] = sprite_importTexture("images/tests/play.png", 1, 1); 
  textures[SPLASH_TEX] = sprite_importTexture("images/sprite_splash.png", 1, 1); 
  textures[BUTTON_TEX] = sprite_importTexture("images/sprite_Button.png", 1, 1); 
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

void sprite_displayFixedTexture(TextureName texture_name)
{
  Texture* texture = textures[texture_name];
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
  Texture* currentTexture = textures[sprite->texture_name];

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
  Texture* texture = textures[sprite->texture_name];

  if (now - sprite->last_frame >= sprite->loop_duration / (texture->sprite_totalX * texture->sprite_totalY)) {
    sprite->sprite_numX++;

    if (sprite->sprite_numX >= textures[sprite->texture_name]->sprite_totalX) {
      sprite->sprite_numX = 0;
      sprite->sprite_numY++;

      if (sprite->sprite_numY >= textures[sprite->texture_name]->sprite_totalY) {
        sprite->sprite_numX = 0;
        sprite->sprite_numY = 0;
      }
    }

    float shift_x = 1. / textures[sprite->texture_name]->sprite_totalX;
    float shift_y = 1. / textures[sprite->texture_name]->sprite_totalY;

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
