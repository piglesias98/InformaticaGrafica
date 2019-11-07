//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

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

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
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

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);


_vertex3f vertice_aux;
_vertex3i cara_aux;


for(int i = 0; i < n_ver; i++){
    vertice_aux.x=ver_ply[i*3];
    vertice_aux.y=ver_ply[i*3 + 1];
    vertice_aux.z=ver_ply[i*3 + 2];

    vertices.push_back(vertice_aux);
  }

for(int i = 0; i < n_car; i++){
    cara_aux._0=car_ply[i*3];
    cara_aux._1=car_ply[i*3 + 1];
    cara_aux._2=car_ply[i*3 + 2];

    caras.push_back(cara_aux);
  }


return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo)
{	
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértices


num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras 


for (int j = 0; j < num; j++) {
  for (int i = 0; i < num_aux-1; i++) {
      cara_aux._0 = i+((j+1)%num)*num_aux;
      cara_aux._1 = i+1+((j+1)%num)*num_aux;
      cara_aux._2 = i+1+j*num_aux;
      caras.push_back(cara_aux);

      cara_aux._0 = i+1+j*num_aux;
      cara_aux._1 = i+j*num_aux;
      cara_aux._2 = i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
  }
}

     
 // tapa inferior
if (fabs(perfil[0].x)>0.0)
  {
  		//Creamos el vértice de abajo
  		if (tipo==0) vertice_aux.y = perfil[0].y;
  		if (tipo==1) vertice_aux.y = -1.0;
  		if (tipo==2) vertice_aux.y = 0.0;
	  	vertice_aux.x = 0.0;
	  	vertice_aux.z = 0.0;
	  	vertices.push_back(vertice_aux);

	  	cara_aux._0 = num_aux*num;	//el último vértice añadido

	  	for (int i = 0; i < num; i++){
		   cara_aux._1 = ((i+1)%num)*num_aux;
		   cara_aux._2 = i*num_aux;
		   caras.push_back(cara_aux);
	  	}
  
  
  
  
  }
 
 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0)
  {
  
		if (tipo==0) vertice_aux.y = perfil[num_aux-1].y;
		if (tipo==1 || tipo==2) vertice_aux.y = 1.0;
		vertice_aux.x = 0.0;
		vertice_aux.z = 0.0;
     	vertices.push_back(vertice_aux);

     	cara_aux._0 = num_aux*num+1;

     	for (int i = 0; i < num; i++){
         cara_aux._1 = i*num_aux+num_aux-1;
         cara_aux._2 = ((i+1)%num)*num_aux+num_aux-1;
         caras.push_back(cara_aux);
     	}
  
  }
  
}

	void _rotacion::eliminar(){
	
	vertices.clear();
	caras.clear();
	perfil.clear();
	num=0;

}
	

//************************************************************************

_bombilla::_bombilla()
{

//perfil bombilla
// perfil pantalla

vector<_vertex3f> perfil_bombilla;
_vertex3f aux_bombilla;
for (int i =1; i<12; i++){
		aux_bombilla.x=sin(M_PI*i/12);
		aux_bombilla.y=-cos(M_PI*i/12);
		aux_bombilla.z=0.0;
		perfil_bombilla.push_back(aux_bombilla);
	}

bom.parametros(perfil_bombilla, 12, 1);

}

void _bombilla::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
glScalef(0.3,0.3,0.3);
bom.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************

_pantalla::_pantalla()
{

altura = 1.0;

// perfil pantalla
vector<_vertex3f> perfil;
_vertex3f aux;
//perfil exterior
aux.x=0.2;aux.y=0.0;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.3;aux.y=0.3;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.7;aux.y=0.7;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.8;aux.y=1.0;aux.z=0.0;
perfil.push_back(aux);
//perfil interior
aux.x=0.7;aux.y=1.0;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.6;aux.y=0.7;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.2;aux.y=0.3;aux.z=0.0;
perfil.push_back(aux);

pan.parametros(perfil,12,0);

}


void _pantalla::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
//glScalef(1.0,0.22,0.95);
pan.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}

//************************************************************************


_brazo::_brazo()
{
altura = 2.0;
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.2;aux.y=0.0;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.2;aux.y=2.0;aux.z=0.0;
perfil.push_back(aux);
br.parametros(perfil,12,0);

}


void _brazo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
//glScalef(1.0,0.22,0.95);
br.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}


//************************************************************************


_base::_base()
{
altura = 0.3;
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=1.0;aux.y=0.0;aux.z=0.0;
perfil.push_back(aux);
aux.x=1.0;aux.y=0.3;aux.z=0.0;
perfil.push_back(aux);
bas.parametros(perfil,12,0);

}


void _base::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
//glScalef(1.0,0.22,0.95);
bas.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
glPopMatrix();
}



//************************************************************************



_lampara::_lampara()
{

giro_brazo_inf = 0.0;
giro_brazo_sup = 0.0;
giro_pantalla = 0.0;


}

void _lampara::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glPushMatrix();
	base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glTranslatef(0.0,base.altura,0.0);
	glRotatef(giro_brazo_inf,0,0,1);
	brazo_inf.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPushMatrix();
		glTranslatef(0.0,brazo_inf.altura,0.0);
		glRotatef(giro_brazo_sup,0,0,1);
		brazo_sup.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPushMatrix();
			glTranslatef(0.0,brazo_sup.altura,0.0);
			glRotatef(giro_pantalla,0,0,1);
				glPushMatrix();
					glTranslatef(0.0,2* pantalla.altura/3,0.0);
					bombilla.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
				glPopMatrix();
				glPushMatrix();	
					pantalla.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
				glPopMatrix();

		glPopMatrix();
	glPopMatrix();
glPopMatrix();
}


