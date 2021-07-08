#include "../include/draw.h"


/* fonction de dessin de la scène à l'écran              */

void drawScene(Camera camera){

	/* Debut du dessin de la scène */
	glPushMatrix();

	/* placement de la caméra */
    gluLookAt(camera.position.x, camera.position.y, camera.position.z,
                camera.pointCible.x, camera.pointCible.y, camera.pointCible.z, 
                camera.axeVertical.x, camera.axeVertical.y, camera.axeVertical.z);

	glDrawRepere(100.0);

	/* gestion de l'affichage (on ne veut pas voir derrière un objet) */
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

	/* PREMIERE PIECE - RDC / SEJOUR */

	/* Dessin du sol */
	glColor3f(0.9 , 0.9, 1);
	glDrawQuad(25, 25, 0.5, 50, 50, 1);

	/* Dessin des murs sans porte */

	//fenetres
	glColor3f(0.7 , 0.7, 1);
	glDrawQuad(25, 0.5, 10, 50, 1, 20); 
	//sdb
	glColor3f(0.6 , 0.6, 1);
	glDrawQuad(50, 25, 10, 1, 50, 20);

	/* Murs avec porte */

	//porte séjour-cuisine
	glColor3f(0.8 , 0.8, 1);
	glDrawQuad(0.5, 15, 10, 1, 30, 20); 
	glDrawQuad(0.5, 45, 10, 1, 10, 20);
	glDrawQuad(0.5, 35, 18, 1, 10, 4);
	//porte séjour-entrée
	glColor3f(0.5 , 0.5, 1);
	glDrawQuad(2, 50, 10, 4, 1, 20);
	glDrawQuad(32, 50, 10, 36, 1, 20);
	glDrawQuad(9, 50, 18, 10, 1, 4);

	/* escalier */
	glColor3f(0.4 , 0.4, 1);
	glDrawQuad(5, 24, 2, 8, 2, 0.5);
	glDrawQuad(5, 22, 4, 8, 2, 0.5);
	glDrawQuad(5, 20, 6, 8, 2, 0.5);
	glDrawQuad(5, 18, 8, 8, 2, 0.5);
	glDrawQuad(5, 16, 10, 8, 2, 0.5);
	glDrawQuad(5, 14, 12, 8, 2, 0.5);
	glDrawQuad(5, 12, 14, 8, 2, 0.5);
	glDrawQuad(5, 10, 16, 8, 2, 0.5);
	glDrawQuad(5, 8, 18, 8, 2, 0.5);

	/* DEUXIEME PIECE - RDC / CUISINE */

	/* Dessin du sol */
	glColor3f(1 , 0.9, 0.9);
	glDrawQuad(-10, 25, 0.5, 20, 50, 1);

	/* Dessin des murs sans porte */

	//fenetre
	glColor3f(1 , 0.8, 0.8);
	glDrawQuad(-10, 0, 10, 20, 1, 20); 
	//extérieur droit
	glColor3f(1 , 0.7, 0.7);
	glDrawQuad(-20, 25, 10, 1, 50, 20);
	//entrée
	glColor3f(1 , 0.6, 0.6);
	glDrawQuad(-10, 50, 10, 20, 1, 20);

	/* TROISIEME PIECE - ETAGE / CHAMBRE */
	
	/* Dessin du sol */
	glColor3f(0.9 , 1, 0.9);
	glDrawQuad(30, 35, 20.5, 40, 70, 1);
	glDrawQuad(-10, 35, 20.5, 20, 70, 1);
	glDrawQuad(5, 47.5, 20.5, 10, 45, 1);

	/* Dessin des murs sans porte */

	//exterieur gauche
	glColor3f(0.7 , 1, 0.7);
	glDrawQuad(50, 35, 30, 1, 70, 20); 
	//exterieur droit
	glColor3f(0.6 , 1, 0.6);
	glDrawQuad(-20, 35, 30, 1, 70, 20);
	//avant
	glColor3f(0.5 , 1, 0.5);
	glDrawQuad(15, 70, 30, 70, 1, 20);

	/* Murs avec porte */

	//porte balcon
	glColor3f(0.8, 1, 0.8);
	glDrawQuad(-2.5, 0.5, 30, 35, 1, 20); 
	glDrawQuad(30, 0.5, 38, 30, 1, 4);
	glDrawQuad(47.5, 0.5, 30, 5, 1, 20);

	/* QUATRIEME PIECE - RDC / SDB */
	
	/* Dessin du sol */
	glColor3f(1 , 0.9, 1);
	glDrawQuad(35, 60, 0.5, 30, 20, 1);

	/* Dessin des murs sans porte */

	//exterieur droit
	glColor3f(1 , 0.7, 1);
	glDrawQuad(50, 60, 10, 1, 20, 20); 
	//exterieur avant
	glColor3f(1 , 0.6, 1);
	glDrawQuad(35, 70, 10, 30, 1, 20);

	/* Murs avec porte */

	//porte sdb-entrée
	glColor3f(1 , 0.8, 1);
	glDrawQuad(20, 52.5, 10, 1, 5, 20); 
	glDrawQuad(20, 60, 18, 1, 10, 4);
	glDrawQuad(20, 67.5, 10, 1, 5, 20);

	/* CINQIEME PIECE - RDC / ENTREE */
	
	/* Dessin du sol */
	glColor3f(0.9, 1, 1);
	glDrawQuad(0, 60, 0.5, 40, 20, 1);

	/* Dessin des murs sans porte */

	//exterieur gauche
	glColor3f(0.7 , 1, 1);
	glDrawQuad(-20, 60, 10, 1, 20, 20); 

	/* Murs avec porte */

	//porte entrée principale
	glColor3f(0.8, 1, 1);
	glDrawQuad(-17.5, 70, 10, 5, 1, 20); 
	glDrawQuad(-10, 70, 18, 10, 1, 4);
	glDrawQuad(7.5, 70, 10, 25, 1, 20);

	/* BALCON */
	
	/* Dessin du sol */
	glColor3f(1, 1, 0.9);
	glDrawQuad(25, -5, 20.5, 40, 10, 1);

	/* Dessin des murets */

	//exterieur gauche
	glColor3f(1, 1, 0.8);
	glDrawQuad(45, -5, 25, 1, 10, 10);
	//fond 
	glColor3f(1, 1, 0.7);
	glDrawQuad(25, -10, 25, 40, 1, 10);
	//exterieur droit
	glColor3f(1, 1, 0.6);
	glDrawQuad(5, -5, 25, 1, 10, 10);

	/* Fin du dessin */
	glPopMatrix();

	/* fin de la définition de la scène */
	glFinish();
}

void glDrawRepere(float length){
	// dessin du repère
	glBegin(GL_LINES);
        //axe x
		glColor3f(1.,0.,0.);
		glVertex3f(0.,0.,0.);
		glVertex3f(length,0.,0.);
        //axe y
		glColor3f(0.,1.,0.);
		glVertex3i(0.,0.,0.);
		glVertex3i(0.,length,0.);
        //axe z
		glColor3f(0.,0.,1.);
		glVertex3i(0.,0.,0.);
		glVertex3i(0.,0.,length);
	glEnd();
}

void glDrawQuad(float x, float y, float z, float largeur, float longueur, float hauteur){
	glPushMatrix();
	glTranslated(x, y, z);
	glScaled(largeur, longueur, hauteur);
	glutSolidCube(1);
	glPopMatrix();
}
