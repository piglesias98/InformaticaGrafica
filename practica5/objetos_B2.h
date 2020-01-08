//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID, SELECCION} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void  draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void  draw_seleccion_color(float r, float g, float b);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);


vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

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

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1, int tipo);
void eliminar();

vector<_vertex3f> perfil; 
int num;
};


//************************************************************************
// objeto articulado: lampara
//************************************************************************

class _pantalla: public _triangulos3D
{
public:
       _pantalla();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
float altura;

protected:
_rotacion  pan;
};

//************************************************************************

class _bombilla: public _triangulos3D
{
public:
       _bombilla();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
float altura;

protected:
_rotacion  bom;
};


//************************************************************************

class _brazo: public _triangulos3D
{
public:
       _brazo();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
float altura;

protected:
_rotacion  br;
};

//************************************************************************


class _base: public _triangulos3D
{
public:
       _base();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
float altura;

protected:
_rotacion  bas;
};


//************************************************************************

class _lampara: public _triangulos3D
{
public:
       _lampara();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float giro_brazo_inf;
float giro_brazo_sup;
float giro_pantalla;
float traslacion_x;
float traslacion_y;

float giro_brazo_inf_min;
float giro_brazo_sup_min;
float giro_pantalla_min;
float giro_brazo_inf_max;
float giro_brazo_sup_max;
float giro_pantalla_max;


protected:
_pantalla pantalla;
_brazo brazo_sup;
_brazo brazo_inf;
_base base;
_bombilla bombilla;
};



