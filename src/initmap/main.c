#include <stdio.h>
#include <stdlib.h>

#include "cases.h"
#include "ppm-loader.h"
#include "itd-file.h"
#include "short-path-algo.h"

extern Plateau* plateau;

int main(int argc, char *argv[])
{
    MapData* mapData = itd_initMapData();
    idt_load("level1.itd", mapData);
    
    case_initPlateau(mapData);
    getShortPath(mapData->infosNodes);
    
}
