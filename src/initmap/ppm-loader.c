#include "ppm-loader.h"


int ppm_checkValidType(char buffer[])
{
  //printf("buffer : %s %c%c%d\n", buffer, buffer[0], buffer[1], buffer[2]);
  if (buffer[0] != 'P' || buffer[1] != '6' || buffer[2] != '\0') {
    return 0;
  }
  else {
    return 1;
  }
}

void ppm_gotoEndOfLine(FILE* image)
{
  char crtChar = (char) fgetc(image);
  while(crtChar != '\n' && crtChar != EOF) {
    crtChar = fgetc(image);
  }
}

void ppm_handleComments(FILE *image)
{
  char buffer[100];
  int current_position = ftell(image);

  fscanf(image, "%s", buffer);
  //printf("comment character :%c\n", buffer[0]);
  if (buffer[0] == '#') {
    //printf("skipping one comment\n");
    ppm_gotoEndOfLine(image);
    ppm_handleComments(image);
  }
  else {
    fseek(image, current_position, SEEK_SET);
  }
}

char* ppm_loadImage(char path[])
{

  int width, height, color_value;

  FILE* image = fopen(path, "rb");
  
  if (!image) {
    printf("Image couldn't be loaded, interupting program\n");
    return EXIT_FAILURE;
  }

  char buffer[100];

  //Read type
  fscanf(image, "%s", buffer);
  if (ppm_checkValidType(buffer) == 0) {
    printf("Invalid PPM type\n");
    return EXIT_FAILURE;
  }

  //Read data loop
  ppm_handleComments(image);
  fscanf(image, "%d", &width);
  ppm_handleComments(image);
  fscanf(image, "%d", &height);
  ppm_handleComments(image);
  fscanf(image, "%d", &color_value);
  ppm_handleComments(image);

  //Read actual image data
  unsigned char* pixel_data = malloc(sizeof(unsigned char)*3*width*height);
  if (!pixel_data) {
    printf("Couldn't initialize array of pixels\n");
    return EXIT_FAILURE;
  }

  ppm_gotoEndOfLine(image);

  fread(pixel_data, 3*width, height, image);
  
  plateau->Xsplit = width;
  plateau->Ysplit = height;

  return pixel_data;

}
