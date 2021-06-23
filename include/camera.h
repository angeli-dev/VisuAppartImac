#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#ifndef CAMERA_H
#define CAMERA_H

#include "../include/geometry.h"


// Classe
typedef struct Camera 
{ 
    float phi=0.0;
    float theta=0.0;
    Vector3D orientation;

    Vector3D axeVertical;
    Vector3D deplacementLateral;

    Vector3D position;
    Vector3D pointCible;

    float sensibilite=0.0;
    float vitesse=0.0;

    point position_2D;
    point orientation_2D;
    
} Camera;

Camera orienter(Camera cam, int xRel, int yRel);
Camera setPointcible(Camera cam, Vector3D pointCible);
Camera setPosition(Camera cam, Vector3D position);

#endif