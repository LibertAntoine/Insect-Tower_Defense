#ifndef PPM_LOADER_H_
#define PPM_LOADER_H_
#pragma once


#include <stdlib.h>
#include <stdio.h>
#include "cases.h"

char* ppm_loadImage(char path[]);
void ppm_handleComments(FILE *image);
void ppm_gotoEndOfLine(FILE* image);
int ppm_checkValidType(char buffer[]);
#endif //PPM_LOADER_H_
