#include "../include/camera.h"

Camera orienter(Camera cam, int xRel, int yRel)
{
    // Modification des angles
    cam.phi += -yRel*cam.sensibilite;
    cam.theta += -xRel*cam.sensibilite;

     // Limitation de l'angle phi
    if(cam.phi > 89.0)
        cam.phi = 89.0;
    if(cam.phi < -89.0)
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
    if(cam.axeVertical.y == 1.0)
    {
         // Calcul des coordonnées sphériques
        cam.orientation.x = cos(phiRadian) * sin(thetaRadian);
        cam.orientation.y = sin(phiRadian);
        cam.orientation.z = cos(phiRadian) * cos(thetaRadian);
        cam.orientation_2D.x = cam.orientation.x;
        cam.orientation_2D.y = cam.orientation.z;
    }

    // Sinon c'est l'axe Z
    if(cam.axeVertical.z == 1.0)
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
        {
            cam.theta *= -1;
        }
    }

    // Sinon c'est l'axe Z
    else
    {
        // Calcul des angles
        cam.phi = asin(cam.orientation.x);
        cam.theta = acos(cam.orientation.z / cos(cam.phi));

        if(cam.orientation.z < 0)
        {
            cam.theta *= -1;
        }
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
    if(cam.axeVertical.y == 1.0)
    {
         // Calcul des coordonnées sphériques
        cam.position_2D.x = cam.position.x;
        cam.position_2D.y = cam.position.z;
    }

    // Sinon c'est l'axe Z
    if(cam.axeVertical.z == 1.0)
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
    /* début */
    if(cam.compteur<50)
    {
        cam.position=createVector(-10, 100, 12);       
        cam.pointCible=createVector(-10, 0, 12);
        cam=setPointCible(cam, cam.pointCible);
        cam.compteur++;
    }
    if(cam.compteur>=50 && cam.compteur<190){
        cam=deplacementAvant(cam);
        cam.compteur++;
    }
    /* entrée */
    if(cam.compteur==190)
    {
        cam.position=createVector(-10, 65, 12);  
        cam.pointCible=createVector(-10, 0, 12);
        cam=setPointCible(cam, cam.pointCible);
        cam.compteur++;
    }
    if(cam.compteur>190 && cam.compteur<390)
    {
        cam=OrienterGauche(cam);
        cam.compteur++;
    }
    if(cam.compteur>=390 && cam.compteur<570)
    {
        cam=deplacementAvant(cam);
        cam.compteur++;
    }
    /* sale de bain */
    if(cam.compteur>=570 && cam.compteur<930)
    {
        cam=OrienterDroite(cam);
        cam.compteur++;
    }
    if(cam.compteur>=930 && cam.compteur<1030)
    {
        cam=deplacementAvant(cam);
        cam.compteur++;
    }
    /* séjour */
    if(cam.compteur>=1030 && cam.compteur<1235)
    {
        cam=OrienterDroite(cam);
        cam.compteur++;
    }
    if(cam.compteur>=1235 && cam.compteur<1600)
    {
        cam=deplacementAvant(cam);
        cam.compteur++;
    }
    if(cam.compteur>=1300 && cam.compteur<1900)
    {
        cam=OrienterDroite(cam);
        cam.compteur++;
    }
    if(cam.compteur>=1900 && cam.compteur<2130)
    {
        cam=deplacementAvant(cam);
        cam.compteur++;
    }
    if(cam.compteur>=1930 && cam.compteur<2050)
    {
        cam=OrienterDroite(cam);
        cam.compteur++;
    }
    if(cam.compteur>=2130 && cam.compteur<2300)
    {
        cam=OrienterDroite(cam);
        cam.compteur++;
    }
    if(cam.compteur>=2300 && cam.compteur<2400)
    {
        cam=deplacementAvant(cam);
        cam.compteur++;
    }
    /* cuisine */
    if(cam.compteur>=2400 && cam.compteur<2800)
    {
        cam=OrienterDroite(cam);
        cam.compteur++;
    }
    if(cam.compteur>=2800 && cam.compteur<2900)
    {
        cam=deplacementAvant(cam);
        cam.compteur++;
    }
    if(cam.compteur>=2900 && cam.compteur<3100)
    {
        cam=OrienterGauche(cam);
        cam.compteur++;
    }
    if(cam.compteur>=3100 && cam.compteur<3180)
    {
        cam=deplacementAvant(cam);
        cam.compteur++;
    }
    if(cam.compteur>=3180 && cam.compteur<3350)
    {
        cam=OrienterGauche(cam);
        cam.compteur++;
    }
    /* escalier */
    //1
    if(cam.compteur>=3350 && cam.compteur<3355)
    {
        cam=deplacementAvant(cam);
        cam=deplacementMonter(cam);
        cam.compteur++;
    }
    if(cam.compteur>=3355 && cam.compteur<3375)
    {
        cam.compteur++;
    }
    //2
    if(cam.compteur>=3375 && cam.compteur<3380)
    {
        cam=deplacementAvant(cam);
        cam=deplacementMonter(cam);
        cam.compteur++;
    }
    if(cam.compteur>=3380 && cam.compteur<3390)
    {
        cam.compteur++;
    }
    //3
    if(cam.compteur>=3390 && cam.compteur<3495)
    {
        cam=deplacementAvant(cam);
        cam=deplacementMonter(cam);
        cam.compteur++;
    }
    if(cam.compteur>=3395 && cam.compteur<3405)
    {
        cam.compteur++;
    }
    //4
    if(cam.compteur>=3405 && cam.compteur<3410)
    {
        cam=deplacementAvant(cam);
        cam=deplacementMonter(cam);
        cam.compteur++;
    }
    if(cam.compteur>=3415 && cam.compteur<3425)
    {
        cam.compteur++;
    }
    //5
    if(cam.compteur>=3425 && cam.compteur<3430)
    {
        cam=deplacementAvant(cam);
        cam=deplacementMonter(cam);
        cam.compteur++;
    }
    if(cam.compteur>=3430 && cam.compteur<3440)
    {
        cam.compteur++;
    }
    /* étage */
    if(cam.compteur>=3440 && cam.compteur<3445)
    {
        cam=OrienterDroite(cam);
        cam=deplacementMonter(cam);
        cam.compteur++;
    }
    if(cam.compteur>=3440 && cam.compteur<3800)
    {
        cam=OrienterDroite(cam);
        cam.compteur++;
    }
    if(cam.compteur>=3800 && cam.compteur<3950)
    {
        cam=deplacementAvant(cam);
        cam.compteur++;
    }
    if(cam.compteur>=3950 && cam.compteur<4370)
    {
        cam=OrienterDroite(cam);
        cam.compteur++;
    }
    if(cam.compteur>=4350 && cam.compteur<4600)
    {
        cam=deplacementAvant(cam);
        cam.compteur++;
    }
    if(cam.compteur>=4600 && cam.compteur<4800)
    {
        cam=OrienterDroite(cam);
        cam.compteur++;
    }
    if(cam.compteur>=4700 && cam.compteur<5500)
    {
        cam=OrienterGauche(cam);
        cam.compteur++;
    }
    return cam;
}

Camera OrienterGauche(Camera cam){
    cam = orienter(cam, 1, 0);
    return cam;
}

Camera OrienterDroite(Camera cam){
    cam = orienter(cam, -1, 0);  
    return cam;
}

Camera OrienterHaut(Camera cam){
    cam = orienter(cam, 0, 1);
    return cam;
}

Camera OrienterBas(Camera cam){
    cam = orienter(cam, 0, -1);  
    return cam;
}

Camera faireUnTour(Camera cam){
    if(cam.i < 360/cam.sensibilite)
    {
        cam = OrienterGauche(cam);
        cam.i++;
    }
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

Camera deplacementMonter(Camera cam){
    cam.position = addVectors(cam.position, multVector(cam.axeVertical, cam.vitesse));
    cam.pointCible = addVectors(cam.position, cam.orientation);
    return cam;           
}

Camera deplacementDescendre(Camera cam){
    cam.position = subVectors(cam.position, multVector(cam.axeVertical, cam.vitesse));
    cam.pointCible = addVectors(cam.position, cam.orientation);                                 
    return cam;             
}


Camera inEntree(Camera cam){
    cam.position=createVector(0, 60, 12);
    cam.pointCible=createVector(70, 0, 12);
    return cam;
}

Camera inSdb(Camera cam){
    cam.position=createVector(35, 60, 12);
    cam.pointCible=createVector(0, 60, 12);;
    return cam;
}
Camera inSejour(Camera cam){
    cam.position=createVector(25, 25, 12);
    cam.pointCible=createVector(0, 0, 12);
    return cam;
}
Camera inCuisine(Camera cam){
    cam.position=createVector(-10, 25, 12);
    cam.pointCible=createVector(0, 0, 12);
    return cam;
}
Camera inChambre(Camera cam){
    cam.position=createVector(10, 35, 32);
    cam.pointCible=createVector(0, 0, 32);
    return cam;
}
Camera inBalcon(Camera cam){
    cam.position=createVector(25, -5, 32);
    cam.pointCible=createVector(0, 0, 32);
    return cam;
}
