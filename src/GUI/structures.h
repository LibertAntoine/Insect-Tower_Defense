#ifndef STRUCTURES_H_
#define STRUCTURES_H_


typedef struct Div {
  int x;
  int y;
  int width;
  int height;
} Div;

typedef enum ButtonName {
  LASER,
  PAUSE,
  MISSILE
} ButtonName;

typedef enum Display {
  NONE,
  ACTIVE,
  INACTIVE,
  CLICK
} Display;

typedef struct Button {
  Div *dimensions;
  Display display;
  struct Button *next;
  ButtonName name;
} Button;

typedef enum SectionName {
  BODY,
  FOOTER,
  PLATEAU,
  HEADER
} SectionName;

typedef struct GUI {
  SectionName name;
  Div *dimensions;
  struct GUI *parent;
  struct GUI *childen;
  struct GUI *next;
  Button *buttons;
} GUI;

extern GUI *bodyGUI;
extern GUI *plateauGUI;
extern GUI *bottomGUI;
extern GUI *topGUI;

#endif //STRUCTURES_H_
