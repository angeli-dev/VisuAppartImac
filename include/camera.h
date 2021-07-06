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

    int compteur=0;
    int i=0;
    int piece=0;
    
} Camera;

Camera orienter(Camera cam, int xRel, int yRel);
Camera setPointCible(Camera cam, Vector3D pointCible);
Camera setPosition(Camera cam, Vector3D position);
Camera visiteAuto (Camera cam);
Camera OrienterGauche (Camera cam);
Camera OrienterDroite (Camera cam);
Camera deplacementArriere(Camera cam);
Camera deplacementAvant(Camera cam);
Camera deplacementDroite(Camera cam);
Camera deplacementGauche(Camera cam);
Camera inEntree(Camera cam);
Camera inSdb(Camera cam);
Camera inSejour(Camera cam);
Camera inCuisine(Camera cam);
Camera inChambre(Camera cam);
Camera inBalcon(Camera cam);

#endif