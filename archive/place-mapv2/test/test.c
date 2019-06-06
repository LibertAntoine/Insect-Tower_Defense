#include <stdlib.h>
#include "testa.h"

Struct *myStruct = NULL;

int main()
{
  init_Struct();

  myStruct->num = 21;
  myStruct->classicArray[1].numInArray1 = 100;
  myStruct->arrayStruct[1].numInArray1 = 200;
  myStruct->arrayStruct[1].numInArray2 = 400;
}
