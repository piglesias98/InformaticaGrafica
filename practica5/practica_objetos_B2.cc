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
_tipo_objeto t_objeto=CUBO;
_modo   modo=LINEA_SOLIDO;

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
_lampara lampara;





//Variables para la animación
int valor_lento = 0;
int valor_rapido = 0;
int flag_giro_brazo_sup=1;
int flag_giro_brazo_inf=0;
int flag_giro_pantalla=0;

// _objeto_ply *ply1;


//Práctica 5
int estadoRaton[3], xc, yc, cambio=0;
int r;
int Ancho=450, Alto=450;
float factor=1.0;

void pick_color(int x, int y);

int modo_camara = 2;




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

void on_idle(){
	actualizaPos();
	glutPostRedisplay();
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

glViewport(0,0,Ancho, Alto);
}


//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{
//glViewport(0,0,Ancho,Alto);
// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

void change_projection_seleccion()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
glViewport(Ancho/2,0,Ancho/2, Alto/2);
}


void change_projection_planta()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-2,2,-2,2,-100,100);
//glRotatef(90,1,0,0);
glScalef(factor, factor, 1.0);	 		
glViewport(0,0, Ancho/2, Alto/2);
}

void change_projection_alzado()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-2,2,-2,2,-100,100);
glScalef(factor, factor, 1.0);			
glViewport(0,Alto/2, Ancho/2, Alto/2);
}


void change_projection_perfil()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(-2, 2, -2, 2, -100, 100);
glScalef(factor, factor, 1.0);
glViewport(Ancho/2, Alto/2, Ancho/2, Alto/2);
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



//*********1.0,0.0,0.0*****************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
switch (t_objeto){

	case CUBO: cubo.draw(modo,cubo.colores, 0.0, 0.0, 0.0, 0.2,  cubo.colores_back, 1, 1, 1);break;
	case PIRAMIDE: piramide.draw(modo,piramide.colores, 0.0, 0.0, 0.0, 0.2, piramide.colores_back, 1, 1, 1);break;
        case OBJETO_PLY: ply.draw(modo,ply.colores, 0.0, 0.0, 0.0, 0.2, ply.colores_back, 1, 1, 1);break;
        case ROTACION:  
        rotacion.draw(modo,rotacion.colores, 0.0, 0.0, 0.0, 0.2, rotacion.colores_back, 1, 1, 1);break;
        case ARTICULADO:
        lampara.draw(modo,lampara.colores, 0.0, 0.0, 0.0, 0.2, lampara.colores_back, 1, 1, 1);
        break;
	}
}


//**************************************************************************
// Funcion que dibuja los objetos en el buffer trasero
//***************************************************************************

void draw_objects_seleccion()
{
switch (t_objeto){
	case CUBO: 
				cubo.draw(SELECCION,cubo.colores, 0.0, 0.0, 0.0, 0.2,  cubo.colores_back, 1, 1, 1);break;
	case PIRAMIDE:
				piramide.draw(SELECCION,piramide.colores, 0.0, 0.0, 0.0, 0.2, piramide.colores_back, 1, 1, 1);break;
        case OBJETO_PLY:
        		ply.draw(SELECCION,ply.colores, 0.0, 0.0, 0.0, 0.2, ply.colores_back, 1, 1, 1);break;
        case ROTACION:        
	        rotacion.draw(SELECCION,rotacion.colores, 0.0, 0.0, 0.0, 0.2, rotacion.colores_back, 1, 1, 1);break;
        case ARTICULADO:
	        lampara.draw(SELECCION,lampara.colores, 0.0, 0.0, 0.0, 0.2, lampara.colores_back, 1, 1, 1);break;
	        break;
        
	}

}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{

if (modo_camara==1){		//Perspectiva

	//BUFFER FRONTAL
	glDrawBuffer(GL_FRONT);	
	clean_window();
	change_projection();
	change_observer();
	draw_axis();
	draw_objects();
	
	//BUFFER TRASERO
	glDrawBuffer(GL_BACK);
	clean_window();
	change_projection();
	change_observer();
	draw_objects_seleccion();
	
	glFlush();
	

}else if (modo_camara==2){		//ortogonal

	//BUFFER FRONTAL--------------------------------------------
	glDrawBuffer(GL_FRONT);
	clean_window();
	change_projection_seleccion();
	change_observer();
	
	draw_axis();
	draw_objects();


	//Planta
	change_projection_planta();
	
	gluLookAt(0,1,0, 0,0,0, 0,0,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	draw_axis();
	draw_objects();
	
	
	
	//Alzado
	change_projection_alzado();
	
	gluLookAt(0,0,1, 0,0,0, 0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	draw_axis();
	draw_objects();
	
	
	//Perfil
	change_projection_perfil();

	gluLookAt(1,0,0, 0,0,0, 0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw_axis();
	draw_objects();
	

	//BUFFER TRASERO-----------------------------------------------
	glDrawBuffer(GL_BACK);
	change_projection_seleccion();
	change_observer();
	
	draw_objects_seleccion();
	
	
	//Planta
	change_projection_planta();
	
	gluLookAt(0,1,0, 0,0,0, 0,0,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	draw_objects_seleccion();
	
	
	//Alzado
	change_projection_alzado();
	
	gluLookAt(0,0,1, 0,0,0, 0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	draw_objects_seleccion();
	
	//Perfil
	change_projection_perfil();

	gluLookAt(1,0,0, 0,0,0, 0,1,0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw_objects_seleccion();
	
	glFlush();

	}

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
	case '5':modo=SELECCION;break;
	case 'J':modo_camara=1;break;
	case 'K':modo_camara=2;break;
        case 'P':t_objeto=PIRAMIDE;break;
        case 'C':t_objeto=CUBO;break;
        case 'O':t_objeto=OBJETO_PLY;break;	
        case 'R':t_objeto=ROTACION;break;
        case 'A':t_objeto=ARTICULADO;break;
        case 'X':valor_lento = 1; valor_rapido=3;break;
        case 'Z':valor_lento = 0; valor_rapido=0;break;
        
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
// Funcion llamada cuando se aprieta una tecla especial
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
// Funciones para la seleccion
//************************************************************************


void procesar_color(unsigned char color[3])
{
switch (t_objeto){
	case CUBO:
			cubo.draw(DETERMINAR,cubo.colores, 0.0, 0.0, 0.0, 0.2,  cubo.colores_back, color[0], color[1], color[2]);
			break;
	case PIRAMIDE:
			piramide.draw(DETERMINAR,piramide.colores, 0.0, 0.0, 0.0, 0.2,  piramide.colores_back, color[0], color[1], color[2]);
			break;
  case OBJETO_PLY:
  			ply.draw(DETERMINAR,ply.colores, 0.0, 0.0, 0.0, 0.2,  ply.colores_back, color[0], color[1], color[2]);
  			break;
  case ROTACION:       
  			rotacion.draw(DETERMINAR,rotacion.colores, 0.0, 0.0, 0.0, 0.2,  rotacion.colores_back, color[0], color[1], color[2]);
  			break;
  case ARTICULADO:
		  lampara.draw(DETERMINAR,lampara.colores, 0.0, 0.0, 0.0, 0.2,  lampara.colores_back, color[0], color[1], color[2]);
		  break;

              
}

}
 
 
void pick_color(int x, int y)
{
GLint viewport[4];
unsigned char pixel[3];
glGetIntegerv(GL_VIEWPORT, viewport);	//me olvido y directamente pongo el tamaño grande x,alto
glReadBuffer(GL_BACK);
glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);	//nos lo da el punto en coord de dispositivo
//podriamos leer varios pixeles, 1,1, --> 100,100
printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

procesar_color(pixel);
glutPostRedisplay();
}

//***************************************************************************
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton( int boton, int estado, int x, int y )
{
if(boton== GLUT_RIGHT_BUTTON) {
   if( estado == GLUT_DOWN) {
      estadoRaton[2] = 1;
      xc=x;
      yc=y;
     } 
   else estadoRaton[2] = 1;
   }
if(boton== GLUT_LEFT_BUTTON) {	//controla el pick (botón izq)
  if( estado == GLUT_DOWN) {
      estadoRaton[2] = 2;
      xc=x;
      yc=y;
      pick_color(xc, yc);
    } 
  }
  if (boton == 3){	//scroll up envent
		factor +=0.1;
		//r=rueda;
	}else if (boton == 4){	//scroll down event
		factor -=0.1;
		//r=rueda;
	}
}

void ruedaRaton(int rueda, int direccion, int x, int y){
	if (rueda>r){
		factor +=0.1;
		r=rueda;
	}else{
		factor -=0.1;
		r=rueda;
	}
	
}
/*************************************************************************/

void getCamara (GLfloat *x, GLfloat *y)
{
*x=Observer_angle_x;
*y=Observer_angle_y;
}

/*************************************************************************/

void setCamara (GLfloat x, GLfloat y)
{
Observer_angle_x=x;
Observer_angle_y=y;
}


/*************************************************************************/

void RatonMovido( int x, int y )
{

if(estadoRaton[2]==1){

Observer_angle_y += x - xc;
Observer_angle_x += y - yc;

xc = x;
yc = y;

glutPostRedisplay();
}


/*
float x0, y0, xn, yn; 
if(estadoRaton[2]==1) 
    {getCamara(&x0,&y0);	//valores de giro que tiene la camara
     yn=y0+(y-yc);
     xn=x0-(x-xc);
     setCamara(xn,yn);	//cambiamos la cámara
     xc=x;	//actualizamos los valores de x e y
     yc=y;
     glutPostRedisplay();
    }
    
*/
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
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);



}



	

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{

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



// eventos ratón
glutMouseFunc( clickRaton );
glutMotionFunc( RatonMovido );


// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);



//ply1 = new _objeto_ply(argv[1]);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
