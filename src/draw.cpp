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

	/* PREMIERE PIECE - SEJOUR */

	/* dessin du sol */
	glColor3f(0.9 , 0.9, 1);
	glDrawQuad(25, 25, 0.5, 50, 50, 1);

	/* dessin des murs sans porte */

	//fenetres
	glColor3f(0.7 , 0.7, 1);
	glDrawQuad(25, 0.5, 10, 50, 1, 20); 
	//sdb
	glColor3f(0.6 , 0.6, 1);
	glDrawQuad(50, 25, 10, 1, 50, 20);

	/* mur avec porte */

	//porte séjour-cuisine
	glColor3f(0.8 , 0.8, 1);
	glDrawQuad(0.5, 15, 10, 1, 30, 20); 
	glDrawQuad(0.5, 45, 10, 1, 10, 20);
	glDrawQuad(0.5, 35, 18, 1, 10, 4);
	//porte séjour-entrée
	glColor3f(0.5 , 0.5, 1);
	glDrawQuad(5, 50, 10, 10, 1, 20);
	glDrawQuad(35, 50, 10, 30, 1, 20);
	glDrawQuad(15, 50, 18, 10, 1, 4);

	/* DEUXIEME PIECE - CUISINE */

	/* dessin du sol */
	glColor3f(1 , 0.9, 0.9);
	glDrawQuad(-10, 25, 0.5, 20, 50, 1);

	/* dessin des murs sans porte */

	//fenetre
	glColor3f(1 , 0.8, 0.8);
	glDrawQuad(-10, 0, 10, 20, 1, 20); 
	//extérieur droit
	glColor3f(1 , 0.7, 0.7);
	glDrawQuad(-20, 25, 10, 1, 50, 20);
	//entrée
	glColor3f(1 , 0.6, 0.6);
	glDrawQuad(-10, 50, 10, 20, 1, 20);

	/* TROISIEME PIECE - SALLE DE BAIN */


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
