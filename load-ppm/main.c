#include <stdio.h>
#include <stdlib.h>

#include "ppm-loader.h"

int main(int argc, char *argv[])
{
  if (ppm_loadImage(argv[1])) {
    printf("All good, image loaded\n");
  }
}
