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
  textures = calloc(14, sizeof(Texture*));

  textures[SOLDER_TEX] = sprite_importTexture("images/sprite_A.png", 4, 1); 
}

SpriteTexture* sprite_loadSprite(TextureName texture_name, Uint32 loop_duration)
{
  SpriteTexture *new_sprite = calloc(1, sizeof(SpriteTexture));
  //TODO: check alloc

  //TODO: clarify magic variables
  new_sprite->loop_duration = loop_duration;
  new_sprite->last_frame = 0;

  new_sprite->sprite_numX = -1;
  new_sprite->sprite_numY = 0;
  new_sprite->texture_name = texture_name;

  return new_sprite;
}

void sprite_displaySprite(SpriteTexture* sprite)
{
  Texture* currentTexture = textures[sprite->texture_name];

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, currentTexture->texture_id);

  sprite_updateSprite(sprite);

  float x_shift = 1. / currentTexture->sprite_totalX;
  float y_shift = 1. / currentTexture->sprite_totalY;

  glColor3f(1,1,1);
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
}

void sprite_updateSprite(SpriteTexture* sprite)
{
  Uint32 now = SDL_GetTicks();
  if (now - sprite->last_frame >= sprite->loop_duration) {
    sprite_translateTexture(sprite);
    sprite->last_frame = now;
  }
}

void sprite_translateTexture(SpriteTexture* sprite)
{
  sprite->sprite_numX++;

  // TODO: checker systeme de coord
  if (sprite->sprite_numX >= textures[sprite->texture_name]->sprite_totalX) {
    sprite->sprite_numX = 0;
    sprite->sprite_numY++;

    if (sprite->sprite_numY >= textures[sprite->texture_name]->sprite_totalY) {
      sprite->sprite_numX = 0;
      sprite->sprite_numY = 0;
    }
  }

  float x_shift = 1. / textures[sprite->texture_name]->sprite_totalX;
  float y_shift = 1. / textures[sprite->texture_name]->sprite_totalY;

  glMatrixMode(GL_TEXTURE);
  glLoadIdentity();

  // TODO: check translate the texture
  glTranslatef(x_shift * sprite->sprite_numX, y_shift * sprite->sprite_numY, 0);

  glMatrixMode(GL_MODELVIEW);
}
