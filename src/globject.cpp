#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include "../include/globject.hpp"
#include "../include/visu.hpp"


void GLObject::createCoordinatesCube() {
	// Vous devez fixer :
	// - le nombre de sommets (vertex_number)
	// - le tableau des coordonnees des sommets (vertex_coord)
	// - le tableau des coordonnees des normales (normal_coord)
	// - le nombre de triangles (triangle_number)
	// - le tableau des indices des sommets consistituant les triangles (triangle_index)
	// CUBE
	vertex_number = 24;
	triangle_number = 12;
	
	vertex_coord = (float*) calloc(sizeof(float),3*vertex_number);
	normal_coord = (float*) calloc(sizeof(float),3*vertex_number);
	triangle_index = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number);
	
	// CONSTRUIRE LES TABLEAUX
	float width = 1.0;
	float coord[3*24] = {
		// Face front (z = -width/2) (E,F,G,H)
		-width/2.0f,-width/2.0f,-width/2.0f,	// E
		width/2.0f,-width/2.0f,-width/2.0f,		// F
		width/2.0f,width/2.0f,-width/2.0f,		// G
		-width/2.0f,width/2.0f,-width/2.0f,		// H
		// Face back (z = width/2) (A,B,C,D)
		-width/2.0f,-width/2.0f,width/2.0f,		// A
		width/2.0f,-width/2.0f,width/2.0f,		// B
		width/2.0f,width/2.0f,width/2.0f,		// C
		-width/2.0f,width/2.0f,width/2.0f,		// D
		// Face left (x = -width/2) (E,A,D,H)
		-width/2.0f,-width/2.0f,-width/2.0f,	// E
		-width/2.0f,-width/2.0f,width/2.0f,		// A
		-width/2.0f,width/2.0f,width/2.0f,		// D
		-width/2.0f,width/2.0f,-width/2.0f,		// H
		// Face right (x = +width/2) (B,F,G,C)
		width/2.0f,-width/2.0f,width/2.0f,		// B
		width/2.0f,-width/2.0f,-width/2.0f,		// F
		width/2.0f,width/2.0f,-width/2.0f,		// G
		width/2.0f,width/2.0f,width/2.0f,		// C
		// Face top (y = +width/2) (D,C,G,H)
		-width/2.0f,width/2.0f,width/2.0f,		// D
		width/2.0f,width/2.0f,width/2.0f,		// C
		width/2.0f,width/2.0f,-width/2.0f,		// G
		-width/2.0f,width/2.0f,-width/2.0f,		// H
		// Face down (y = -width/2) (A,B,F,E)
		-width/2.0f,-width/2.0f,width/2.0f,		// A
		width/2.0f,-width/2.0f,width/2.0f,		// B
		width/2.0f,-width/2.0f,-width/2.0f,		// F
		-width/2.0f,-width/2.0f,-width/2.0f		// E
	};
	float normals[3*24] = {
		// Face back (z = -width/2) (E,F,G,H)
		0.0f,0.0f,-1.0f,	0.0f,0.0f,-1.0f,	0.0f,0.0f,-1.0f,	0.0f,0.0f,-1.0f,
		// Face front (z = width/2) (A,B,C,D)
		0.0f,0.0f,1.0f,		0.0f,0.0f,1.0f,		0.0f,0.0f,1.0f,		0.0f,0.0f,1.0f,
		// Face left (x = -width/2) (E,A,D,H)
		-1.0,0.0,0.0,		-1.0,0.0,0.0,		-1.0,0.0,0.0,		-1.0,0.0,0.0,
		// Face right (x = +width/2) (B,F,G,C)
		1.0,0.0,0.0,		1.0,0.0,0.0,		1.0,0.0,0.0,		1.0,0.0,0.0,
		// Face top (y = +width/2) (D,C,G,H)
		0.0,1.0,0.0,		0.0,1.0,0.0,		0.0,1.0,0.0,		0.0,1.0,0.0,
		// Face down (y = -width/2) (A,B,F,E)
		0.0,-1.0,0.0,		0.0,-1.0,0.0,		0.0,-1.0,0.0,		0.0,-1.0,0.0
	};
	memcpy(vertex_coord,coord,3*vertex_number*sizeof(float));
	memcpy(normal_coord,normals,3*vertex_number*sizeof(float));
	uint indexes[3*12] = {
		// Face front (z = -width/2) (E,F,G,H)
		0,1,2,		0,2,3,
		// Face back (z = width/2) (A,B,C,D)
		4,5,6,		4,6,7,
		// Face left (x = -width/2) (E,A,D,H)
		8,9,10,		8,10,11,
		// Face right (x = +width/2) (B,F,G,C)
		12,13,14,		12,14,15,
		// Face top (y = +width/2) (D,C,G,H)
		16,17,18,		16,18,19,
		// Face down (y = -width/2) (A,B,F,E)
		20,21,22,		20,22,23
	};
	memcpy(triangle_index,indexes,3*triangle_number*sizeof(float));
}

void GLObject::createCoordinatesSphere() {
	// Vous devez fixer :
	// - le nombre de sommets (vertex_number)
	// - le tableau des coordonnees des sommets (vertex_coord)
	// - le tableau des coordonnees des normales (normal_coord)
	// - le nombre de triangles (triangle_number)
	// - le tableau des indices des sommets consistituant les triangles (triangle_index)
	// CUBE
	unsigned int nb_div_tranche = 40;
	unsigned int nb_div_circle = 60;
	// 2 points à chaque extremitee + des cercles concentriques
	vertex_number = 2 + nb_div_tranche*nb_div_circle;
	// La sphere a 2 calottes en haut et en bas + (nb_div_tranche - 1) bandes de triangles 
	triangle_number = 2*nb_div_circle + (nb_div_tranche - 1)*2*nb_div_circle;
	
	vertex_coord = (float*) calloc(sizeof(float),3*vertex_number);
	normal_coord = (float*) calloc(sizeof(float),3*vertex_number);
	triangle_index = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number);

	// On rentre les sommets sans les deux points haut / bas
	float theta,phy;
	unsigned int idxV = 0;
	unsigned int idxN = 0;
	for(uint i = 0;i < nb_div_tranche;i++) {
		phy = (i+1)*M_PI/(float)(nb_div_tranche+1);
		for(uint j = 0; j < nb_div_circle; j++) {
			theta = j*2*M_PI/nb_div_circle;
			vertex_coord[idxV++] = sin(phy)*cos(theta);
			vertex_coord[idxV++] = cos(phy);
			vertex_coord[idxV++] = sin(phy)*sin(theta);
			normal_coord[idxN++] = sin(phy)*cos(theta);
			normal_coord[idxN++] = cos(phy);
			normal_coord[idxN++] = sin(phy)*sin(theta);
		}
	}
	// Le sommet (haut) => indice : nb_div_tranche*nb_div_circle
	vertex_coord[idxV++] = normal_coord[idxN++] = 0.0;
	vertex_coord[idxV++] = normal_coord[idxN++] = 1.0;
	vertex_coord[idxV++] = normal_coord[idxN++] = 0.0;
	// Le sommet (bas) => indice : nb_div_tranche*nb_div_circle + 1
	vertex_coord[idxV++] = normal_coord[idxN++] = 0.0;
	vertex_coord[idxV++] = normal_coord[idxN++] = -1.0;
	vertex_coord[idxV++] = normal_coord[idxN++] = 0.0;

	// Calotte haute 
	unsigned int idxTr = 0;
	for(uint i=0;i<nb_div_circle;i++) {
		triangle_index[idxTr++] = nb_div_tranche*nb_div_circle;
		triangle_index[idxTr++] = i;
		triangle_index[idxTr++] = (i==nb_div_circle-1) ? 0 : i+1;
	}
	// Calotte basse 
	unsigned int first_idx = (nb_div_tranche-1)*nb_div_circle;
	for(uint i=0;i<nb_div_circle;i++) {
		triangle_index[idxTr++] = nb_div_tranche*nb_div_circle+1;
		triangle_index[idxTr++] = first_idx + i;
		triangle_index[idxTr++] = (i==0) ? first_idx + nb_div_circle -1 : first_idx + i - 1;
	}
	// Bandes de triangles
	unsigned int A,B,C,D; // A (i,j) / B(i+1,j) / C(i+1,j+1) / D(i,j+1)
	for(uint i = 0;i < nb_div_tranche-1;i++) {
		for(uint j = 0;j < nb_div_circle ; j++) {
			A = i*nb_div_circle+j;
			B = (i+1)*nb_div_circle+j;
			C = (j==nb_div_circle-1) ? (i+1)*nb_div_circle : (i+1)*nb_div_circle+j+1;
			D = (j==nb_div_circle-1) ? i*nb_div_circle : i*nb_div_circle + j + 1;
			triangle_index[idxTr++] = A;
			triangle_index[idxTr++] = B;
			triangle_index[idxTr++] = C;
			triangle_index[idxTr++] = A;
			triangle_index[idxTr++] = C;
			triangle_index[idxTr++] = D;
		}
	}

}

void GLObject::createCoordinatesQuad() {
	// Vous devez fixer :
	// - le nombre de sommets (vertex_number)
	// - le tableau des coordonnees des sommets (vertex_coord)
	// - le tableau des coordonnees des normales (normal_coord)
	// - le nombre de triangles (triangle_number)
	// - le tableau des indices des sommets consistituant les triangles (triangle_index)
	// QUAD
	// Des bandes de n*n points donc n-1 * n-1 carrés
	int nb_pt_per_side = 100;
	int nb_div = nb_pt_per_side - 1;
	vertex_number = nb_pt_per_side*nb_pt_per_side;
	// 2 triange par carré 
	triangle_number = 2*nb_div*nb_div;
	
	vertex_coord = (float*) calloc(sizeof(float),3*vertex_number);
	normal_coord = (float*) calloc(sizeof(float),3*vertex_number);
	triangle_index = (unsigned int*) calloc(sizeof(unsigned int),3*triangle_number);

	unsigned int idx = 0;
	unsigned int idxn = 0;
	float width = 1.0;
	for(int i=0;i<nb_pt_per_side;i++) {
		for(int j=0;j<nb_pt_per_side;j++) {
			vertex_coord[idx++]  = - width/2.0 + j*width/(float)nb_div; 
			vertex_coord[idx++]  = 0.0;
			vertex_coord[idx++]  = width/2.0 - i*width/(float)nb_div; 
			normal_coord[idxn++] = 0.0;
			normal_coord[idxn++] = 1.0;
			normal_coord[idxn++] = 0.0;
		}
	}

	unsigned int idxt = 0;
	for(int i=0;i<nb_div;i++) {
		for(int j=0;j<nb_div;j++) {
			triangle_index[idxt++] = i*nb_pt_per_side + j;
			triangle_index[idxt++] = i*nb_pt_per_side + j + 1;
			triangle_index[idxt++] = (i+1)*nb_pt_per_side + j + 1;
			triangle_index[idxt++] = i*nb_pt_per_side + j;
			triangle_index[idxt++] = (i+1)*nb_pt_per_side + j + 1;
			triangle_index[idxt++] = (i+1)*nb_pt_per_side + j;
		}
	}

	/*
	float coord[3*4] = {
		-width/2.0f,0.0f,width/2.0f,			// A
		width/2.0f,0.0f,width/2.0f,				// B
		width/2.0f,0.0f,-width/2.0f,			// C
		-width/2.0f,0.0f,-width/2.0f			// D
	};
	float normals[3*4] = {
		0.0f,1.0f,0.0f,		
		0.0f,1.0f,0.0f,		
		0.0f,1.0f,0.0f,
		0.0f,1.0f,0.0f
	};
	memcpy(vertex_coord,coord,3*vertex_number*sizeof(float));
	memcpy(normal_coord,normals,3*vertex_number*sizeof(float));
	uint indexes[3*12] = {
		// A,B,C and A,C,D
		0,1,2,		0,2,3
	};
	memcpy(triangle_index,indexes,3*triangle_number*sizeof(float));
	*/
}

void GLObject::createCoordinates() {

	if (triangle_index != NULL) free(triangle_index);
	if (vertex_coord != NULL) free(vertex_coord);
	if (normal_coord != NULL) free(normal_coord);

	if (type_objet == CUBE) {
		createCoordinatesCube();
	}
	else if (type_objet == SPHERE) {
		createCoordinatesSphere();
	}
	else if (type_objet == QUAD) {
		createCoordinatesQuad();
	}
	else  {
		std::cerr<<"Primitive non connue"<<std::endl;
		exit(1);
	}
}

void GLObject::glDrawObject() {
	float black[3] = {0.0,0.0,0.0};
	float white[3] = {1.0,1.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,black);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,coef_ref_dif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,128.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,vertex_coord);
	glNormalPointer(GL_FLOAT,0,normal_coord);
	glDrawElements(GL_TRIANGLES,3*triangle_number,GL_UNSIGNED_INT,triangle_index);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

