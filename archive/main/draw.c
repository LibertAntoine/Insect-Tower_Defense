#include "draw.h"
#include <GL/glew.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>


/* Subdivisions cercle */
static const int CIRCLE_SUBDIVS = 2<<5;

void drawOrigin() 
{
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR,currentColor);

    glBegin(GL_LINES);

    glColor3f(1., 0., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 1.0 , 0.0);

    glColor3f(0., 1., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 0.0 , 1.0);

    glEnd();

    glColor3fv(currentColor);
}

void drawSquare(int filled) 
{
    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }


    glEnd();
}

void drawCircle(int filled) 
{
    int i = 0;

    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    for(i = 0; i < CIRCLE_SUBDIVS; i++) 
    {
        glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)), 
                    sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)));
    }
    glVertex2f( cos(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)), 
                sin(i * (2 * M_PI / (float) CIRCLE_SUBDIVS)));

    glEnd();
}

int createFirstArm() {
    int id = glGenLists(1);
    glNewList(id, GL_COMPILE);
        glPushMatrix();
            glColor3f(150., 0.,0.);
            glScalef(20.,20.,0.);
            drawCircle(0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(60., 0., 0.);
            glScalef(10.,10.,0.);
            drawCircle(0);
        glPopMatrix();
        glPushMatrix();
            glColor3f(255., 0.,0.);
            glBegin(GL_LINES);
                glVertex2f(0, 20);
                glVertex2f(60, 10);
            glEnd();
            glBegin(GL_LINES);
                glVertex2f(0, -20);
                glVertex2f(60, -10);
            glEnd();
        glPopMatrix();
    glEndList();
    return id;
}

int createSecondArm() {
    int id = glGenLists(1);
    glNewList(id, GL_COMPILE);
        glPushMatrix();
            glColor3f(0., 230.,0.);
            glScalef(10.,10.,0.);
            drawSquare(0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(40, 0., 0.);
            glScalef(10.,10.,0.);
            drawSquare(0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(20, 0., 0.);
            glScalef(46.,7.,0.);
            drawSquare(1);
        glPopMatrix();
    glEndList();
    return id;
}

int createTheirdArm() {
    int id = glGenLists(1);
    glNewList(id, GL_COMPILE);
        glPushMatrix();
            glColor3f(0., 0.,255.);
            glScalef(6.,6.,0.);
            drawSquare(0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(40, 0., 0.);
            glScalef(4.,4.,0.);
            drawCircle(1);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(20, 0., 0.);
            glScalef(44.,4.,0.);
            drawSquare(1);
        glPopMatrix();
    glEndList();
    return id;
}