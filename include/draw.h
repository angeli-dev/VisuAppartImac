using namespace std;
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>


#ifndef DRAW_H 
#define DRAW_H

#include "../include/geometry.h"
#include "../include/camera.h"

void drawScene(Camera camera);
void glDrawRepere(float length);
void glDrawQuad(float x, float y, float z, float largeur, float longueur, float hauteur);

#endif