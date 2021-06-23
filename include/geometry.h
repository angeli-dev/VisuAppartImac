#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef GEOMETRY_H 
#define GEOMETRY_H

//Structure qui sert pour définir un point - ok ça va servir pour les pixels
typedef struct point
{
    float x;
    float y;
    
}Point;

typedef struct Vector3D
{ 
    float x, y, z;
}Vector3D;

typedef struct Point3D
{ 
    float x, y, z;
}Point3D;

// Construit le point (x, y, z)
Point3D createPoint(float x, float y, float z);
point createPointfromFloats(float _x, float _y);
point createPoint();
// Construit le vecteur (x, y, z)
Vector3D createVector(float x, float y, float z);

// Construit le vecteur reliant les points P1 et P2
Vector3D createVectorFromPoints(Point3D p1, Point3D p2);
point create2DVectorFromPoints(point p1, point p2);

// Construit le point P + V (i.e. translation de P par V)
Point3D pointPlusVector(Point3D p, Vector3D v);
point pointPlusVector2D(point p, point v);

// Addition et soustraction des vecteurs V1 et V2
Vector3D addVectors(Vector3D v1, Vector3D v2);
Vector3D subVectors(Vector3D v1, Vector3D v2);

//Produit vectoriel des vecteurs V1 et V2
Vector3D multVectors(Vector3D v1, Vector3D v2);

// Multiplication et division d'un vecteur V par un scalaire a
Vector3D multVector(Vector3D v, float a);
point multVector2D(point v, float a);
Vector3D divVector(Vector3D v, float a);

// Produit scalaire des vecteurs V1 et V2
float dot(Vector3D a, Vector3D b);

// Norme d'un vecteur V
float norm(Vector3D v);

// Construit le vecteur normalisé du vecteur V
Vector3D normalize(Vector3D v);

float determinant(point p1, point p2);
bool intersection(Point p1, Point p2, Point v1, Point v2);

//tests pour les points et vecteurs
void printPoint3D(Point3D p);
void printVector3D(Vector3D v);

float norm_2D(point v);
point normalize_2D(point v);
#endif