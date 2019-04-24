#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRST_PARAMETER_ARG 1

/**
 * Bit flags used to check that MapData is properly filled
 */
enum MapDataContent {
  MDATA_IMG = 1,
  MDATA_ENERGY = 2,
  MDATA_IN = 4,
  MDATA_OUT = 8,
  MDATA_PATH = 16,
  MDATA_CONSTRUCT = 32,
  MDATA_NODE = 64,
};

enum Operations {
  CHK_SUCCESS = 0,
  CHK_ERROR_ALLOC = 1,
  CHK_ERROR_FILE = 2
} Operations;

typedef enum Bool {
  FALSE = 0,
  TRUE = 1
} Bool;

typedef struct RGBcolor {
  char red;
  char green;
  char blue;
} RGBcolor;

typedef struct MapData {
  char* mapFile;
  int energy;
  RGBcolor pathCol;
  RGBcolor nodeCol;
  RGBcolor buildingCol;
  RGBcolor inCol;
  RGBcolor outCol;
  unsigned char contentState; 
} MapData;


/**
 * Create a MapData of an empty state
 * param[out] MapData 
 */
MapData* itd_initMapData()
{
  MapData* mapData = malloc(sizeof(MapData));
  if (!mapData) {
    return CHK_ERROR_ALLOC;
  }

  mapData->contentState = 0;

  return mapData;
}

/**
 * Move specific file cursor to the end of the current line
 * @param[in] file
 */
void itd_gotoEndOfLine(FILE* file)
{
  char crtChar = (char) fgetc(file);
  while(crtChar != '\n' && crtChar != EOF) {
    crtChar = fgetc(file);
  }
}

/**
 * Fill an array with RGB color data found in file
 * param[in] file
 * param[in] * RGBcolor empty 
 */
int itd_getColor(FILE* file, MapData* mapData) {
  int red;
  int green;
  int blue;
  int noOfColors = fscanf(file, "%d %d %d", &red, &green, &blue);
  if (noOfColors != 3) {
    return CHK_ERROR_FILE;
  }
  else {
    if (red > 255 || red < 0) {
      return CHK_ERROR_FILE;
    }
    else if (green > 255 || green < 0) {
      return CHK_ERROR_FILE;
    }
    else if (blue > 255 || blue < 0) {
      return CHK_ERROR_FILE;
    }

    else {
      mapData->pathCol.red = red;
      mapData->pathCol.green = green;
      mapData->pathCol.blue = blue;
      return CHK_SUCCESS;
    }
  }
}

/**
 * Extract a single file path
 * param[in] file
 * param[in] * MapData
 * param[out] * MapData updated if the line is valid
 *
 * TODO check whether it's a .ppm otherwise throw an error
 */
int itd_getImageFilePath(FILE* file, MapData* mapData)
{
  char currentChar;

  do {
    currentChar = fgetc(file);
  } while (currentChar == ' ');

  fseek(file, -1, SEEK_CUR); // We're at the beginning of the 'supposed' file path
  int letterCount = 0;
  do {
    letterCount++;
    currentChar = fgetc(file);
  } while (currentChar != '\n' && currentChar != EOF);

  if (letterCount == 0) {
    return CHK_ERROR_FILE;
  }
  else {
    char* filePath = malloc(sizeof(char) * letterCount);
    if (!filePath) {
      return CHK_ERROR_ALLOC;
    }

    int i;
    fseek(file, -letterCount, SEEK_CUR);
    for (i=0; i<letterCount -1; i++) {
      currentChar = fgetc(file);
      filePath[i] = currentChar; 
    }
    filePath[i+1] = '\0';

    mapData->mapFile = filePath;
    return CHK_SUCCESS;
  }
}

/**
 * Extract a single decimal value
 * param[in] file
 * param[in] * MapData
 * param[out] * MapData updated if the line is valid
 */
int itd_getEnergyValue(FILE* file, MapData* mapData)
{
  int energy;
  if(fscanf(file, "%d", &energy)) {
    mapData->energy = energy;
    return CHK_SUCCESS;
  }
  else {
    return CHK_ERROR_FILE;
  }
}

/**
 * Verify whether it is a keyword, if so, check it's value
 * The function sets the cursor back in it's original position if the line is invalid
 * In case it's of another type
 * param[in] file
 * param[in] * MapData
 * param[out] * MapData updated if the line is valid
 */
int itd_checkForMapData(FILE* file, MapData* mapData)
{
  int originalPosition = ftell(file);
  char label[15];

  if (fscanf(file, "%s", label)) {

    if (strcmp("carte", label) == 0) {
      if (itd_getImageFilePath(file, mapData) == CHK_SUCCESS) {
        mapData->contentState |= MDATA_IMG;
        return CHK_SUCCESS;
      }

      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("energie", label) == 0) {
      if (itd_getEnergyValue(file, mapData) == CHK_SUCCESS) {
        mapData->contentState |= MDATA_ENERGY;
        return CHK_SUCCESS;
      }

      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("chemin", label) == 0) {
      if (itd_getColor(file, mapData) == CHK_SUCCESS) {
        mapData->contentState |= MDATA_PATH;
        return CHK_SUCCESS;
      }

      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("noeud", label) == 0) {
      if (itd_getColor(file, mapData) == CHK_SUCCESS) {
        mapData->contentState |= MDATA_NODE;
        return CHK_SUCCESS;
      }

      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }
    if (strcmp("construct", label) == 0) {
      if (itd_getColor(file, mapData) == CHK_SUCCESS) {
        mapData->contentState |= MDATA_CONSTRUCT;
        return CHK_SUCCESS;
      }

      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("in", label) == 0) {
      if (itd_getColor(file, mapData) == CHK_SUCCESS) {
        mapData->contentState |= MDATA_IN;
        return CHK_SUCCESS;
      }

      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("out", label) == 0) {
      if (itd_getColor(file, mapData) == CHK_SUCCESS) {
        mapData->contentState |= MDATA_OUT;
        return CHK_SUCCESS;
      }

      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

  }

  else {
    fseek(file, originalPosition, SEEK_SET);
    return CHK_ERROR_FILE;
  }
}

/**
 * Pass commented lines that use '#' sign
 * param[in]
 */
void  itd_checkComment(FILE* file)
{
  char crtChar = fgetc(file);
  if (crtChar == '#') {
    itd_gotoEndOfLine(file);
  }
  else {
    fseek(file, -1, SEEK_CUR);
  }
}

/**
 * Treats .itd files code @ITD {num}
 * @param[in] file
 */
int itd_checkCode(FILE* file)
{
  if (fgetc(file) != '@') {
    return CHK_ERROR_FILE;
  }

  char itd[] = "ITD";
  char name[4];
  fscanf(file, "%s", name);
  if (strcmp(name, itd)) {
    return CHK_ERROR_FILE;
  } 

  int version;
  fscanf(file, "%d", &version);
  switch(version) {
    case 1:
      printf("v1\n");
      break;
    default:
      return CHK_ERROR_FILE;

  }
  return CHK_SUCCESS;
}

int main(int argc, char* argv[])
{
  FILE* file = fopen(argv[FIRST_PARAMETER_ARG], "r");
  if (!file) {
    printf("Cound't open the file %s\n", argv[FIRST_PARAMETER_ARG]);
  }
  else {
    fseek(file, 0, SEEK_END);
    int totalSizeofFile = ftell(file);
    printf("size of file = %d\n", totalSizeofFile);
    fseek(file, 0, SEEK_SET);

    MapData* mapData = itd_initMapData();

    if(itd_checkCode(file)) {
      // ERROR file code doesn't match ITD
    }
    else {
      printf("correct file ITD\n");
      itd_gotoEndOfLine(file);
    }

    while (ftell(file) != totalSizeofFile) {
      itd_checkComment(file);
      itd_checkForMapData(file, mapData);

      printf("pos : %ld %c\n", ftell(file), fgetc(file));
    }

    int allFlags = (MDATA_IMG | MDATA_ENERGY | MDATA_IN | MDATA_OUT | MDATA_PATH | MDATA_NODE | MDATA_CONSTRUCT);
    if (mapData->contentState == allFlags) {
      printf("file is valid\n");
    }
  }
}
