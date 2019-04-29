#include "itd-file.h"

enum MapDataContent {
  MDATA_IMG = 1,
  MDATA_ENERGY = 2,
  MDATA_IN = 4,
  MDATA_OUT = 8,
  MDATA_PATH = 16,
  MDATA_CONSTRUCT = 32,
  MDATA_NODE = 64,
  MDATA_INFOSNODE = 128,
  MDATA_WAVES = 256
};

enum Operations {
  CHK_SUCCESS = 0,
  CHK_NULL = 0,
  CHK_ERROR_ALLOC = 1,
  CHK_ERROR_FILE = 2
} Operations;

typedef enum Bool {
  FALSE = 0,
  TRUE = 1
} Bool;

MapData* itd_initMapData()
{
  MapData* mapData = malloc(sizeof(MapData));
  if (!mapData) {
    printf("ERROR ALLOC : mapData");
  } else {
  mapData->contentState = 0;
  return mapData;
  }
}

void itd_gotoEndOfLine(FILE* file)
{
  char crtChar = (char) fgetc(file);
  while(crtChar != '\n' && crtChar != EOF) {
    crtChar = fgetc(file);
  }
}

void itd_checkComment(FILE* file)
{
  char crtChar = fgetc(file);
  if (crtChar == '#') {
    itd_gotoEndOfLine(file);
  }
  else {
    fseek(file, -1, SEEK_CUR);
  }
}

int itd_checkCode(FILE* file)
{
  if (fgetc(file) != '@') {
    return CHK_ERROR_FILE;
  }

  char itd[] = "ITD";
  char name[4];
  fscanf_s(file, "%s", name, _countof(name));
  if (strcmp(name, itd)) {
    return CHK_ERROR_FILE;
  } 

  int version;
  fscanf_s(file, "%d", &version);
  switch(version) {
    case 1:
      printf("v1\n");
      break;
    default:
      return CHK_ERROR_FILE;

  }
  return CHK_SUCCESS;
}

int itd_getColor(FILE* file, RGBcolor* RGBColor) {
  int red;
  int green;
  int blue;
  int noOfColors = fscanf_s(file, "%d %d %d", &red, &green, &blue);
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
      RGBColor->red = red;
      RGBColor->green = green;
      RGBColor->blue = blue;
      return CHK_SUCCESS;
    }
  }
}

int itd_getInfosNodes(FILE* file, MapData* MapData) {
  int nbNoeud;
  int noOfNoeud = fscanf_s(file, "%d", &nbNoeud);
  if (noOfNoeud != 1 || nbNoeud <= 0) {
    return CHK_ERROR_FILE;
  }
  else {
    itd_gotoEndOfLine(file);
    Node* nodes = malloc(sizeof(Node)*nbNoeud);
    int nbEntree = 0;
    int idOut = -1;
    for (int i = 0; i < nbNoeud; i++)
    {
      int id, type;
      double x, y;
      int connect[4] = {-1, -1, -1, -1};
      itd_checkComment(file);
      char line[100];
      fgets(line, 100 ,file);
      if(sscanf(line, "%d %d %lf %lf %d %d %d %d", &id, &type, &x, &y, 
      &connect[0], &connect[1], &connect[2], &connect[3])) {
        nodes[i].id = id;
        nodes[i].type = type;
        nodes[i].x = x;
        nodes[i].y = y;
        nodes[i].link[0] = connect[0];
        nodes[i].link[1] = connect[1];
        nodes[i].link[2] = connect[2];
        nodes[i].link[3] = connect[3];
        if(type == 2) {
          nbEntree++;
        } else if (type == 3) {
            if (idOut == -1) {
              idOut = id;
            } else {
              return CHK_ERROR_FILE;
            }
        }
      } else {
        return CHK_ERROR_FILE;
      }
    }
    
    if (nbEntree <= 0 || nbEntree > nbNoeud - 1) {
      
      return CHK_ERROR_FILE;
    }
    if (idOut == -1) {
      
      return CHK_ERROR_FILE;
    }
    InfosNodes* infosNodes = malloc(sizeof(InfosNodes));
    infosNodes->nbNoeud = nbNoeud;
    infosNodes->nodes = nodes;
    infosNodes->nbEntrees = nbEntree;
    infosNodes->idOut = idOut;
    MapData->infosNodes = infosNodes;
    getIdEntrees(MapData);
    return CHK_SUCCESS;
  }
}

int getIdEntrees(MapData* mapdata) {
    int* idEntrees = malloc(sizeof(int)*mapdata->infosNodes->nbEntrees);
    int j = 0;
    for (int i = 0; i < mapdata->infosNodes->nbNoeud; i++)
    {
        if(mapdata->infosNodes->nodes[i].type == 2) {
            idEntrees[j] = mapdata->infosNodes->nodes[i].id;
            j++;
        }
    }
    if (mapdata->infosNodes->nbEntrees != j) {
        return CHK_ERROR_FILE;
    } else {
        mapdata->infosNodes->idEntrees = idEntrees;
        return CHK_SUCCESS;
    }
}

int itd_getInfosWaves(FILE* file, MapData* MapData) {
  int nbWaves;
  int noOfNoeud = fscanf_s(file, "%d", &nbWaves);
  if (noOfNoeud != 1 || nbWaves <= 0) {
    return CHK_ERROR_FILE;
  } else {
    itd_gotoEndOfLine(file);
    ListWaves* listWaves = malloc(sizeof(ListWaves));
    listWaves->nbWaves = nbWaves;
    listWaves->next = NULL;
    
    for (int k = 0; k < nbWaves; k++)
    {
      Wave* wave = NULL;
      wave = malloc(sizeof(Wave));
      if (!wave) {
        printf("ERROR ALLOC : mapData");
      }   
      int nbWave;
      float timeBegin, freq, random;
      int nbSolder, nbHugeSolder, nbGeneral, nbBoss;
      itd_checkComment(file);
      
      char line[100];
      fgets (line, 100 ,file);
      
      if(sscanf(line, "%d %f %f %f %d %d %d %d", &nbWave, &timeBegin, &freq, &random, 
      &nbSolder, &nbHugeSolder, &nbGeneral, &nbBoss)) {
        
        wave->nbWave = nbWave;
        wave->timeBegin = timeBegin;
        wave->freq = freq;
        wave->nextMonster = freq;
        wave->random = random;
        wave->nbMonster = nbSolder + nbHugeSolder + nbGeneral + nbBoss;
        wave->next = NULL;
        int* monsters = malloc(sizeof(int)*wave->nbMonster);
        
        int i = 0;
        for (i ; i < nbSolder ; i++) {

            monsters[i] = SOLDER;
        }
        
        int j = i + nbHugeSolder;
        for (i ; i < j ; i++) {
            monsters[i] = HUGE_SOLDER;
        }
        j = i + nbGeneral;
        for (i ; i < j ; i++) {
            monsters[i] = GERERAL;
        }
        j = i + nbBoss;
        for (i ; i < j ; i++) {
            monsters[i] = BOSS;
        }
        
        if(i != wave->nbMonster) {
          
          return CHK_ERROR_FILE;
        }
        
        wave->monsters = monsters;
        
        addToWaves(listWaves, wave);

      }
    }
    MapData->listWaves = listWaves;
    return CHK_SUCCESS;
  }  
}


int addToWaves(ListWaves* listWaves, Wave* wave) {
  
    if(listWaves->next == NULL) {
        listWaves->next = wave;
        return 0;
    }
    
    Wave* currentWave = listWaves->next;
    while (currentWave->next != NULL)
        {  
            currentWave = currentWave->next;
        }
    currentWave->next = wave;
    return 0;
}




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
    fseek(file, -letterCount -1, SEEK_CUR);
    for (i=0; i<letterCount-1; i++) {
      currentChar = fgetc(file);
      filePath[i] = currentChar; 
    }
    filePath[i] = '\0';
    mapData->mapFile = filePath;
    return CHK_SUCCESS;
  }
}

int itd_getEnergyValue(FILE* file, MapData* mapData)
{
  int energy;
  if(fscanf_s(file, "%d", &energy)) {
    mapData->energy = energy;
    return CHK_SUCCESS;
  }
  else {
    return CHK_ERROR_FILE;
  }
}

int itd_checkForMapData(FILE* file, MapData* mapData)
{
  int originalPosition = ftell(file);
  char label[15];
  
  if (fscanf_s(file, "%s", label, _countof(label))) {
    RGBcolor* color = malloc(sizeof(RGBcolor));
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
      if (itd_getColor(file, color) == CHK_SUCCESS) {
        mapData->pathCol = *color;
        mapData->contentState |= MDATA_PATH;
        return CHK_SUCCESS;
      }

      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("noeud", label) == 0) {
      if (itd_getColor(file, color) == CHK_SUCCESS) {
        mapData->nodeCol = *color;
        mapData->contentState |= MDATA_NODE;
        return CHK_SUCCESS;
      }

      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }
    if (strcmp("construct", label) == 0) {
      if (itd_getColor(file, color) == CHK_SUCCESS) {
        mapData->buildingCol = *color;
        mapData->contentState |= MDATA_CONSTRUCT;
        return CHK_SUCCESS;
      }

      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("in", label) == 0) {
      if (itd_getColor(file, color) == CHK_SUCCESS) {
        mapData->inCol = *color;
        mapData->contentState |= MDATA_IN;
        return CHK_SUCCESS;
      }

      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("out", label) == 0) {
      if (itd_getColor(file, color) == CHK_SUCCESS) {
        mapData->outCol = *color;
        mapData->contentState |= MDATA_OUT;
        return CHK_SUCCESS;
      }

      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("infosNodes", label) == 0) {
      if (itd_getInfosNodes(file, mapData) == CHK_SUCCESS) {
        mapData->contentState |= MDATA_INFOSNODE;
        return CHK_SUCCESS;
      }
      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("aves", label) == 0) {
      
      if (itd_getInfosWaves(file, mapData) == CHK_SUCCESS) {
        mapData->contentState |= MDATA_WAVES;
        return CHK_SUCCESS;
      }

      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }
    return CHK_NULL;
  }

  else {
    fseek(file, originalPosition, SEEK_SET);
    return CHK_ERROR_FILE;
  }
}


void idt_load(char* itdFile, MapData* mapData)
{
    FILE* file = fopen(itdFile, "r");
    if (!file) {
    printf("Cound't open the file %s\n", itdFile);
    } else {
    fseek(file, 0, SEEK_END);
    int totalSizeofFile = ftell(file);
    // printf("size of file = %d\n", totalSizeofFile);
    fseek(file, 0, SEEK_SET);

    if(itd_checkCode(file)) {
      // ERROR file code doesn't match ITD
    }
    else {
      printf("correct file ITD\n");
      itd_gotoEndOfLine(file);
    }

    while (fgetc(file) != EOF) {
      itd_checkComment(file);
      itd_checkForMapData(file, mapData);
      //printf("pos : %ld %c\n", ftell(file), fgetc(file));
    }


    int allFlags = (MDATA_IMG | MDATA_ENERGY | MDATA_IN | MDATA_OUT | MDATA_PATH | MDATA_NODE | MDATA_CONSTRUCT | MDATA_INFOSNODE | MDATA_WAVES);
    if (mapData->contentState == allFlags) {
      printf("file is valid\n");
    }
  }
}



