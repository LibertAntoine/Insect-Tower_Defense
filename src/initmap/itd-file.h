#ifndef ITD_FILE_H_
#define ITD_FILE_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"

#define FIRST_PARAMETER_ARG 1


/**
 * Create a MapData of an empty state
 * param[out] MapData 
 */
MapData* itd_initMapData();

/**
 * Move specific file cursor to the end of the current line
 * @param[in] file
 */
void itd_gotoEndOfLine(FILE* file);

/**
 * Pass commented lines that use '#' sign
 * param[in]
 */
void itd_checkComment(FILE* file);

/**
 * Treats .itd files code @ITD {num}
 * @param[in] file
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

int getIdEntrees(MapData* mapdata);

int itd_getInfosWaves(FILE* file, MapData* MapData);
int addToWaves(ListWaves* listWaves, Wave* wave);
/**
 * Verify whether it is a keyword, if so, check it's value
 * The function sets the cursor back in it's original position if the line is invalid
 * In case it's of another type
 * param[in] file
 * param[in] * MapData
 * param[out] * MapData updated if the line is valid
 */
int itd_checkForMapData(FILE* file, MapData* mapData);

void idt_load(char* itdFile, MapData* mapData);

#endif //PPM_LOADER_H_
