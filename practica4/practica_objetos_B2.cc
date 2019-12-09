//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B2.h"
#include <iostream>


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, ARTICULADO} _tipo_objeto;
_tipo_objeto t_objeto=ARTICULADO;
_modo   modo=POINTS;

typedef enum{CONO, ESFERA, CILINDRO} _tipo_rotacion;
_tipo_rotacion t_rotacion=CILINDRO;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply; 
_rotacion rotacion; 
_pantalla pantalla;
_brazo brazo;
_base base;
_lampara lampara;
_bombilla bombilla;

//Variables para la animación
int valor_lento = 0;
int valor_rapido = 0;
int flag_giro_brazo_sup=1;
int flag_giro_brazo_inf=0;
int flag_giro_pantalla=0;

// _objeto_ply *ply1;


//luces
_luz luz_fija;
_luz luz_dinamica; 

// Movimiento luz
/*
float x_luz = 0;
float y_luz = 0;
float z_luz = 10;
int alpha_luz = 0;
int beta_luz = 0;
int color_luz = -1;
*/

float x_luz = 10;
float y_luz = 10;
float z_luz = 10;
int alpha_luz = 0;
int beta_luz = 0;

int mat=0;
int activar=0;

//Material
_vertex4f ambiente_difusa = {0.022, 0.17, 0.02, 1.0};
_vertex4f especular = {0.63, 0.73, 0.63, 1.0};
float brillo = 10;



//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//***************************************************************************
// Animación
//
// 
// 
//***************************************************************************

void actualizaPos(){
	//Pantalla
	if (flag_giro_pantalla == 1){
		lampara.giro_pantalla+=valor_lento;
		if (lampara.giro_pantalla>lampara.giro_pantalla_max){
			lampara.giro_pantalla=lampara.giro_pantalla_max;
			flag_giro_pantalla=0;
		}
	}else{
		lampara.giro_pantalla-=valor_lento;
		if (lampara.giro_pantalla<lampara.giro_pantalla_min){
			lampara.giro_pantalla=lampara.giro_pantalla_min;
			flag_giro_pantalla=1;
		}
	}
	
	
	//Brazo superior
	if (flag_giro_brazo_sup == 1){
		lampara.giro_brazo_sup+=valor_rapido;
		if (lampara.giro_brazo_sup>lampara.giro_brazo_sup_max){
			lampara.giro_brazo_sup=lampara.giro_brazo_sup_max;
			flag_giro_brazo_sup=0;
		}
	}else{
		lampara.giro_brazo_sup-=valor_rapido;
		if (lampara.giro_brazo_sup<lampara.giro_brazo_sup_min){
			lampara.giro_brazo_sup=lampara.giro_brazo_sup_min;
			flag_giro_brazo_sup=1;
		}
	}
	
	
	//Brazo inferior
	if (flag_giro_brazo_inf == 1){
		lampara.giro_brazo_inf+=valor_lento;
		if (lampara.giro_brazo_inf>lampara.giro_brazo_inf_max){
			lampara.giro_brazo_inf=lampara.giro_brazo_inf_max;
			flag_giro_brazo_inf=0;
		}
	}else{
		lampara.giro_brazo_inf-=valor_lento;
		if (lampara.giro_brazo_inf<lampara.giro_brazo_inf_min){
			lampara.giro_brazo_inf=lampara.giro_brazo_inf_min;
			flag_giro_brazo_inf=1;
		}
	}
}

void iluminacionRotacion(){

if (activar==1){
alpha_luz++;
beta_luz++;
}

}

void on_idle(){
	actualizaPos();
	iluminacionRotacion();
	glutPostRedisplay();
}

//**************************************************************************
// Función para cambiar el material
//***************************************************************************

void material(){
	switch(mat){
	case 0:
	//Rubí
		ambiente_difusa = {0.61424, 0.04136, 0.04136, 0.55};
		especular = {0.297254, 0.626959, 0.626959, 0.8};
		brillo = 12.8;
		break;
	case 1:
		//Pewter
		ambiente_difusa = {0.4274, 0.470588, 0.541176, 1.0};
		especular = {0.333333, 0.333333, 0.521569, 1.0};
		brillo = 9.8461;
		break;
	case 2:
	//Cobre
		ambiente_difusa = {0.5508, 0.2118, 0.066, 1.0};
		especular = {0.580, 0.2232, 0.069, 1.0};
		brillo = 51.2;
		break;;
		break;
	case 3:
		ambiente_difusa = {0.022, 0.17, 0.02, 1.0};
		especular = {0.63, 0.73, 0.63, 1.0};
		brillo = 10;
		break;
	case 4:
		mat = -1;
		break;
	}
	
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}

//esfera

float esfera(float x){
	return sqrt(1-x*x);
}


//***************************************************************************
// Funcion que crea los perfiles de los objetos de rotacion
//***************************************************************************

vector<_vertex3f> perfil_rotacion(){
	vector<_vertex3f> perfil2;
	_vertex3f aux;
	switch(t_rotacion){
		case CILINDRO:
			aux.x=1.0; aux.y=-1.0; aux.z=0.0;
			perfil2.push_back(aux);
			aux.x=1.0; aux.y=1.0; aux.z=0.0;
			perfil2.push_back(aux);
		break;
		case ESFERA:
			for (int i =1; i<6; i++){
				aux.x=sin(M_PI*i/6);
				aux.y=-cos(M_PI*i/6);
				aux.z=0.0;
				perfil2.push_back(aux);
			}
		break;	
		case CONO:
			aux.x=0.5; aux.y=0.0; aux.z=0.0;
			perfil2.push_back(aux);
		break;
	}
	return perfil2;
}



//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{

//luz_fija.encender(GL_LIGHT0, 0, 0, 0, 0, 0, 1.0, 1.0, 1.0);
luz_dinamica.encender(GL_LIGHT1, x_luz, y_luz, z_luz, alpha_luz, beta_luz, 1.0, 0.0, 1.0);//QUEREMOS QUE SEA DE COLOR MAGENTA


switch (t_objeto){
	case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2, ambiente_difusa, especular, brillo);break;
	case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2, ambiente_difusa, especular, brillo);break;
        case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2, ambiente_difusa, especular, brillo);break;
        case ROTACION:        
        rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2, ambiente_difusa, especular, brillo);break;
        case ARTICULADO:
        lampara.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2, ambiente_difusa, especular, brillo);break;
        
	}

}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{

clean_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
vector<_vertex3f> nulo = {{0.0,0.0,0.0}};
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_CHESS;break;
	case '5':modo=SOLID_ILLUMINATED_FLAT;break;
	case '6':modo=SOLID_ILLUMINATED_GOURAUD;break;
        case 'P':t_objeto=PIRAMIDE;break;
        case 'C':t_objeto=CUBO;break;
        case 'O':t_objeto=OBJETO_PLY;break;	
        case 'R':t_objeto=ROTACION;break;
        case 'A':t_objeto=ARTICULADO;break;
        case 'X':valor_lento = 1; valor_rapido=3;break;
        case 'Z':valor_lento = 0; valor_rapido=0;break;
        case 'K':activar=1;break;
        case 'M':mat++;material();break;
        
			  case 'E':t_rotacion=ESFERA;
			  				rotacion.eliminar();
			  				rotacion.parametros(perfil_rotacion(), 6, 1);
		     				break;
			  case 'I':t_rotacion=CILINDRO;
			  				rotacion.eliminar();
			  				rotacion.parametros(perfil_rotacion(), 20, 0);
		     				break;
		   case 'N':t_rotacion=CONO;
		   				rotacion.eliminar();
							rotacion.parametros(perfil_rotacion(), 20, 2);
							break;
							
			  
	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	case GLUT_KEY_F1:lampara.giro_pantalla+=1;
							if (lampara.giro_pantalla>lampara.giro_pantalla_max) lampara.giro_pantalla=lampara.giro_pantalla_max;
		             break;
	case GLUT_KEY_F2:lampara.giro_pantalla-=1;
		             if (lampara.giro_pantalla<lampara.giro_pantalla_min) lampara.giro_pantalla=lampara.giro_pantalla_min;
		             break;
	case GLUT_KEY_F3:lampara.giro_brazo_sup+=1;
							if (lampara.giro_brazo_sup>lampara.giro_brazo_sup_max) lampara.giro_brazo_sup=lampara.giro_brazo_sup_max;
							break;
	case GLUT_KEY_F4:lampara.giro_brazo_sup-=1;
							if (lampara.giro_brazo_sup<lampara.giro_brazo_sup_min) lampara.giro_brazo_sup=lampara.giro_brazo_sup_min;
							break;
	case GLUT_KEY_F5:lampara.giro_brazo_inf+=1;
							if (lampara.giro_brazo_inf>lampara.giro_brazo_inf_max) lampara.giro_brazo_inf=lampara.giro_brazo_inf_max;
							break;
	case GLUT_KEY_F6:lampara.giro_brazo_inf-=1;
							if (lampara.giro_brazo_inf<lampara.giro_brazo_inf_min) lampara.giro_brazo_inf=lampara.giro_brazo_inf_min;
							break;
	case GLUT_KEY_F7:lampara.traslacion_x+=0.5;break;
	case GLUT_KEY_F8:lampara.traslacion_x-=0.5;break;
	}
glutPostRedisplay();
}






//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
//glEnable(GL_DEPTH_TEST);
//change_projection();
//1glViewport(0,0,Window_width,Window_high);

//se deshabilita el z-buffer
glClearDepth (1.0);
glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



}







	

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{
/*
vector<_vertex3f> perfil2;
_vertex3f aux;

aux.x=1.0; aux.y=-1.0; aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.0; aux.y=1.0; aux.z=0.0;
perfil2.push_back(aux);
*/
/*
vector<_vertex3f> perfil2;
perfil2={  {1.0,1.0,0.0},
            {1.0,-1.0,0.0}};
*/
rotacion.eliminar();
rotacion.parametros(perfil_rotacion(),20,0);
// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

//Activar EPO
glEnable(GL_DEPTH_TEST);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 2");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

//ANIMACION

glutIdleFunc(on_idle);


// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);



//ply1 = new _objeto_ply(argv[1]);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
