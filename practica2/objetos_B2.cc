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
  
  
  /*
  void _rotacion::parametros(vector<_vertex3f> perfil, int num){
  
    unsigned int tam_perfil=perfil.size();
//  Tupla3f nuevo_vertice={0.0,0.0,0.0};
	_vertex3f vertice_aux={0.0,0.0,0.0};

   for (int i=0; i<num; i++){
     float angulo=(2*M_PI*i)/(num-1.0);
     for( int j=0; j<tam_perfil; j++){

       vertice_aux.x=perfil[j][0]*cos(angulo)-perfil[j][2]*sin(angulo);
       vertice_aux.y=perfil[j][1];
       vertice_aux.z=perfil[j][2]*cos(angulo)+perfil[j][0]*sin(angulo);

       vertices.push_back(vertice_aux);
     }
   }

   for(int i=0; i<num; i++){
     for(int j=0; j< tam_perfil-1; j++){
       int k=i*tam_perfil+j;
       caras.push_back({k,k+tam_perfil,k+tam_perfil+1});
       caras.push_back({k,k+tam_perfil+1,k+1});
     }
   }
  
  
  */
  
}

	void _rotacion::eliminar(){
	
	vertices.clear();
	caras.clear();
	perfil.clear();
	num=0;

}
	



