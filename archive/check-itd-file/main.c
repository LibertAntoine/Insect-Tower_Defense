#include <stdio.h>
#include <stdlib.h>

#include "itd-file.h"
int main(int argc, char *argv[])
{
  MapData* mapData = itd_initMapData();
  idt_load("level1.itd", mapData);
  printf("%d", mapData->nodes[0].link[0]);
}
