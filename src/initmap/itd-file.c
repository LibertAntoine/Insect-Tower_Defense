#include "itd-file.h"

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
    itd_checkComment(file);
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

int itd_getColor(FILE* file, RGBcolor* RGBColor) {
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
      RGBColor->red = red;
      RGBColor->green = green;
      RGBColor->blue = blue;
      return CHK_SUCCESS;
    }
  }
}

int itd_getInfosNodes(FILE* file, MapData* MapData) {
  int nbNoeud;
  int noOfNoeud = fscanf(file, "%d", &nbNoeud);
  if (noOfNoeud != 1 || nbNoeud <= 0) {
    return CHK_ERROR_FILE;
  }
  else {
    itd_gotoEndOfLine(file);
    Node* nodes = malloc(sizeof(Node)*nbNoeud);
    // TODO: Checker l'allocation.
    int entrance_total = 0;
    int idOut = -1;
    for (int i = 0; i < nbNoeud; i++)
    {
      int id, type;
      double x, y;
      int connect[4] = {-1, -1, -1, -1};
      itd_checkComment(file);
      char line[100];
      fgets(line, 100, file);
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
          entrance_total++;
        }
        else if (type == 3) {
          if (idOut == -1) {
            idOut = id;
          } else {
            return CHK_ERROR_FILE;
          }
        }
      }
      else {
        return CHK_ERROR_FILE;
      }
    }

    if (entrance_total <= 0 || entrance_total > nbNoeud - 1) {

      return CHK_ERROR_FILE;
    }
    if (idOut == -1) {

      return CHK_ERROR_FILE;
    }
    InfosNodes* infosNodes = malloc(sizeof(InfosNodes));
    //TODO: Checker allocation.

    infosNodes->nbNoeud = nbNoeud;
    infosNodes->nodes = nodes;
    infosNodes->entrance_total = entrance_total;
    infosNodes->idOut = idOut;
    MapData->infosNodes = infosNodes;

    getIdEntrees(MapData);

    fseek(file, -1, SEEK_CUR);
    return CHK_SUCCESS;
  }
}

int getIdEntrees(MapData* mapdata) {
  int* idEntrees = malloc(sizeof(int)*mapdata->infosNodes->entrance_total);
  //TODO: Checker allocation.

  int j = 0;
  for (int i = 0; i < mapdata->infosNodes->nbNoeud; i++)
  {
    if(mapdata->infosNodes->nodes[i].type == 2) {
      idEntrees[j] = mapdata->infosNodes->nodes[i].id;
      j++;
    }
  }
  if (mapdata->infosNodes->entrance_total != j) {
    return CHK_ERROR_FILE;
  } else {
    mapdata->infosNodes->idEntrees = idEntrees;
    return CHK_SUCCESS;
  }
}

int itd_getInfosWaves(FILE* file, MapData* MapData) {
  int wave_total;
  int noOfNoeud = fscanf(file, "%d", &wave_total);
  if (noOfNoeud != 1 || wave_total <= 0) {
    return CHK_ERROR_FILE;
  } else {
    itd_gotoEndOfLine(file);
    ListWaves* listWaves = malloc(sizeof(ListWaves));
    // TODO: Checker allocation.

    listWaves->wave_total = wave_total;
    listWaves->next = NULL;

    for (int wave_id = 0; wave_id < wave_total; wave_id++) {
      Wave* wave = NULL;
      wave = malloc(sizeof(Wave));
      if (!wave) {
        printf("ERROR ALLOC : mapData");
      }   

      int wave_id;
      float timeBegin, freq_pop, random;
      int nbSolder, nbHugeSolder, nbGeneral, nbBoss;
      itd_checkComment(file);

      char line[100];
      // TODO: Vérifier à quoi sert la ligne suivante :

      fgets(line, 100, file);
      if(sscanf(line, "%d %f %f %f %d %d %d %d", &wave_id, &timeBegin, &freq_pop, &random, 
            &nbSolder, &nbHugeSolder, &nbGeneral, &nbBoss)) {
        wave->wave_id = wave_id;
        wave->timeBegin = timeBegin;
        wave->freq_pop = freq_pop;
        wave->nextMonster_timer = freq_pop;
        wave->random = random;
        wave->monster_total = nbSolder + nbHugeSolder + nbGeneral + nbBoss;
        wave->next = NULL;
        TypeMonster* monsters = malloc(sizeof(TypeMonster) * wave->monster_total);
        // TODO: Checker allocation.


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

        // NOTE: cas impossible car monster_total = nbSolder + nbHugeSolder + ...;
        /*
           if(i != wave->monster_total) {

           return CHK_ERROR_FILE;
           }
         */

        wave->monsters = monsters;

        addToWaves(listWaves, wave);

      }
    }

    MapData->listWaves = listWaves;
    return CHK_SUCCESS;
  }  
}


int addToWaves(ListWaves* listWaves, Wave* wave)
{
  if(listWaves->next == NULL) {
    listWaves->next = wave;
    return 0;
  }

  Wave* currentWave = listWaves->next;
  while (currentWave->next != NULL) {  
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

  //fseek(file, -1, SEEK_CUR); // We're at the beginning of the 'supposed' file path
  int letterCount = 0;
  do {
    letterCount++;
    currentChar = fgetc(file);
  } while (currentChar != '\n' && currentChar != EOF);

  if (letterCount == 0) {
    return CHK_ERROR_FILE;
  }
  else {
    // NOTE: ici le chiffre 6 correspond à la longueure de "level/"
    char* filePath = malloc(sizeof(char) * (letterCount + 6));
    if (!filePath) {
      return CHK_ERROR_ALLOC;
    }

    int i;
    fseek(file, -letterCount -1, SEEK_CUR);
    strcpy(filePath, "level/");
    for (i=6; i<letterCount+6; i++) {
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
  if(fscanf(file, "%d", &energy)) {
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

  if (fscanf(file, "%s", label)) {
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

    if (strcmp("waves", label) == 0) {
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


MapData* idt_load(char* itd_path)
{
  MapData* mapData = itd_initMapData();

  FILE* file = fopen(itd_path, "r");

  if (!file) {
    printf("Cound't open the file %s\n", itd_path);
  } else {
    fseek(file, 0, SEEK_END);
    int totalSizeofFile = ftell(file);
    fseek(file, 0, SEEK_SET);

    if(itd_checkCode(file)) {
      //TODO: ERROR file code doesn't match ITD
    }
    else {
      printf("Correct file ITD\n");
      itd_gotoEndOfLine(file);
    }

    while (fgetc(file) != EOF) {
      itd_checkComment(file);
      itd_checkForMapData(file, mapData);
    }


    int allFlags = (MDATA_IMG | MDATA_ENERGY | MDATA_IN | MDATA_OUT | MDATA_PATH | MDATA_NODE | MDATA_CONSTRUCT | MDATA_INFOSNODE | MDATA_WAVES);
    if (mapData->contentState == allFlags) {
      printf("file is valid\n");
    }
  }
  return mapData;
}



