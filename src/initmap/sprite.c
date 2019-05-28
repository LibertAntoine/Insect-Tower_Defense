#include "sprite.h"

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

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_surface->w, texture_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_surface->pixels);
  // NOTE: Unbinding
  glBindTexture(GL_TEXTURE_2D, 0);

  return new_texture;
}

void sprite_init()
{
  textures = calloc(15, sizeof(Texture*));

  textures[SOLDER_TEX] = sprite_importTexture("images/sprite_A.png", 4, 1); 
  textures[HUGE_SOLDER_TEX] = sprite_importTexture("images/sprite_B2.png", 2, 1); 
  textures[BOSS_TEX] = sprite_importTexture("images/sprite_C.png", 4, 1); 
  textures[GERERAL_TEX] = sprite_importTexture("images/sprite_D.png", 3, 1); 
  textures[SPLASH_TEX] = sprite_importTexture("images/sprite_splash.png", 1, 1); 
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
