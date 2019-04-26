#ifndef PPM_LOADER_H_
#define PPM_LOADER_H_

#include <stdlib.h>
#include <stdio.h>

char* ppm_loadImage(char path[], int* Xcases, int* Ycases);
void ppm_handleComments(FILE *image);
void ppm_gotoEndOfLine(FILE* image);
int ppm_checkValidType(char buffer[]);
#endif //PPM_LOADER_H_
