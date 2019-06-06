#include "animation.h"

SpriteTexture* animation_loadSprite(char image_path[], int total_splitX, int total_splitY, Uint32 loop_duration)
{
  SDL_Surface* texture_surface = IMG_Load(image_path);

  SpriteTexture *new_sprite = calloc(1, sizeof(SpriteTexture));
  //TODO: check alloc


  //TODO: clarify magic variables
  new_sprite->loop_duration = loop_duration;
  new_sprite->last_frame = 0;
  new_sprite->sprite_totalX = total_splitX;
  new_sprite->sprite_totalY = total_splitY;

  new_sprite->sprite_numX = -1;
  new_sprite->sprite_numY = 0;

  GLuint texture_id;
  glGenTextures(1, &texture_id);
  new_sprite->texture_id = texture_id;

  glBindTexture(GL_TEXTURE_2D, new_sprite->texture_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_surface->w, texture_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_surface->pixels);

  // NOTE: Unbinding
  glBindTexture(GL_TEXTURE_2D, 0);

  return new_sprite;
}

void animation_displaySprite(SpriteTexture* sprite)
{
  //NOTE: Activation de la couche alpha
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  //NOTE: Mettre du blanc sous l'image et activation de la texture
  glColor3f(0, 1, 0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, sprite->texture_id);

  animation_updateSprite(sprite);

  GLfloat params[16];
  glGetFloatv(GL_TEXTURE_MATRIX, params);

  float x_shift = 1. / sprite->sprite_totalX;
  float y_shift = 1. / sprite->sprite_totalY;

  glColor4f(1,1,1,0.5);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex2f(0, 0);
  glTexCoord2f(x_shift, 0);
  glVertex2f(400, 0);
  glTexCoord2f(x_shift, y_shift);
  glVertex2f(400, 300);
  glTexCoord2f(0, y_shift);
  glVertex2f(0, 300);
  glEnd();

  glDisable(GL_BLEND);

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}

void animation_updateSprite(SpriteTexture* sprite)
{
  Uint32 now = SDL_GetTicks();
  if (now - sprite->last_frame >= sprite->loop_duration) {
    animation_translateTexture(sprite);
    sprite->last_frame = now;
  }
}

void animation_translateTexture(SpriteTexture* sprite)
{
  sprite->sprite_numX++;

  // TODO: checker systeme de coord
  if (sprite->sprite_numX >= sprite->sprite_totalX) {
    sprite->sprite_numX = 0;
    sprite->sprite_numY++;

    if (sprite->sprite_numY >= sprite->sprite_totalY) {
      sprite->sprite_numX = 0;
      sprite->sprite_numY = 0;
    }
  }

  float x_shift = 1. / sprite->sprite_totalX;
  float y_shift = 1. / sprite->sprite_totalY;

  glMatrixMode(GL_TEXTURE);
  glLoadIdentity();

  // TODO: check translate the texture
  glTranslatef(x_shift * sprite->sprite_numX, y_shift * sprite->sprite_numY, 0);

  glMatrixMode(GL_MODELVIEW);
}
