#include "cases.h"

int case_initPlateau(Plateau* plateau, MapData* mapdata)
{
  unsigned char* pixel_data;
  pixel_data = ppm_loadImage(mapdata->mapFile, &plateau->Xsplit, &plateau->Ysplit);
  /* NOTE: Energy correspond aux unités d'énergies produites par les centrales. ;-)
  if(plateau->Xsplit*plateau->Ysplit != mapdata->energy) {
    return 0;
  } 
  */
  TypeCase* cases = malloc(sizeof(int)*plateau->Xsplit*plateau->Ysplit);
  RGBcolor* pixel_ppm = malloc(sizeof(RGBcolor));
  for(int i = 0; i < plateau->Xsplit*plateau->Ysplit; i++) {
    pixel_ppm->red = (char) pixel_data[i*3];
    pixel_ppm->green = (char) pixel_data[i*3+1];
    pixel_ppm->blue = (char) pixel_data[i*3+2];
    if(case_RGBCompare(*pixel_ppm, mapdata->pathCol)) {
        cases[i] = CHEMIN;
    } else if (case_RGBCompare(pixel_ppm, &mapdata->nodeCol)) {
        cases[i] = NOEUD;
    } else if (case_RGBCompare(pixel_ppm, &mapdata->buildingCol)) {
        cases[i] = TERRAIN;
    } else if (case_RGBCompare(pixel_ppm, &mapdata->inCol)) {
        cases[i] = ENTREE;
    } else if (case_RGBCompare(pixel_ppm, &mapdata->outCol)) {
        cases[i] = SORTIE;
    } else {
      return 0;
    }
    //printf("%d ", cases[i]);
  }
  plateau->cases = cases;
  return 1;
}

int case_RGBCompare(RGBcolor *color1, RGBcolor *color2) {
  if(color1->green != color2->green) {
    return 0;
  } else if (color1->red != color2->red) {
    return 0;
  } else if (color1->blue != color2->blue) {
    return 0;
  } else {
    return 1;
  }
}


int case_getCaseIndex(Plateau *plateau, int caseX, int caseY)
{
  return caseY * plateau->Xsplit + caseX;
}

int case_getType(Plateau *plateau, int caseX, int caseY)
{
  int index_case = case_getCaseIndex(plateau, caseX, caseY);
  return plateau->cases[index_case];
}

int case_getCaseCoordFromPixels(Plateau *plateau, int positionX, int positionY, int *caseX, int *caseY, int px_width, int px_height)
{
  int case_width = px_width / plateau->Xsplit;
  int case_height = px_height / plateau->Ysplit;

  if (positionX >= 0 && positionX < px_width && positionY >= 0 && positionY < px_height) {
    *caseX = positionX / case_width;
    *caseY = positionY / case_height;
    return 1;
  }
  else {
    return 0;
  }
}

int case_isEmpty(Plateau *plateau, int caseX, int caseY)
{
  int index_position = case_getCaseIndex(plateau, caseX, caseY);
  if (plateau->cases[index_position] != TERRAIN) {
    return 0;
  }
  else {
    return 1;
  }
}
