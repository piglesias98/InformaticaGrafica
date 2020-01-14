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

void _triangulos3D::draw_solido(vector<vector<float>> los_colores)
{
int i;
for (i=0;i<caras.size();i++){
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3f(los_colores[i][0],los_colores[i][1],los_colores[i][2]);
	glBegin(GL_TRIANGLES);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	glEnd();
	}
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(vector<vector<float>> los_colores, float r2, float g2, float b2)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//glLineWidth(grosor);
glColor3f(r2,g2,b2);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if (i%2==0) glColor3f(r2,g2,b2);
	else glColor3f(los_colores[i][0],los_colores[i][1],los_colores[i][2]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}


//*************************************************************************
// dibujar con seleccion de color
//*************************************************************************

void _triangulos3D::draw_seleccion_color(vector<vector<int>> los_colores)
{
int i;
for (i=0;i<caras.size();i++){
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3ub(los_colores[i][0],los_colores[i][1],los_colores[i][2]);
	glBegin(GL_TRIANGLES);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	glEnd();
	}

   
}


//*************************************************************************
// dibujar el triangulo seleccionado
//*************************************************************************

void _triangulos3D::determinar_triangulo(int p_r, int p_g, int p_b)
{
	
	int cara = -1;
	for (int i=0; i<caras.size(); i++){
		if (colores_back[i][0]==p_r && colores_back[i][1]==p_g && colores_back[i][2]==p_b){
			cara=i;
		}
	}
	
	if (cara!=-1){
		if (colores[cara][0] == 1.0 && colores[cara][1] == 0.0){	//si era rojo lo ponemos amarillo
			colores[cara][0]=1.0;
			colores[cara][1]=1.0;
			colores[cara][2]=0.0;
		}else{								//si no era rojo lo volvemos a poner a rojo
			colores[cara][0]=1.0;
			colores[cara][1]=0.0;
			colores[cara][2]=0.0;
	}
	}
	
	
	
}




//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, vector<vector<float>> los_colores, float r2, float g2, float b2, float grosor, vector<vector<int>> los_colores_back, int r3, int g3, int b3)
{
switch (modo){
	case POINTS:draw_puntos(r2, g2, b2, grosor);break;
	case EDGES:draw_aristas(r2,g2,b2, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(los_colores, r2, g2, b2);break;
	case SOLID:draw_solido(los_colores);break;
	case LINEA_SOLIDO:
		draw_aristas(0.1,0.1,0.1, grosor);	//pintamos las líneas
		draw_solido(los_colores);break;	//pintamos el relleno	
	case SELECCION:
		draw_seleccion_color(los_colores_back);break;
	case DETERMINAR:
		determinar_triangulo(r3, g3, b3);break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam, int ini)
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
for (int i = 0; i<caras.size(); i++){
	colores.push_back({1.0,0.0,0.0});
}

for (int i=ini; i<caras.size()+ini; i++){
	int r = (i/256)/256;
	int g = (i/256)%256;
	int b = (i%256);
	colores_back.push_back({r,g,b});
}


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

_piramide::_piramide(float tam, float al, int ini)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);

for (int i = 0; i<caras.size(); i++){
	colores.push_back({1.0,0.0,0.0});
}

for (int i=ini; i<caras.size()+ini; i++){
	int r = (i/256)/256;
	int g = (i/256)%256;
	int b = (i%256);
	colores_back.push_back({r,g,b});
}


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


for (int i = 0; i<caras.size(); i+=3){
	colores.push_back({1.0,0.0,0.0});
}

for (int i=0; i<caras.size(); i++){
	int r = (i/256)/256;
	int g = (i/256)%256;
	int b = (i%256);
	colores_back.push_back({r,g,b});
}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo, int a)
{	
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;
ini=a;
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
  
  for (int i = 0; i<caras.size(); i++){
	colores.push_back({1.0,0.0,0.0});
	}

	for (int i=ini; i<ini+caras.size(); i++){
		int r = (i/256)/256;
		int g = (i/256)%256;
		int b = (i%256);
		colores_back.push_back({r,g,b});
	}
}

	void _rotacion::eliminar(){
	
	vertices.clear();
	caras.clear();
	perfil.clear();
	num=0;

}
	

//************************************************************************

_bombilla::_bombilla(int i)
{

//perfil bombilla
// perfil pantalla
ini=i;
vector<_vertex3f> perfil_bombilla;
_vertex3f aux_bombilla;
for (int i =1; i<12; i++){
		aux_bombilla.x=sin(M_PI*i/12);
		aux_bombilla.y=-cos(M_PI*i/12);
		aux_bombilla.z=0.0;
		perfil_bombilla.push_back(aux_bombilla);
	}

bom.parametros(perfil_bombilla, 12, 1, ini);

}

void _bombilla::draw(_modo modo, vector<vector<float>> los_colores, float r2, float g2, float b2, float grosor, vector<vector<int>> los_colores_back, int r3, int g3, int b3)
{
glPushMatrix();
glScalef(0.3,0.3,0.3);
bom.draw(modo, bom.colores, r2, g2, b2, grosor, bom.colores_back, r3, g3, b3);
glPopMatrix();
}

//************************************************************************

_pantalla::_pantalla(int i)
{
ini = i;
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

pan.parametros(perfil,12,0, ini);

}


void _pantalla::draw(_modo modo, vector<vector<float>> los_colores, float r2, float g2, float b2, float grosor, vector<vector<int>> los_colores_back, int r3, int g3, int b3)
{
glPushMatrix();
//glScalef(1.0,0.22,0.95);
pan.draw(modo, pan.colores, r2, g2, b2, grosor, pan.colores_back, r3, g3, b3);
glPopMatrix();
}

//************************************************************************


_brazo::_brazo(int i)
{
altura = 2.0;
ini = i;
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=0.2;aux.y=0.0;aux.z=0.0;
perfil.push_back(aux);
aux.x=0.2;aux.y=2.0;aux.z=0.0;
perfil.push_back(aux);
br.parametros(perfil,12,0, ini);

}


void _brazo::draw(_modo modo, vector<vector<float>> los_colores, float r2, float g2, float b2, float grosor, vector<vector<int>> los_colores_back, int r3, int g3, int b3)
{
glPushMatrix();
//glScalef(1.0,0.22,0.95);
br.draw(modo, br.colores, r2, g2, b2, grosor, br.colores_back, r3, g3, b3);
glPopMatrix();
}


//************************************************************************


_base::_base(int i)
{
ini =i;
printf("ini base %d",ini);
altura = 0.3;
// perfil para un cilindro
vector<_vertex3f> perfil;
_vertex3f aux;
aux.x=1.0;aux.y=0.0;aux.z=0.0;
perfil.push_back(aux);
aux.x=1.0;aux.y=0.3;aux.z=0.0;
perfil.push_back(aux);
bas.parametros(perfil,12,0, ini);

}


void _base::draw(_modo modo, vector<vector<float>> los_colores, float r2, float g2, float b2, float grosor, vector<vector<int>> los_colores_back, int r3, int g3, int b3)
{
glPushMatrix();
bas.draw(modo, bas.colores, r2, g2, b2, grosor, bas.colores_back, r3, g3, b3);
glPopMatrix();
}



//************************************************************************



_lampara::_lampara()
{

giro_brazo_inf = 0.0;
giro_brazo_sup = 0.0;
giro_pantalla = 0.0;
traslacion_x = 0.0;
traslacion_y =0.0;

giro_brazo_inf_min=-30.0;
giro_brazo_sup_min=-45.0;
giro_pantalla_min=-90.0;
giro_brazo_inf_max=30.0;
giro_brazo_sup_max=45.0;
giro_pantalla_max=90.0;

//pantalla(0);
//brazo_sup(pantalla.pan.caras.size());



}

void _lampara::draw(_modo modo, vector<vector<float>> los_colores, float r2, float g2, float b2, float grosor, vector<vector<int>> los_colores_back, int r3, int g3, int b3)
{
glPushMatrix();
	glTranslatef(0.0,traslacion_y,0.0);
	glTranslatef(traslacion_x,0.0,0.0);
	base.draw(modo, base.colores, r2, g2, b2, grosor, base.colores_back, r3, g3, b3);
	glTranslatef(0.0,base.altura,0.0);
	glRotatef(giro_brazo_inf,0,0,1);
	brazo_inf.draw(modo, brazo_inf.colores, r2, g2, b2, grosor, brazo_inf.colores_back, r3, g3, b3);
	glPushMatrix();
		glTranslatef(0.0,brazo_inf.altura,0.0);
		glRotatef(giro_brazo_sup,0,0,1);
		brazo_sup.draw(modo, brazo_sup.colores, r2, g2, b2, grosor, brazo_sup.colores_back, r3, g3, b3);
		glPushMatrix();
			glTranslatef(0.0,brazo_sup.altura,0.0);
			glRotatef(giro_pantalla,0,0,1);
				glPushMatrix();
					glTranslatef(0.0,2* pantalla.altura/3,0.0);
					bombilla.draw(modo, bombilla.colores, r2, g2, b2, grosor, bombilla.colores_back, r3, g3, b3);
				glPopMatrix();
				glPushMatrix();	
					pantalla.draw(modo, pantalla.colores, r2, g2, b2, grosor, pantalla.colores_back, r3, g3, b3);
				glPopMatrix();

		glPopMatrix();
	glPopMatrix();
glPopMatrix();
}


