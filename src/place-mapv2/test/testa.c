#include "testa.h"

//Struct *myStruct;


void init_Struct()
{
  myStruct = malloc(sizeof(Struct));
  myStruct->num = 22;

  myStruct->arrayStruct = malloc(sizeof(Array) * 2);
  myStruct->arrayInt = malloc(sizeof(int) * 2);
}
