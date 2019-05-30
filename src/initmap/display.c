#include "display.h"

TextureText*  display_loadTextureText(char text[])
{
  TTF_Init();
  TTF_Font *font = TTF_OpenFont("fonts/fun.ttf", 36);
  SDL_Color white = {255, 255, 255};
  SDL_Surface* texture_surface = TTF_RenderText_Blended(font, text, white);

  GLuint texture_id;
  glGenTextures(1, &texture_id);

  glBindTexture(GL_TEXTURE_2D, texture_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_surface->w, texture_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_surface->pixels);

  glBindTexture(GL_TEXTURE_2D, 0);

  TTF_CloseFont(font);
  TTF_Quit();

  TextureText* texture_texte = malloc(sizeof(TextureText));
  texture_texte->texture_id = texture_id;
  texture_texte->ratio = texture_surface->w / (float) texture_surface->h;

  return texture_texte;
}


void display_drawSingleStat(GeneralType generalType, char text[], TextureName texture_name)
{
  TextureText* texture_texte = display_loadTextureText(text);

  glTranslatef(50, 10 ,0);
  glColor3f(1,1,1);

  glPushMatrix();
  glScalef(100, 35, 1);
  sprite_displayFixedTexture(PLANK_TEX);
  glPopMatrix();

  glTranslatef(-25, 0 ,0);

  glPushMatrix();
  glTranslatef(5, 0, 0);
  glScalef(25, 25, 1);
  sprite_displayFixedTexture(texture_name);
  glPopMatrix();

  if (generalType == BATIMENT) {
    glPushMatrix();
    glTranslatef(15, 5, 0);
    glScalef(15, 15, 1);
    sprite_displayFixedTexture(PLUS_TEX);
    glPopMatrix();
  }

  glPushMatrix();
  glTranslatef(30, 0, 0);
  glScalef(14*texture_texte->ratio, 14, 1);
  sprite_displayFixedTextureText(texture_texte);
  glPopMatrix();
}

void display_initDefaultList()
{
  default_list = calloc(10, sizeof(DefaultList*));

  int position = 0;
  char str[12];

  GeneralType generalType = TOUR;
  for (int i = LASER; i <= MISSILE; i++) {
    default_list[i] = calloc(1, sizeof(DefaultList));

    GLuint idListInfos = glGenLists(1);
    glNewList(idListInfos, GL_COMPILE);
    glPushMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", plateau->constructionData[i].degats);
    display_drawSingleStat(generalType, str, DAMAGE_TEX);
    position++;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", plateau->constructionData[i].cadence);
    display_drawSingleStat(generalType, str, CADENCE_TEX);
    position++;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", plateau->constructionData[i].portee);
    display_drawSingleStat(generalType, str, TARGET_TEX);
    position++;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", plateau->constructionData[i].alimentation);
    display_drawSingleStat(generalType, str, FOOD_TEX);
    position++;
    glPopMatrix();

    position = 0;
    glTranslatef(100, 0,0);

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", plateau->constructionData[i].valeur_achat);
    display_drawSingleStat(generalType, str, MONEY_TEX);
    position++;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", plateau->constructionData[i].valeur_revente);
    display_drawSingleStat(generalType, str, MONEY_TEX);
    position++;
    glPopMatrix();

    glPopMatrix();
    glEndList();
    default_list[i]->idListInfos = idListInfos;
    position = 0;
  }

  generalType = BATIMENT;
  for (int i = RADAR; i <= MUNITION; i++) {
    default_list[i] = calloc(1, sizeof(DefaultList));

    GLuint idListInfos = glGenLists(1);
    glNewList(idListInfos, GL_COMPILE);
    glPushMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", plateau->constructionData[i].degats);
    display_drawSingleStat(generalType, str, DAMAGE_TEX);
    position++;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", plateau->constructionData[i].cadence);
    display_drawSingleStat(generalType, str, CADENCE_TEX);
    position++;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", plateau->constructionData[i].portee);
    display_drawSingleStat(generalType, str, TARGET_TEX);
    position++;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", plateau->constructionData[i].alimentation);
    display_drawSingleStat(generalType, str, FOOD_TEX);
    position++;
    glPopMatrix();

    position = 0;
    glTranslatef(100, 0,0);

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", plateau->constructionData[i].valeur_achat);
    display_drawSingleStat(generalType, str, MONEY_TEX);
    position++;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", plateau->constructionData[i].valeur_revente);
    display_drawSingleStat(generalType, str, MONEY_TEX);
    position++;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", plateau->constructionData[i].range);
    display_drawSingleStat(TOUR, str, TARGET_TEX);
    position++;
    glPopMatrix();

    glPopMatrix();
    glEndList();
    default_list[i]->idListInfos = idListInfos;
    position = 0;
  }

  generalType = TOUR;
  int type;
  for (int i = SOLDER_DEF; i <= BOSS_DEF; i++) {
    type = i - 6;
    default_list[i] = calloc(1, sizeof(DefaultList));

    GLuint idListInfos = glGenLists(1);
    glNewList(idListInfos, GL_COMPILE);
    glPushMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", (int) plateau->listMonsters->dataMonsters[type]->PDV);
    display_drawSingleStat(generalType, str, LIFE_TEX);
    position++;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", (int) plateau->listMonsters->dataMonsters[type]->strength);
    display_drawSingleStat(generalType, str, SHIELD_TEX);
    position++;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%f", 0.01/plateau->listMonsters->dataMonsters[type]->mass);
    display_drawSingleStat(generalType, str, SPEED_TEX);
    position++;
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15, position*35+15, 0);
    sprintf(str, "%d", plateau->listMonsters->dataMonsters[type]->value);
    display_drawSingleStat(BATIMENT, str, MONEY_TEX);
    position++;
    glPopMatrix();

    glPopMatrix();
    glEndList();
    default_list[i]->idListInfos = idListInfos;

    position = 0;
  }
}

void display_printInfos()
{
  if (plateau->index_case_hover == -1 && plateau->monster_hover == NULL) {
    glCallList(default_list[plateau->joueur->type]->idListInfos);
  }
  else if (plateau->monster_hover) {
    glCallList(default_list[plateau->monster_hover->type + 6]->idListInfos);
  }
  else if (case_getGeneralConstructionType(plateau->cases[plateau->index_case_hover]) == TOUR) {
    printf("faire l'affichage infos tour\n");
  }
  else if (case_getGeneralConstructionType(plateau->cases[plateau->index_case_hover]) == BATIMENT) {
    printf("faire l'affichage infos batiment\n");
  }
}

void display_drawCircle(int fillMode)
{
  float angleStep = 2 * M_PI / 360;
  float angleCurrent = 0;

  glPolygonMode(GL_FRONT_AND_BACK, fillMode);

  glBegin(GL_POLYGON);

  while(angleCurrent < 2 * M_PI) {
    glVertex2f(0.5 * cos(angleCurrent), 0.5 * sin(angleCurrent));
    angleCurrent += angleStep;
  }
  glEnd();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void display_drawSquare(int fillMode)
{
  glPolygonMode(GL_FRONT_AND_BACK, fillMode);

  glBegin(GL_QUADS);
  glVertex2f(-0.5,0.5);
  glVertex2f(0.5,0.5);
  glVertex2f(0.5,-0.5);
  glVertex2f(-0.5,-0.5);
  glEnd();
}

void display_drawTriangle(int fillMode)
{
  glPolygonMode(GL_FRONT_AND_BACK, fillMode);

  glBegin(GL_TRIANGLES);
  glVertex2f(0, -0.3);
  glVertex2f(0.3, 0.3);
  glVertex2f(-0.3, 0.3); 
  glEnd();
}

void display_drawTargetRange(int caseX, int caseY, float range)
{
  glPushMatrix();
  glTranslatef(caseX, caseY, 0);
  glTranslatef(0.5,0.5,0);
  glScalef(range, range, 1);
  glColor3f(1,1,1);
  display_drawCircle(GL_LINE);
  glPopMatrix();
}

void display_drawSingleMonster(Monster* monster)
{
  if(monster->status == ALIVE) {
    glColor3f(1,1,1);
  } else {
    glColor4f(1,1,1, monster->decomposition);
  }

  float angle = 0;
  if (monster->orientation == HAUT) {
    angle = 0;
  } else if (monster->orientation == BAS) {
    angle = 180;
  } else if (monster->orientation == GAUCHE) {
    angle = -90;
  } else if (monster->orientation == DROITE) {
    angle = 90;
  }
  float PDV = monster->PDV;
  float maxPDV = plateau->listMonsters->dataMonsters[monster->type]->PDV;
  float percentPDV = 1 / maxPDV * PDV;
  glPushMatrix();
  glTranslatef(monster->x, monster->y, 0);

  glPushMatrix();
  glRotatef(angle, 0, 0, 1);

  sprite_displaySprite(monster->sprite_texture);
  //display_drawTriangle(GL_FILL);

  glPopMatrix();

  // NOTE: affiche la vie que si le monstre est vivant et qu'il a subi des dommages
  if(monster->status == ALIVE && percentPDV < 1) {
    glPushMatrix();
    glScalef(0.8, 0.3, 1);
    glTranslatef(0, 0.9, 0);
    display_drawMonsterLife(percentPDV);
    glPopMatrix();
  }
  glPopMatrix();
}

void display_drawMonsterLife(float PDV)
{
  glPushMatrix();
  glScalef(1,0.5,1);
  glColor3f(1,0,0);
  display_drawSquare(GL_FILL);
  glColor3f(0,1,0);
  glTranslatef(-((1-PDV)/2),0,0);
  glScalef(PDV,1,1);
  display_drawSquare(GL_FILL);
  glPopMatrix();
}

int display_drawAllMonsters()
{
  if(plateau->listMonsters->firstMonster == NULL) {
    return 0;
  }

  Monster* currentMonster = plateau->listMonsters->firstMonster;
  while (currentMonster != NULL) {  
      display_drawSingleMonster(currentMonster);
      if (plateau->monster_hover == currentMonster) {
        display_drawItineraire(currentMonster);
      }
      currentMonster = currentMonster->next;
  }
  return 0;
}


int display_drawAllProjectiles()
{
  if(plateau->listProjectiles->next == NULL) {
    return 0;
  }
  Projectile* currentProjectile = plateau->listProjectiles->next;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  while (currentProjectile != NULL) {  
    display_drawSingleProjectile(currentProjectile);
    currentProjectile = currentProjectile->next;

  }
  return 0;
}

void display_drawSingleProjectile(Projectile* projectile)
{
  glColor3d(255,0,255);

  glBegin(GL_TRIANGLES);
  glVertex2f(projectile->x, projectile->y-0.1);
  glVertex2f(projectile->x+0.1, projectile->y+0.1);
  glVertex2f(projectile->x-0.1, projectile->y+0.1); 
  glEnd();

}

void display_mapList(GLuint id)
{
  glNewList(id, GL_COMPILE);
  int caseX;
  int caseY;

  for (int index_case = 0; index_case < plateau->Xsplit * plateau->Ysplit; index_case++) {

    case_getCasePosition(index_case, &caseX, &caseY);
    TypeCase type = case_getType(caseX, caseY);

    switch (type) {
      case CHEMIN:
        glColor3f(1,0,1);
        break;
      case NOEUD:
        glColor3f(1,0,0);
        break;
      case ENTREE:
        glColor3d(0,0,1);
        break;
      case SORTIE:
        glColor3f(0,1,0);
        break;
      default:
        glColor3f(0,0,0);
        break;
    }

    glPushMatrix();
    glTranslatef(caseX, caseY, 0);
    glTranslatef(0.5, 0.5, 0);
    display_drawSquare(GL_FILL);
    glPopMatrix();

  }

  glEndList();
}

void display_gridList(GLuint id)
{
  glNewList(id, GL_COMPILE);
  glColor3d(0,255,0);
  glLineWidth(3);

  for (int i=0; i<plateau->Xsplit; i++) {
    glBegin(GL_LINES);
    glVertex2d(i+1, 1);
    glVertex2d(i+1, plateau->Ysplit+1);
    glEnd();
  }
  glColor3d(255,255,0);
  for (int i=0; i<plateau->Ysplit; i++) {
    glBegin(GL_LINES);
    glVertex2d(1, i+1);
    glVertex2d(plateau->Xsplit+1, i+1);
    glEnd();
  }

  glColor3d(255,0,255);
  glPointSize(5);
  glBegin(GL_POINTS);
  for (int i=0; i<plateau->Xsplit*plateau->Ysplit; i++) {
    float centerY = i / plateau->Xsplit + 1.5;
    float centerX = i % plateau->Xsplit + 1.5;
    glVertex2f(centerX, centerY);
  }
  glEnd();
  glEndList();
}

void display_drawSingleTower(int caseX, int caseY, TypeCase type)
{
  glPushMatrix();
  glTranslatef(caseX, caseY, 0);
  glTranslatef(0.5,0.5,0);
  int index_case = case_getCaseIndex(caseX, caseY);
  GeneralType generalType = case_getGeneralConstructionType(type);
  if (generalType != OTHER) {
    switch (type) {
      case LASER:
        glColor3f(0,1,0);
        break;
      case MISSILE:
        glColor3f(1,0,0);
        break;
      case ARMEMENT:
        glColor3f(1,0,0);
        break;
      case MUNITION:
        glColor3d(1,1,0);
        break;
      case RADAR:
        glColor3f(0,0,1);
        break;
      case CENTRALE:
        glColor3f(0,1,0);
        break;
    }
    switch (generalType) {
      case BATIMENT:
        display_drawSquare(GL_FILL);
        break;
      case TOUR:
        display_drawCircle(GL_FILL);
        break;
    }
  }

  glPopMatrix();
}

void display_drawAllTargetRanges()
{
  int total_cases = plateau->Xsplit * plateau->Ysplit;

  for (int index_case=0; index_case < total_cases; index_case++) {
    TypeCase type = plateau->cases[index_case];
    GeneralType generalType = case_getGeneralConstructionType(type);
    if (generalType == OTHER) {
      continue;
    }
    int caseY, caseX;
    case_getCasePosition(index_case, &caseX, &caseY);
    if (plateau->index_case_hover == index_case) {
      glPushMatrix();
      float range = 0;
      switch (generalType) {
        case BATIMENT:
          range = tour_getRange(type);
          break;
        case TOUR:
          range = tour_calculPortee(plateau->tours[index_case]);
          break;
      }
      display_drawTargetRange(caseX, caseY, range);
      glPopMatrix();
    }
  }
}

void display_drawBoard()
{
  int total_cases = plateau->Xsplit * plateau->Ysplit;

  for (int index_case = 0; index_case < total_cases; index_case++) {
    int caseY, caseX;
    case_getCasePosition(index_case, &caseX, &caseY);
    TypeCase type = plateau->cases[index_case];

    display_drawSingleTower(caseX, caseY, type);
  }
  display_drawAllTargetRanges();
}

void display_drawItineraire(Monster* monster)
{
  if(monster->itineraire->next->next != NULL) {
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2f(monster->x, monster->y);
    glVertex2f(monster->itineraire->next->next->node->x, monster->itineraire->next->next->node->y);

    Etape* currentEtape = monster->itineraire->next->next;
    while(currentEtape->next != NULL) {
      glVertex2f(currentEtape->node->x, currentEtape->node->y);
      glVertex2f(currentEtape->next->node->x, currentEtape->next->node->y);
      currentEtape = currentEtape->next;
    }
    glEnd();
  }
}

void display_setDrawingZone(GUI *section)
{
  int X = 0;
  int Y = 0;
  gui_getAbsoluteCoordinates(section, &X, &Y);

  glViewport(X, bodyGUI->dimensions->height - Y - section->dimensions->height, section->dimensions->width, section->dimensions->height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(0, section->dimensions->width, section->dimensions->height, 0);
  glMatrixMode(GL_MODELVIEW);
}

void display_drawZoneBasedOnGUI(GUI *section)
{
  display_setDrawingZone(section);

  if (default_list == NULL) {
    display_initDefaultList();
  }

  glBegin(GL_QUADS);
  glVertex2f(0, 0);
  glVertex2f(0, section->dimensions->height);
  glVertex2f(section->dimensions->width, section->dimensions->height);
  glVertex2f(section->dimensions->width, 0);
  glEnd();

  Button *button = section->buttons;
  while (button != NULL) {
    display_drawSingleButton(button);
    button = button->next;
  }

  if (section == infoGUI) {
    display_printInfos();
  }

  display_setDrawingZone(bodyGUI);
}

void display_buttonBackground(Display display)
{
  switch (display) {
    case NONE:
      glColor4f(0,0,0,0);
      break;
    case CLICKED:
      glColor3f(0,1,0);
      break;
    case INACTIVE:
      glColor4f(1,1,1, 0.2);
      break;
    case DISABLED:
      glColor3f(1,0,0);
      break;
    case ACTIVE:
      glColor3f(1,1,1);
      break;
  }

  sprite_displayFixedTexture(BUTTON_TEX);
}

void display_drawSingleButton(Button *button)
{
  int half_width = button->dimensions->width / 2;
  int half_height = button->dimensions->height / 2;

  glPushMatrix();
  glTranslatef(button->dimensions->x, button->dimensions->y, 0);

  glScalef(button->dimensions->width, button->dimensions->height, 0);

  Display display_mode;
  if (button->name == PAUSE_BTN) {
    if (plateau->play == TRUE) {
      display_mode = CLICKED;
    }
    else {
      display_mode = DISABLED;
    }
  }
  else {
    display_mode = button->display;
  }

  display_buttonBackground(display_mode);

  glColor3f(1,1,1);

  TextureName texture_name = sprite_getTextureNameFromButtonName(button->name);
  sprite_displayFixedTexture(texture_name);

  glPopMatrix();
}

void display_top()
{
  glColor3f(1,1,0);
  display_drawZoneBasedOnGUI(topGUI);
}

void display_bottom()
{
  glColor3f(1,0,1);
  display_drawZoneBasedOnGUI(bottomGUI);
  glColor3f(1,1,1);
  display_drawZoneBasedOnGUI(buttonGUI);
  glColor3f(.50,0.7,1);
  display_drawZoneBasedOnGUI(infoGUI);
}

void display_left()
{
  glColor3f(1,0,0);
  glBegin(GL_QUADS);
  glVertex2f(0,100);
  glVertex2f(0,500);
  glVertex2f(300,500);
  glVertex2f(300,100);
  glEnd();
}

void display_window()
{
    display_top();
    display_bottom();
}

void display_game(GUI *plateau_gui, GLuint idMap, GLuint idGrid)
{
  Div* plateau_div = plateau_gui->dimensions;
  Div* body_div = bodyGUI->dimensions;

  glViewport(plateau_div->x, plateau_div->y, plateau_div->width, plateau_div->height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(1, plateau->Xsplit+1, plateau->Ysplit+1, 1);
  glMatrixMode(GL_MODELVIEW);

  glCallList(idMap);
  glCallList(idGrid);

  display_drawBoard();

  display_drawAllMonsters();
  display_drawAllProjectiles();

  glViewport(0, 0, body_div->width, body_div->height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, body_div->width, body_div->height, 0);
  glMatrixMode(GL_MODELVIEW);
}
