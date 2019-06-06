# README
## COMPILING

gcc main.c cases.c display.c player.c tour.c -o prog -g -lSDL2 -lGL -lGLU -lm

## About
This version features
* 4 types of buildings
* 2 types of towers
* the ability to ADD / REMOVE towers or buildings
* the ability to get INFO about each element
* Calculate towers' surrounding buildings
* Switch building and tower placement via kayboard shortcuts

On the display side it is capable of
* Showing the grid (rows and colums)
* Displaying buildings as squares and towers as circles
* Displaying each buildings range of action
* Click directly on he map to ADD/REMOVE/GET INFO

## Colors
Towers
* LASER : green
* MISSILE : red

Buildings
* MUNITION : yellow
* ARMEMENT : red
* RADAR : blue
* CENTRALE : green

## KEYBOARD CONTROLS
Selecting construction types
* r - radar
* c - central
* a - armement
* m - munition
* 1 - laser
* 2 - missile

Changing mode
* p - add
* x - remove
* i - get info
