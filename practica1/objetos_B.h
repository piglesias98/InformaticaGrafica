//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

using namespace std;

const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;	// de tipo real porque almacenamos los números reales
//podriamos haber puesti
//vector<_vertex3f> color y asi a cada punto le incorporamos el color /y quitamos lo de rgb de draw puntos
};

//*************************************************************************
// clase triángulo
//*************************************************************************

//Cara plana más sencilla --> así creamos todas las caras planas
class _triangulos3D: public _puntos3D	//--> hija de la clase punto
{
public:

//formado por tres vertices 
/*
almacenamos por un lado la geometria
x1y1z1
x2y2z2
x3y3z3
y por otro la topologia --> como se conectan
123 (el orden en el que van los puntos
*/

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);

vector<_vertex3i> caras;	//son índices --> de tipo i pq son enteros (solo necesitamos el indie)
};


//*************************************************************************
// clase cubo
//*************************************************************************

//INTENTAR HACER EL CUBO
//solamente tenemos para implementarlo en forma de punto

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};






