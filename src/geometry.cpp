#include "../include/geometry.h"

// Construit le point (x, y, z)
Point3D createPoint(float x, float y, float z)
{
    Point3D newPoint;
    newPoint.x=x;
    newPoint.y=y;
    newPoint.z=z;
    return newPoint;
}

point createPointfromFloats(float _x, float _y)
{
	point point;
    point.x = _x;
    point.y = _y;
	return point;
}
point createPoint()
{	
	point point;
    point.x = 0;
    point.y = 0;
	return point;
}

// Construit le vecteur (x, y, z)
Vector3D createVector(float x, float y, float z)
{
    Vector3D newVecteur;
    newVecteur.x=x;
    newVecteur.y=y;
    newVecteur.z=z;
    return newVecteur;
}

// Construit le vecteur reliant les points P1 et P2
Vector3D createVectorFromPoints(Point3D p1, Point3D p2)
{
    Vector3D newVecteur;
    newVecteur.x=p2.x-p1.x;
    newVecteur.y=p2.y-p1.y;
    newVecteur.z=p2.z-p1.z;
    return newVecteur;
}

point create2DVectorFromPoints(point p1, point p2){
    point vector;
    vector.x = p2.x - p1.x;
    vector.y = p2.y - p1.y;
    return vector;
}

// Construit le point P + V (i.e. translation de P par V)
Point3D pointPlusVector(Point3D p, Vector3D v)
{
    Point3D newPoint;
    newPoint.x=p.x+v.x;
    newPoint.y=p.y+v.y;
    newPoint.z=p.z+v.z;
    return newPoint;
}
point pointPlusVector2D(point p, point v)
{
    point newPoint;
    newPoint.x=p.x+v.x;
    newPoint.y=p.y+v.y;
    return newPoint;
}

// Addition et soustraction des vecteurs V1 et V2
Vector3D addVectors(Vector3D v1, Vector3D v2)
{
    Vector3D newVecteur;
    newVecteur.x=v1.x+v2.x;
    newVecteur.y=v1.y+v2.y;
    newVecteur.z=v1.z+v2.z;
    return newVecteur;
}
Vector3D subVectors(Vector3D v1, Vector3D v2)
{
    Vector3D newVecteur;
    newVecteur.x=v1.x-v2.x;
    newVecteur.y=v1.y-v2.y;
    newVecteur.z=v1.z-v2.z;
    return newVecteur;
}

point subVectors_2D(point v1, point v2)
{
    point newVecteur;
    newVecteur.x=v1.x-v2.x;
    newVecteur.y=v1.y-v2.y;
    return newVecteur;
}

//Produit vectoriel des vecteurs V1 et V2
Vector3D multVectors(Vector3D v1, Vector3D v2){
    Vector3D newVecteur;
    newVecteur.x=v1.y*v2.z-v2.y*v1.z;
    newVecteur.y=v1.z*v2.x-v2.z*v1.x;
    newVecteur.z=v1.x*v2.y-v2.x*v1.y;
    return newVecteur;
}

// Multiplication et division d'un vecteur V par un scalaire a
Vector3D multVector(Vector3D v, float a)
{
    Vector3D newVecteur;
    newVecteur.x=v.x*a;
    newVecteur.y=v.y*a;
    newVecteur.z=v.z*a;
    return newVecteur;
}
point multVector2D(point v, float a)
{
    Point newVecteur;
    newVecteur.x=v.x*a;
    newVecteur.y=v.y*a;
    return newVecteur;
}
Vector3D divVector(Vector3D v, float a)
{
    Vector3D newVecteur;
    if (a!=0){
        newVecteur.x=v.x/a;
        newVecteur.y=v.y/a;
        newVecteur.z=v.z/a;
    }
    else{
        return v;
    }
    return newVecteur;
}

// Produit scalaire des vecteurs V1 et V2
float dot(Vector3D a, Vector3D b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

float dot_2D(Point a, Point b)
{
    return a.x*b.x + a.y*b.y;
}

// Norme d'un vecteur V
float norm(Vector3D v)
{
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

// Construit le vecteur normalisé du vecteur V
Vector3D normalize(Vector3D v)
{
   float norme=norm(v);
   if(norme!=0)
   {
       v.x/=norme;
       v.y/=norme;
       v.z/=norme;
   }
   return v;
}

float determinant(point p1, point p2){
    return p1.x * p2.y - p1.y * p2.x;
}

bool intersection(Point p1, Point p2, Point v1, Point v2){
    point d1 = create2DVectorFromPoints(p1,p2);
    point d2 = create2DVectorFromPoints(v1,v2);
    float inv_det = -1/determinant(d1,d2);
    point inv_d2 = createPointfromFloats(-d2.y, d2.x);
    point inv_d1 = createPointfromFloats(-d1.y, d1.x);
    float t1 = inv_det * dot_2D(inv_d2,subVectors_2D(v1,p1));
    float t2 = inv_det * dot_2D(inv_d1,subVectors_2D(v1,p1));
    return (0 <= t1 && t1 <= 1
         && 0 <= t2 && t2 <= 1);
}

void printPoint3D(Point3D p)
{
    printf("p(%f,%f,%f)",p.x, p.y, p.z);
}
void printVector3D(Vector3D v)
{
    printf("p(%f,%f,%f)",v.x, v.y, v.z);
}

float norm_2D(point v){
    return sqrtf(v.x*v.x + v.y*v.y);
}

point normalize_2D(point v){
    float norme=norm_2D(v);
   if(norme!=0)
   {
       v.x/=norme;
       v.y/=norme;
   }
   return v;
}