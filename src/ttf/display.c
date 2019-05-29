#include "display.h"

TextureText*  loadTextureText(char text[])
{
  TTF_Init();
  TTF_Font *font = TTF_OpenFont("../../fonts/fun.ttf", 36);
  SDL_Color couleurNoire = {255, 55, 155};
  SDL_Surface* texture_surface = TTF_RenderText_Blended(font, "Hello Font !", couleurNoire);

  GLuint texture_id;
  glGenTextures(1, &texture_id);

  glBindTexture(GL_TEXTURE_2D, texture_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  GLuint colours = texture_surface->format->BytesPerPixel;
  GLuint externalFormat, internalFormat;
  SDL_PixelFormat *format = texture_surface->format;
  if (colours == 4) {

    if (texture_surface->format->Rmask == 0x000000ff)
      externalFormat = GL_RGBA;
    else
      externalFormat = GL_BGRA;
  }
  else {
      if (texture_surface->format->Rmask == 0x000000ff)
        externalFormat = GL_RGB;
      else
        externalFormat = GL_BGR;
  }
  internalFormat = (colours == 4) ? GL_RGBA : GL_RGB;

                                                                             

  glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, texture_surface->w, texture_surface->h, 0, externalFormat, GL_UNSIGNED_BYTE, texture_surface->pixels);

  glBindTexture(GL_TEXTURE_2D, 0);

  TTF_CloseFont(font);
  TTF_Quit();

  TextureText* texture_texte = malloc(sizeof(TextureText));
  texture_texte->texture_id = texture_id;
  texture_texte->ratio = texture_surface->w / (float) texture_surface->h;

  return texture_texte;
}

void display_infos(TextureText* text, int height)
{
  int width = text->ratio * height;

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, text->texture_id);

  glColor4f(1,1,1,1);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex2f(0, 0);
  glTexCoord2f(1, 0);
  glVertex2f(width, 0);
  glTexCoord2f(1, 1);
  glVertex2f(width, height);
  glTexCoord2f(0, 1);
  glVertex2f(0, height);
  glEnd();

  glDisable(GL_BLEND);

  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);
}
