#ifndef ITD_FILE_H_
#define ITD_FILE_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRST_PARAMETER_ARG 1

typedef struct RGBcolor {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} RGBcolor;

typedef struct Node {
  int id;
  int type;
  int x;
  int y;
  int link[4];
} Node;

typedef struct MapData {
  char* mapFile;
  int energy;
  int nbNoeud;
  RGBcolor pathCol;
  RGBcolor nodeCol;
  RGBcolor buildingCol;
  RGBcolor inCol;
  RGBcolor outCol;
  unsigned char contentState; 
  Node* nodes;
} MapData;

/**
 * @brief Initialise la structure de données qui contient le niveau actuel
 * @return MapData*
 */
MapData* itd_initMapData();

/**
 * @brief Avance le curseur de lecture du fichier à la fin de la ligne actuelle.
 * @param[in] file fichier .itd.
 */
void itd_gotoEndOfLine(FILE* file);

/**
 * @brief Si on rencontre le carractère '#', passer à la ligne suivante.
 * @param[in] file fichier .itd.
 */
void itd_checkComment(FILE* file);

/**
 * @brief Vérifie le code de fichier @ITD {{num}}.
 * @param[in] file fichier .itd.
 */
int itd_checkCode(FILE* file);

/**
 * Extract a single file path
 * param[in] file
 * param[in] * MapData
 * param[out] * MapData updated if the line is valid
 *
 * TODO check whether it's a .ppm otherwise throw an error
 */
int itd_getImageFilePath(FILE* file, MapData* mapData);

/**
 * Extract a single decimal value
 * param[in] file
 * param[in] * MapData
 * param[out] * MapData updated if the line is valid
 */
int itd_getEnergyValue(FILE* file, MapData* mapData);

/**
 * Fill an array with RGB color data found in file
 * param[in] file
 * param[in] * RGBcolor empty 
 */
int itd_getColor(FILE* file, RGBcolor* RGBColor);

/**
 * Fill the number of noeud data found in file
 * param[in] file
 * param[in] * MapData MapData 
 */
int itd_getInfosNodes(FILE* file, MapData* MapData);

/**
 * @brief Lis la ligne en cours et remplis la structure MapData avec les données rencontrées.
 * Vérifie la validité de la ligne, si OK remet le curseur en position et commence le remplissage.
 * Sinon remet le curseur en position initiale.
 * @param[in] file fichier .itd.
 * param[in] mapData
 * param[out] mapData mis à jour si la ligne est bien valide
 */
int itd_checkForMapData(FILE* file, MapData* mapData);

/**
 * @brief Vérifie la validité du fichier .itd et parcours le fichier
 */
void idt_load(char* itdFile, MapData* mapData);

#endif //PPM_LOADER_H_
