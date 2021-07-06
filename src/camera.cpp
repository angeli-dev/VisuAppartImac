#include "../include/camera.h"

Camera orienter(Camera cam, int xRel, int yRel)
{
    // Modification des angles
    cam.phi += -yRel*cam.sensibilite;
    cam.theta += -xRel*cam.sensibilite;

     // Limitation de l'angle phi
    if(cam.phi > 89.0)
        cam.phi = 89.0;
    else if(cam.phi < -89.0)
        cam.phi = -89.0;

     // Conversion des angles en radian
    float phiRadian = cam.phi * M_PI / 180;
    float thetaRadian = cam.theta * M_PI / 180;

    // Si l'axe vertical est l'axe X
    if(cam.axeVertical.x == 1.0)
    {
        // Calcul des coordonnées sphériques
        cam.orientation.x = sin(phiRadian);
        cam.orientation.y = cos(phiRadian) * cos(thetaRadian);
        cam.orientation.z = cos(phiRadian) * sin(thetaRadian);
        cam.orientation_2D.x = cam.orientation.y;
        cam.orientation_2D.y = cam.orientation.z;
        
    }

    // Si c'est l'axe Y
    else if(cam.axeVertical.y == 1.0)
    {
         // Calcul des coordonnées sphériques
        cam.orientation.x = cos(phiRadian) * sin(thetaRadian);
        cam.orientation.y = sin(phiRadian);
        cam.orientation.z = cos(phiRadian) * cos(thetaRadian);
        cam.orientation_2D.x = cam.orientation.x;
        cam.orientation_2D.y = cam.orientation.z;
    }

    // Sinon c'est l'axe Z
    else
    {
         // Calcul des coordonnées sphériques
        cam.orientation.x = cos(phiRadian) * cos(thetaRadian);
        cam.orientation.y = cos(phiRadian) * sin(thetaRadian);
        cam.orientation.z = sin(phiRadian);
        cam.orientation_2D.x = cam.orientation.x;
        cam.orientation_2D.y = cam.orientation.y;
    }

    // Calcul de la normale
    cam.deplacementLateral = multVectors(cam.axeVertical, cam.orientation);
    cam.deplacementLateral = normalize(cam.deplacementLateral);

    // Calcul du point ciblé pour OpenGL
    cam.pointCible = addVectors(cam.position, cam.orientation);

    return cam;
}

Camera setPointCible(Camera cam, Vector3D pointCible){

    // Calcul du vecteur orientation
    cam.orientation = subVectors(cam.pointCible, cam.position);
    cam.orientation = normalize(cam.orientation);

     // Si l'axe vertical est l'axe X
    if(cam.axeVertical.x == 1.0)
    {
       // Calcul des angles
        cam.phi = asin(cam.orientation.x);
        cam.theta = acos(cam.orientation.y / cos(cam.phi));

        if(cam.orientation.y < 0)
            cam.theta *= -1;
    }

    // Si c'est l'axe Y
    else if(cam.axeVertical.y == 1.0)
    {
        // Calcul des angles
        cam.phi = asin(cam.orientation.y);
        cam.theta = acos(cam.orientation.z / cos(cam.phi));

        if(cam.orientation.z < 0)
            cam.theta *= -1;
    }

    // Sinon c'est l'axe Z
    else
    {
        // Calcul des angles
        cam.phi = asin(cam.orientation.x);
        cam.theta = acos(cam.orientation.z / cos(cam.phi));

        if(cam.orientation.z < 0)
            cam.theta *= -1;
    }

    // Conversion en degrés
    cam.phi = cam.phi * 180 / M_PI;
    cam.theta = cam.theta * 180 / M_PI;

    return cam;
}

Camera setPosition(Camera cam, Vector3D position)
{
    // Mise à jour de la position
    cam.position = position;
    if(cam.axeVertical.x == 1.0)
    {
        // Calcul des coordonnées sphériques
        cam.position_2D.x = cam.position.y;
        cam.position_2D.y = cam.position.z;
        
    }

    // Si c'est l'axe Y
    else if(cam.axeVertical.y == 1.0)
    {
         // Calcul des coordonnées sphériques
        cam.position_2D.x = cam.position.x;
        cam.position_2D.y = cam.position.z;
    }

    // Sinon c'est l'axe Z
    else
    {
         // Calcul des coordonnées sphériques
        cam.position_2D.x = cam.position.x;
        cam.position_2D.y = cam.position.y;
    }
    // Actualisation du point ciblé
    cam.pointCible = addVectors(cam.position, cam.orientation);

    return cam;
}

Camera visiteAuto (Camera cam){
    if(cam.compteur<50)
    {
        cam.position=createVector(-10, 100, 12);
        cam.pointCible=createVector(-10, 0, 12);
        cam=setPointCible(cam, cam.pointCible);
        cam.compteur++;
    }
    if(cam.compteur>=50 && cam.compteur<100){
        cam=deplacementAvant(cam);
        cam.compteur++;
    }/*
    if(cam.compteur>0 && cam.compteur<2/cam.vitesse){
        cam=inEntree(cam);
        cam.compteur++;
    }
    if(cam.compteur>=2/cam.vitesse && cam.compteur<360/cam.sensibilite)
    {
        cam=OrienterGauche(cam);
        cam.compteur++;
    }*/
    return cam;
}

Camera OrienterGauche(Camera cam){
    cam = orienter(cam, 1, 0);
    return cam;
}

Camera deplacementAvant(Camera cam){
    cam.position = addVectors(cam.position, multVector(cam.orientation, cam.vitesse));
    cam.pointCible = addVectors(cam.position, cam.orientation);  
    return cam;             
}

Camera deplacementArriere(Camera cam){
    cam.position = subVectors(cam.position, multVector(cam.orientation, cam.vitesse));
    cam.pointCible = addVectors(cam.position, cam.orientation);           
    return cam;             
}

Camera deplacementGauche(Camera cam){
    cam.position = addVectors(cam.position, multVector(cam.deplacementLateral, cam.vitesse));
    cam.pointCible = addVectors(cam.position, cam.orientation);                          
    return cam;             
}

Camera deplacementDroite(Camera cam){
    cam.position = subVectors(cam.position, multVector(cam.deplacementLateral, cam.vitesse));
    cam.pointCible = addVectors(cam.position, cam.orientation);                                 
    return cam;             
}

Camera inEntree(Camera cam){
    //cam = setPosition(cam, createVector(0, 60, 12));
    //cam = setPointCible(cam, createVector(70, 0, 12)); 
   
    cam.position=createVector(0, 60, 12);
    cam.pointCible=createVector(70, 0, 12);
   
    cam.piece=1;
    cam.i=0;
    return cam;
}

Camera inSdb(Camera cam){
    cam.position=createVector(35, 60, 12);
    cam.pointCible=createVector(0, 60, 12);
    cam.piece=2;
    cam.i=0;
    return cam;
}
Camera inSejour(Camera cam){
    cam.position=createVector(25, 25, 12);
    cam.pointCible=createVector(0, 0, 12);
    cam.piece=3;
    cam.i=0;
    return cam;
}
Camera inCuisine(Camera cam){
    cam.position=createVector(-10, 25, 12);
    cam.pointCible=createVector(0, 0, 12);
    cam.piece=4;
    cam.i=0;
    return cam;
}
Camera inChambre(Camera cam){
    cam.position=createVector(10, 35, 32);
    cam.pointCible=createVector(0, 0, 32);
    cam.piece=5;
    cam.i=0;
    return cam;
}
Camera inBalcon(Camera cam){
    cam.position=createVector(25, -5, 32);
    cam.pointCible=createVector(0, 0, 32);
    cam.piece=6;
    cam.i=0;
    return cam;
}
