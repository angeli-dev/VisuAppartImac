#include "../include/draw.h"


/* fonction de dessin de la scène à l'écran              */

void drawScene(Camera camera){

	/* Debut du dessin de la scène */
	glPushMatrix();

	/* placement de la caméra */
    gluLookAt(camera.position.x, camera.position.y, camera.position.z,
                camera.pointCible.x, camera.pointCible.y, camera.pointCible.z, 
                camera.axeVertical.x, camera.axeVertical.y, camera.axeVertical.z);


	glDrawRepere(50.0);

	glPushMatrix();
	glTranslated(0.5, 0.5, 0.5);
	glScaled(1.0, 1.0, 1.0);
	glColor3f(0.9 , 0.9, 1);
	glutSolidCube(1);
	glPopMatrix();

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
