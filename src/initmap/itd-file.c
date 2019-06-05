#include "itd-file.h"

void itd_initMapData()
{
  mapData = malloc(sizeof(MapData));
    if (!mapData) {
      printf("ERROR ALLOC : mapData");
      exit(CHK_ERROR_ALLOC);
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

int itd_getInfosNodes(FILE* file) 
{
  int nbNoeud;
  int noOfNoeud = fscanf(file, "%d", &nbNoeud);
  if (noOfNoeud != 1 || nbNoeud <= 0) {
    return CHK_ERROR_FILE;
  }
  else {
    itd_gotoEndOfLine(file);
    Node* nodes = malloc(sizeof(Node)*nbNoeud);
    if (!nodes) {
      printf("ERROR ALLOC : nodes");
      exit(CHK_ERROR_ALLOC);
    }
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
    if (!infosNodes) {
      printf("ERROR ALLOC : infosNodes");
      exit(CHK_ERROR_ALLOC);
    }

    infosNodes->nbNoeud = nbNoeud;
    infosNodes->nodes = nodes;
    infosNodes->entrance_total = entrance_total;
    infosNodes->idOut = idOut;
    mapData->infosNodes = infosNodes;

    getIdEntrees();

    fseek(file, -1, SEEK_CUR);
    return CHK_SUCCESS;
  }
}

int itd_getMonstersData(FILE* file, TypeCase type) 
{
  float PDV;
  float strength;
  double mass;
  int value;
  int noOfColors = fscanf(file, "%f %f %lf %d", &PDV, &strength, &mass, &value);
  if (noOfColors != 4) {
    return CHK_ERROR_FILE;
  }
  else {
    mapData->dataMonsters[type].PDV = PDV;
    mapData->dataMonsters[type].strength = strength;
    mapData->dataMonsters[type].mass = mass;
    mapData->dataMonsters[type].value = value;
    return CHK_SUCCESS;
  }
}

int itd_getConstructionData(FILE* file, TypeCase type) 
{
  int degats;
  int alimentation;
  int cadence;
  int portee;
  int range;
  int valeur_achat;
  int valeur_revente;
  int noOfColors = fscanf(file, "%d %d %d %d %d %d %d", &degats, &alimentation, 
  &cadence, &portee, &range, &valeur_achat, &valeur_revente);
  if (noOfColors != 7) {
    return CHK_ERROR_FILE;
  }
  else {
    mapData->constructionData[type].type = type;
    mapData->constructionData[type].degats = degats;
    mapData->constructionData[type].alimentation = alimentation;
    mapData->constructionData[type].cadence = cadence;
    mapData->constructionData[type].portee = portee;
    mapData->constructionData[type].range = range;
    mapData->constructionData[type].valeur_achat = valeur_achat;
    mapData->constructionData[type].valeur_revente = valeur_revente;
    return CHK_SUCCESS;
  }
}


int getIdEntrees() 
{
  int* idEntrees = malloc(sizeof(int)*mapData->infosNodes->entrance_total);
  if (!idEntrees) {
    printf("ERROR ALLOC : idEntrees");
    exit(CHK_ERROR_ALLOC);
  }

  int j = 0;
  for (int i = 0; i < mapData->infosNodes->nbNoeud; i++)
  {
    if(mapData->infosNodes->nodes[i].type == 2) {
      idEntrees[j] = mapData->infosNodes->nodes[i].id;
      j++;
    }
  }
  if (mapData->infosNodes->entrance_total != j) {
    return CHK_ERROR_FILE;
  } else {
    mapData->infosNodes->idEntrees = idEntrees;
    return CHK_SUCCESS;
  }
}

int itd_getInfosWaves(FILE* file) 
{
  int wave_total;
  int noOfNoeud = fscanf(file, "%d", &wave_total);
  if (noOfNoeud != 1 || wave_total <= 0) {
    return CHK_ERROR_FILE;
  } else {
    itd_gotoEndOfLine(file);
    ListWaves* listWaves = malloc(sizeof(ListWaves));
    if (!listWaves) {
      printf("ERROR ALLOC : listWaves");
      exit(CHK_ERROR_ALLOC);
    }

    listWaves->wave_total = wave_total;
    listWaves->next = NULL;

    for (int wave_id = 0; wave_id < wave_total; wave_id++) {
      Wave* wave = NULL;
      wave = malloc(sizeof(Wave));
      if (!wave) {
        printf("ERROR ALLOC : wave");
        exit(CHK_ERROR_ALLOC);
      }   

      int wave_id;
      float timeBeforeNext, freq_pop, random;
      int nbSolder, nbHugeSolder, nbGeneral, nbBoss;
      itd_checkComment(file);

      char line[100];

      fgets(line, 100, file);
      if(sscanf(line, "%d %f %f %f %d %d %d %d", &wave_id, &timeBeforeNext, &freq_pop, &random, 
            &nbSolder, &nbHugeSolder, &nbGeneral, &nbBoss)) {
        wave->wave_id = wave_id;
        wave->timeBeforeNext = timeBeforeNext;
        wave->freq_pop = freq_pop;
        wave->nextMonster_timer = freq_pop;
        wave->random = random;
        wave->monster_total = nbSolder + nbHugeSolder + nbGeneral + nbBoss;
        wave->next = NULL;
        TypeMonster* monsters = malloc(sizeof(TypeMonster) * wave->monster_total);
        if (!monsters) {
          printf("ERROR ALLOC : monsters");
          exit(CHK_ERROR_ALLOC);
        }

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

        wave->monsters = monsters;

        addToWaves(listWaves, wave);
      }
    }

    mapData->listWaves = listWaves;
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




int itd_getImageFilePath(FILE* file)
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
      printf("ERROR ALLOC : filePath");
      exit(CHK_ERROR_ALLOC);
    }

    int i;
    #ifdef _WIN32
      fseek(file, -letterCount -2, SEEK_CUR);
    #else
      fseek(file, -letterCount -1, SEEK_CUR);
    #endif
    
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

int itd_getEnergyValue(FILE* file)
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

int itd_checkForMapData(FILE* file)
{
  int originalPosition = ftell(file);
  char label[15];

  if (fscanf(file, "%s", label)) {
    RGBcolor* color = malloc(sizeof(RGBcolor));
    if (!color) {
      printf("ERROR ALLOC : color");
      exit(CHK_ERROR_ALLOC);
    }
    if (strcmp("carte", label) == 0) {
      if (itd_getImageFilePath(file) == CHK_SUCCESS) {
        mapData->contentState |= MDATA_IMG;
        return CHK_SUCCESS;
      }

      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("energie", label) == 0) {
      if (itd_getEnergyValue(file) == CHK_SUCCESS) {
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
    if (strcmp("inconstructible", label) == 0) {
      if (itd_getColor(file, color) == CHK_SUCCESS) {
        mapData->inconstructibleCol = *color;
        mapData->contentState |= MDATA_INCONSTRUCTIBLE;
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
      if (itd_getInfosNodes(file) == CHK_SUCCESS) {
        mapData->contentState |= MDATA_INFOSNODE;
        return CHK_SUCCESS;
      }
      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("laser", label) == 0) {
      if (itd_getConstructionData(file, LASER) == CHK_SUCCESS) {
        return CHK_SUCCESS;
      }
      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("missile", label) == 0) {
      if (itd_getConstructionData(file, MISSILE) == CHK_SUCCESS) {
        return CHK_SUCCESS;
      }
      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("radar", label) == 0) {
      if (itd_getConstructionData(file, RADAR) == CHK_SUCCESS) {
        return CHK_SUCCESS;
      }
      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("armement", label) == 0) {
      if (itd_getConstructionData(file, ARMEMENT) == CHK_SUCCESS) {
        return CHK_SUCCESS;
      }
      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("centrale", label) == 0) {
      if (itd_getConstructionData(file, CENTRALE) == CHK_SUCCESS) {
        return CHK_SUCCESS;
      }
      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("solder", label) == 0) {
      if (itd_getMonstersData(file, SOLDER) == CHK_SUCCESS) {
        return CHK_SUCCESS;
      }
      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("huge_solder", label) == 0) {
      if (itd_getMonstersData(file, HUGE_SOLDER) == CHK_SUCCESS) {
        return CHK_SUCCESS;
      }
      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("gereral", label) == 0) {
      if (itd_getMonstersData(file, GERERAL) == CHK_SUCCESS) {
        return CHK_SUCCESS;
      }
      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("boss", label) == 0) {
      if (itd_getMonstersData(file, BOSS) == CHK_SUCCESS) {
        return CHK_SUCCESS;
      }
      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("munition", label) == 0) {
      if (itd_getConstructionData(file, MUNITION) == CHK_SUCCESS) {
        return CHK_SUCCESS;
      }
      else {
        fseek(file, originalPosition, SEEK_SET);
        return CHK_ERROR_FILE;
      }
    }

    if (strcmp("waves", label) == 0) {
      if (itd_getInfosWaves(file) == CHK_SUCCESS) {
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


void idt_load(char* itd_path)
{
  itd_initMapData();

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
      itd_checkForMapData(file);
    }


    int allFlags = (MDATA_IMG | MDATA_ENERGY | MDATA_IN | MDATA_OUT | MDATA_PATH | MDATA_NODE | MDATA_CONSTRUCT | MDATA_INFOSNODE | MDATA_WAVES | MDATA_INCONSTRUCTIBLE);
    if (mapData->contentState == allFlags) {
      printf("file is valid\n");
      mapData->cases = case_loadFromPPM();
      mapData->listChemins = itineraire_initListChemins();
    }
  }
}


void itd_actionMenu(ButtonName button) {
  if(gameData->gameState == MAINMENU) {
    if (button == LEVEL1_BTN) {
      idt_load("level/level1.itd");
    } else if (button == LEVEL2_BTN) {
      idt_load("level/level2.itd");
    } else if (button == LEVEL3_BTN) {
      idt_load("level/level3.itd");
    } else {
      return EXIT_FAILURE;
    }
  itd_initLevel();
  gameData->gameState = LEVELPLAY;
  } else if (gameData->gameState == LOSEMENU || gameData->gameState == WINMENU) {
    if(button == MAINMENU_BTN) {
      itd_freeMapData();
      gameData->gameState = MAINMENU;
    } else if (button == REPLAY_BTN) {
      itd_initLevel();
      gameData->gameState = LEVELPLAY;
    }
  }
}

void itd_initLevel() 
{
  /* Création du plateau */
  case_initPlateau();
  player_checkTarifs();
  /* Calcul des chemins les plus courts */
  itineraire_findShortestPath();

  mapData->idGrid = glGenLists(1);
  display_gridList(mapData->idGrid);

  mapData->idMap = glGenLists(1);
  display_mapList(mapData->idMap);

  gameData->beginMomentLevel = SDL_GetTicks();

  Mix_PlayChannel(-1, gameData->sound[BEGINLEVEL], 0);
}

void itd_freeMapData() {
  wave_freeListWaves();
  itineraire_freeListChemins();
  free(mapData->infosNodes);
  free(mapData);
}

