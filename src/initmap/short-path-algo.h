#ifndef SHORT_PATH_ALGO_H_
#define SHORT_PATH_ALGO_H_

#include "cases.h"
#include "itd-file.h"
#include "math.h"

extern Plateau* plateau;

int getShortPath(InfosNodes* infosNodes);
void fill(int* array, int size, int value);
double distanceNodes(Node StartNode, Node ArrivedNode);

#endif //SHORT_PATH_ALGO_H_
