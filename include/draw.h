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
#include "../include/texture.h"


void drawScene(Camera camera);

void glDrawRepere(float length);
/* 1 pour se placer au mileu d'un axe, 0.5 pour les extremités de la pièce*/
void glDrawQuad(float x, float y, float z, float largeur, float longueur, float hauteur);

#endif