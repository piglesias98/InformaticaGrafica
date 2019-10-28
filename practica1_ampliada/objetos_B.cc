//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B.h"
#include<stdlib.h>
#include<time.h>


//cuando creemos el cubo ponemos en practica1_B.cc

//*************************************************************************
// _puntos3D
//*************************************************************************


_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

//pinta una lista de vértices , size nos duevelve el tamaño
void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}



//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}



//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();


}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//glLineWidth(grosor);
glColor3f(r1,g2,b2);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if (i%2==0) glColor3f(r2,g2,b2);
	else glColor3f(r1,g2,b2);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();



}

int _triangulos3D::generadorColorAleatorio(){
	srand(time(NULL));
	return (1+rand()%(256-1));
}


//*************************************************************************
// dibujar cada cara de un color aleatorio
//*************************************************************************

void _triangulos3D::draw_solido_aleatorio()
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
for (i=0;i<caras.size();i++){
glBegin(GL_TRIANGLES);
	glColor3f(colores[i].r,colores[i].g, colores[i].b);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
glEnd();
}



}



//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices

vertices.resize(8);

vertices[0].x = 0;
vertices[0].y = 0;
vertices[0].z = tam;

vertices[1].x = tam;
vertices[1].y = 0;
vertices[1].z = tam;

vertices[2].x = tam;
vertices[2].y = 0;
vertices[2].z = 0;

vertices[3].x = 0;
vertices[3].y = 0;
vertices[3].z = 0;

vertices[4].x = 0;
vertices[4].y = tam;
vertices[4].z = tam;

vertices[5].x = tam;
vertices[5].y = tam;
vertices[5].z = tam;

vertices[6].x = tam;
vertices[6].y = tam;
vertices[6].z = 0;

vertices[7].x = 0;
vertices[7].y = tam;
vertices[7].z = 0;

// triangulos
//tendría doce caras
//resize 12

caras.resize(12);

caras[0]._0=0;
caras[0]._1=1;
caras[0]._2=4;

caras[1]._0=1;
caras[1]._1=5;
caras[1]._2=4;

caras[2]._0=1;
caras[2]._1=2;
caras[2]._2=5;

caras[3]._0=2;
caras[3]._1=6;
caras[3]._2=5;

caras[4]._0=2;
caras[4]._1=3;
caras[4]._2=6;

caras[5]._0=3;
caras[5]._1=7;
caras[5]._2=6;

caras[6]._0=3;
caras[6]._1=0;
caras[6]._2=7;

caras[7]._0=0;
caras[7]._1=4;
caras[7]._2=7;

caras[8]._0=4;
caras[8]._1=5;
caras[8]._2=6;

caras[9]._0=4;
caras[9]._1=6;
caras[9]._2=7;

caras[10]._0=3;
caras[10]._1=1;
caras[10]._2=0;

caras[11]._0=3;
caras[11]._1=2;
caras[11]._2=1;




}


//*************************************************************************
// clase piramide
//*************************************************************************



_piramide::_piramide(float tam, float al)
{

//tam lo pasamos por parametros, que es la base

//GROMETRIA
//vertices 
//piramide tiene cinco puntos
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;	//seria el que está en el eje z alejado
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;	//el de más a la izq
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;	//el de la altura
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

//TOPOLOGIA = CARAS --> tiene seis caras pq la de la base hay que dividirla en dos (tam min es triangulo)
caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;	//lo estamos asignando a los índices de arriba
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;

//la cara de atras ciudado en sentido contrario a las agujas de reloj, pero como está atrás es a favor de las agujas de reloj

// colores
colores.resize(6);
srand(time(NULL));
for (int i=0;i<6;i++){
	
	colores[i].r=rand()%255/255.0;
	colores[i].g=rand()%255/255.0;
	colores[i].b=rand()%255/255.0;

}
}
