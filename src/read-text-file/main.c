#include <stdlib.h> #include <stdio.h>

int main(int argc, char* argv[]) {
  FILE* file = NULL;
  file = fopen(argv[1], "r");
  if (!file) {
    printf("File can't be loaded!");
    return EXIT_FAILURE;
  }
  else {
    printf("Successfully loaded %s\n", argv[1]);

    if (fclose(file) == 0) {
      printf("File closed\n");
    }
  }

}
