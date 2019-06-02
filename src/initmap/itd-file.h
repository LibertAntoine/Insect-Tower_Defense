#ifndef ITD_FILE_H_
#define ITD_FILE_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cases.h>
#include <itineraire.h>
#include <display.h>
#include <waves.h>

#include "structures.h"

#define FIRST_PARAMETER_ARG 1


/**
 * Create a MapData of an empty state
 */
void itd_initMapData();

/**
 * Move specific file cursor to the end of the current line
 * @param[in] file itd
 */
void itd_gotoEndOfLine(FILE* file);

/**
 * Pass commented lines that use '#' sign
 * param[in] file itd
 */
void itd_checkComment(FILE* file);

/**
 * Treats .itd files code @ITD {num}
 * @param[in] file itd
 */
int itd_checkCode(FILE* file);

/**
 * Extract a single file path
 * param[in] file itd
 */
int itd_getImageFilePath(FILE* file);

/**
 * Extract a single decimal value
 * param[in] file itd
 */
int itd_getEnergyValue(FILE* file);

/**
 * Fill an array with RGB color data found in file
 * param[in] file itd
 * param[in] * RGBcolor empty 
 */
int itd_getColor(FILE* file, RGBcolor* color);

/**
 * Fill the data contruction found in file
 * param[in] file itd
 * param[in] the data construction type of infos
 */
int itd_getConstructionData(FILE* file, TypeCase type);

/**
 * Fill the number of noeud data found in file
 * param[in] file itd
 */
int itd_getInfosNodes(FILE* file);

/**
 * Find the id of entrees cases
 */
int getIdEntrees();


/**
 * Fill the waves infos found in file
 * param[in] file
 */
int itd_getInfosWaves(FILE* file);

/**
 * Add waves of listWaves of the level
 * param[in] listWaves
 * param[in] wave to add.
 */
int addToWaves(ListWaves* listWaves, Wave* wave);

/**
 * Verify whether it is a keyword, if so, check it's value
 * The function sets the cursor back in it's original position if the line is invalid
 * In case it's of another type
 * param[in] file
 */
int itd_checkForMapData(FILE* file);

/**
 * Recup the infos contains in the idt file
 * param[in] string of itd_path
 */
void idt_load(char* itd_path);

/**
 * Active an action of one menu of the game
 * param[in] button name on click
 */
void itd_actionMenu(ButtonName button);

/**
 * init the gameData in plateau after the idt/ppm load
 */
void itd_initLevel();

/**
 * free the mapData structure (when the level is quit)
 */
void itd_freeMapData();

#endif //PPM_LOADER_H_
