//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID, LINEA_SOLIDO, SELECCION, PINTAR_TRIANGULO, DETERMINAR} _modo;

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
//void set_color(float r, float g, float b);
void 	determinar_triangulo(int p_r, int p_g, int p_b);
void 	draw_aristas(float r, float g, float b, int grosor);
void  draw_solido(vector<vector<float>> los_colores);
void 	draw_solido_ajedrez(vector<vector<float>> los_colores, float r2, float g2, float b2);
void  draw_seleccion_color(vector<vector<int>> los_colores);
void 	draw(_modo modo, vector<vector<float>> los_colores, float r2, float g2, float b2, float grosor, vector<vector<int>> los_colores_back, int r3, int g3, int b3);


vector<_vertex3i> caras;
vector<vector<float>> colores;
vector<vector<int>> colores_back;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5, int ini=0);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75, int ini=0);
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
void  parametros(vector<_vertex3f> perfil1, int num1, int tipo, int a=0);
void eliminar();

vector<_vertex3f> perfil; 
int num;
int ini;
};


//************************************************************************
// objeto articulado: lampara
//************************************************************************

class _pantalla: public _triangulos3D
{
public:
       _pantalla(int i=120);
void 	draw(_modo modo, vector<vector<float>> los_colores, float r2, float g2, float b2, float grosor, vector<vector<int>> los_colores_back, int r3, int g3, int b3);
float altura;

//protected:
_rotacion  pan;
int ini;
};

//************************************************************************

class _bombilla: public _triangulos3D
{
public:
       _bombilla(int i=80);
void 	draw(_modo modo, vector<vector<float>> los_colores, float r2, float g2, float b2, float grosor, vector<vector<int>> los_colores_back, int r3, int g3, int b3);
float altura;

//protected:
_rotacion  bom;
int ini;
};


//************************************************************************

class _brazo: public _triangulos3D
{
public:
       _brazo(int i=40);
void 	draw(_modo modo, vector<vector<float>> los_colores, float r2, float g2, float b2, float grosor, vector<vector<int>> los_colores_back, int r3, int g3, int b3);
float altura;

//protected:
_rotacion  br;
int ini;
};

//************************************************************************


class _base: public _triangulos3D
{
public:
       _base(int i=0);
void 	draw(_modo modo, vector<vector<float>> los_colores, float r2, float g2, float b2, float grosor, vector<vector<int>> los_colores_back, int r3, int g3, int b3);
float altura;


//protected:
_rotacion  bas;
int ini;
};


//************************************************************************

class _lampara: public _triangulos3D
{
public:
       _lampara();
void 	draw(_modo modo, vector<vector<float>> los_colores, float r2, float g2, float b2, float grosor, vector<vector<int>> los_colores_back, int r3, int g3, int b3);

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

_pantalla pantalla{0};
_brazo brazo_sup{pantalla.pan.caras.size()};
_brazo brazo_inf{brazo_sup.ini + brazo_sup.br.caras.size()};
_base base{brazo_inf.ini + brazo_inf.br.caras.size()};
_bombilla bombilla{base.ini + base.bas.caras.size()};


};



