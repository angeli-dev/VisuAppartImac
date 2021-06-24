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

	/* dessin du sol */
	glColor3f(0.9 , 0.9, 1);
	//glDrawQuad(1, 1, 1, 50, 50, 0.5);
	glDrawQuad(0.5, 0.5, 0, 50, 50, 0.5);

	/* dessin des murs sans porte */

	//cuisine-entrée
	glColor3f(0.8 , 0.8, 1);
	//glDrawQuad(0.5, 1, 1, 0.5, 50, 20);
	glDrawQuad(0.25, 0.5, 0.5, 0.5, 50, 20);  
	//fenetres-sejour
	glColor3f(0.7 , 0.7, 1);
	//glDrawQuad(1, 0.5, 1, 50, 0.5, 20);
	glDrawQuad(0.5, 1, 0.5, 50, 0.5, 20); 
	//sejour-sdb
	glColor3f(0.6 , 0.6, 1);
	//glDrawQuad(200, 1, 1, 0.5, 50, 20);
	glDrawQuad(100, 0.5, 0.5, 0.5, 50, 20);

	/* mur avec porte */

	//entrée principale
	glColor3f(0.5 , 0.5, 1);
	//glDrawQuad(200, 1, 1, 30, 0.5, 20);
	//glDrawQuad(1, 200, 1, 10, 0.5, 20);
	glDrawQuad(0.5, 100, 0.5, 10, 0.5, 20);
	glDrawQuad(1.16, 100, 0.5, 30, 0.5, 20);
	glDrawQuad(1.5, 100, 4.5, 10, 0.5, 4);
	

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
	glTranslated(largeur*x, longueur*y, hauteur*z);
	//glTranslated(x, y, z);
	glScaled(largeur, longueur, hauteur);
	glutSolidCube(1);
	glPopMatrix();
}
