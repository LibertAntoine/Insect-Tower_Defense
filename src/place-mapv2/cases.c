#include "cases.h"

void case_initPlateau(Plateau *plateau, int Xsplit, int Ysplit)
{
  plateau->Xsplit = Xsplit;
  plateau->Ysplit = Ysplit;
  int total_cases = Xsplit*Ysplit;

  plateau->cases = malloc(sizeof(TypeCase)*total_cases);
  if (!plateau->cases) {
    return EXIT_FAILURE;
  }
  for (int no_case = 0; no_case < total_cases; no_case++) {
    plateau->cases[no_case] = TERRAIN;
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

/*
void case_addTower(int caseX, int caseY, int cases[], TypeCase type)
{
  int index_position = case_getCaseIndex(caseX, caseY);
  cases[index_position] = type;
}

void case_activateAllTowers(int cases[], int range)
{
  int total_cases = Xsplit*Ysplit;

  for (int case_idx=0; case_idx<total_cases; case_idx++) {

    if (cases[case_idx] != CENTRALE) {
      continue;
    }

    for (int i = case_idx - range*Xsplit; i <= case_idx + range*Xsplit; i+=Xsplit) {
      if (i < 0 || i >= total_cases) {
        continue;
      }
      for (int j = i-range; j <= i+range; j++) {
        if (i/Xsplit != j/Xsplit || j < 0 || j >= total_cases) {
          continue;
        }

        if (cases[j] == TOWER_INACTIVE) {
          cases[j] = TOWER_ACTIVE;
        }
      }
    }
  }
}
*/
