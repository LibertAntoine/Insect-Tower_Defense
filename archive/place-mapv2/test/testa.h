#include <stdlib.h>

typedef struct Array {
  int numInArray1;
  int numInArray2;
} Array;

typedef struct Struct {
  int num;
  Array classicArray[2];
  Array *arrayStruct;
  int *arrayInt;
} Struct;

extern Struct *myStruct;

void init_Struct();
