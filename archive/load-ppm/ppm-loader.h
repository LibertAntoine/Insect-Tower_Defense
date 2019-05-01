#ifndef PPM_LOADER_H_
#define PPM_LOADER_H_

#include <stdlib.h>
#include <stdio.h>

char* ppm_loadImage(char path[], int* Xcases, int* Ycases);
/**
 * @brief Fonction récursive qui lorsqu'elle trouve un '#' à l'endroit du curseur, l'avance jusqu'à la prochaine et se rappelle elle même.
 * S'il n'y a pas de '#', replace le curseur en position initiale.
 * @param[in] image le fichier .ppm
 */
void ppm_handleComments(FILE *image);
void ppm_gotoEndOfLine(FILE* image);
int ppm_checkValidType(char buffer[]);
#endif //PPM_LOADER_H_
