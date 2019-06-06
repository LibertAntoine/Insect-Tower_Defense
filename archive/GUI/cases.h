#ifndef CASES_H_
#define CASES_H_
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "structures.h"

void get_casesi(int *caseX, int *caseY, Div *plateau);
void get_casesf(float *caseX, float *caseY, Div *plateau);

#endif //CASES_H_
