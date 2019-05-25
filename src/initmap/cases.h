#ifndef CASES_H_
#define CASES_H_

#ifdef _WIN32
    #include <GL/glew.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <stdio.h>

#include "structures.h"

#include "itd-file.h"
#include "ppm-loader.h"
#include "tour.h"
#include "player.h"
#include "monster.h"


extern Plateau *plateau;

/** 
 * @brief Remplis les informations de cases de la structure plateau.
 * @param[in] mapData données du fichier .itd.
 */
int case_initPlateau(MapData* mapdata);
int case_RGBCompare(RGBcolor color1, RGBcolor color2);

int case_getCaseIndex(int caseX, int caseY);
void case_getCasePosition(int caseIndex, int* caseX, int* caseY);
TypeCase case_getType(int caseX, int caseY);
int case_getCaseCoordFromPixels(int positionX, int positionY, int *caseX, int *caseY, int px_width, int px_height);
GeneralType case_getGeneralConstructionType(TypeCase type);
int case_isConstructible(int caseX, int caseY);
void case_update(int caseX, int caseY, TypeCase newType);
int case_isUserPlaced(int caseX, int caseY);
void case_removeConstruction(int caseX, int caseY);
void case_addConstruction(int caseX, int caseY);
void case_printInfos(int caseX, int caseY);
Tour* case_getTourPointer(int caseX, int caseY);

void case_checkChemin(MapData* mapData);
void case_checkExistChemin(ListChemins* listChemins, Node* node_in, Node* node_out);
void case_addChemin(ListChemins* listChemins, Node* node_in, Node* node_out);
void case_addValueChemin(Monster* monster);
void case_removeValueChemin(Monster* monster);
Chemin* case_giveChemin(Node* firstNode, Node* secondNode);

#endif //CASES_H_

