//**************************************************************************
// Práctica 1
//
//
// GPL
//**************************************************************************

/*

CUANDO SE ENTREGA
PASADA LAS VACACIONES
de forma presencial enseñar la última práctica en periodo de exámenes
calificaciones de las otras cuatro --> el dia que vayamos a entregar la quinta práctica

como el examen es el último
primera semana de la vuelta
le da igual sobre la práctica

a partir de la vuelta de navidad, nos citará le enseñamos esta 
TIENE QUE SER CON LA PRÁCTICA 3 DE BASE 





No creo que llegue viva al día 22
cuando hay que entregar todo esto
encima ya no hay clases ni tutorías
qué mal todooooooooooooooooooooo

Partir de la práctica 3 nuestro objeto articulado
Hacer el zoom de la cámara en perspectiva (del primer punto)
- cámara ortogonal y su zoom
dos modos de selección
- el objeto completo
- dado un objeto que se pueda seleccionar una de sus caras

tomamos el objeto articulado
hacemos una seleccion de los triangulos que lo forman
subir nota --> que se pueda hacer lo mismo con todos los objetos

añadir el punto uno a nuestro código

camara ortogonal --> cambiando el change_projection
gl frustrum es normal
si queremos pararelo tenemos que poner orto

problema -->esta funcion se la llama una sola vez, en initialize
donde pone cambiar observador llamar a change_projection

subir nota --> cambiar de una camara a otra cuatro vistas
vista en alzado, perfil, planta y perspectiva

el fichero punto h de la practica 3
añadir metodo
- draw_solido_seleccion_completa(float r, float g, float b);
- draw_solido_seleccion_cara(float r, float g, float b); una cara de un color y otras de otro
metodo para dibujar solido cara(mismos parametros que los anteriores, int n) (no es selección, como los anteriores)
también podríamos hacer uno draw solido arista
n seria el triangulo que se pintaría de un color distinto
hacer la seleccion solamente cuando sea solo --> para subir nota
pintar modo linea y modo solido al mismo tiempo para que se distingan las caras
glColor3ub(r,g,b)
aydiosito
poner el glcolor dentro de cada for para que se pinten todos




*/
#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "user_code.h"

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=450,UI_window_height=450;

int estadoRaton[3], xc, yc, modo[5], cambio=0;

solido *piramide1, *piramide2, *piramide3, *piramide4, *piramide5;

int Ancho=450, Alto=450;
float factor=1.0;

void pick_color(int x, int y);

int tipo_camara = 0;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)

if (tipo_camara == 0 )
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
if (tipo_camara == 1){	//Cambiamos el tipo de cámara con una tecla --> c perspectiva, v paralela
glOrtho(-2,2,2,2,-100,100);
glScalef(factor, factor,1);
}
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
//change_projection();
glViewport(0,0,Ancho,Alto);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

void change_projection_alzado()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glViewport(0,Alto/2, Ancho/2, Alto/2);
glOrtho(-2,2,-2,2,-100,100);
glScalef(factor, factor, 1.0);
}

void change_projection_planta()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glViewport(0,Alto/2, Ancho/2, Alto/2);
glOrtho(-2,2,-2,-100,100);
glRotatef(90,1,0,0);
}

/*

como se hace un zoom en paralelo?
glOrtho

*/

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glLineWidth(1);
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


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
  glPushMatrix();
     glTranslatef(0.0,-0.4,0.0);
     glPushMatrix(); 
     glTranslatef(0.0,0.8,0.0);
     draw_solido(piramide1,0.1,0.1,0.1,1);
     draw_solido(piramide1,piramide1->r,piramide1->g,piramide1->b,2);
     glPopMatrix();         

     glPushMatrix(); 
     glTranslatef(-0.5,0.0,0.5);
     draw_solido(piramide2,0.2,0.2,0.4,1);
     draw_solido(piramide2,piramide2->r,piramide2->g,piramide2->b,2);
     glPopMatrix(); 
     
     glPushMatrix(); 
     glTranslatef(0.5,0.0,0.5);
     draw_solido(piramide3,0.2,0.2,0.7,1);
     draw_solido(piramide3,piramide3->r,piramide3->g,piramide3->b,2);
     glPopMatrix();

     glPushMatrix(); 
     glTranslatef(-0.5,0.0,-0.5);
     draw_solido(piramide4,0.2,0.2,1.0,1);
     draw_solido(piramide4,piramide4->r,piramide4->g,piramide4->b,2);
     glPopMatrix(); 

     glPushMatrix(); 
     glTranslatef(0.5,0.0,-0.5);
     draw_solido(piramide5,1.0,0.2,0.0,1);
     draw_solido(piramide5,piramide5->r,piramide5->g,piramide5->b,2);
     glPopMatrix(); 
   glPopMatrix();   
}

//**************************************************************************
// Funcin que dibuja los objetos en el buffer trasero
//***************************************************************************


void draw_objects_seleccion()
{

int inc=20;
   glPushMatrix();    
     glTranslatef(0.0,-0.4,0.0);
     glPushMatrix(); 
     glTranslatef(0.0,0.8,0.0);
     draw_seleccion_color(piramide1,100,100,100);
     glPopMatrix();         

     glPushMatrix(); 
     glTranslatef(-0.5,0.0,0.5);
     draw_seleccion_color(piramide2,100+inc,100+inc,100+inc);
     glPopMatrix(); 
     inc+=20;
     
     glPushMatrix(); 
     glTranslatef(0.5,0.0,0.5);
     draw_seleccion_color(piramide3,100+inc,100+inc,100+inc);
     glPopMatrix();
     inc+=20;  

     glPushMatrix(); 
     glTranslatef(-0.5,0.0,-0.5);
     draw_seleccion_color(piramide4,100+inc,100+inc,100+inc);
     glPopMatrix(); 
     inc+=20;

     glPushMatrix(); 
     glTranslatef(0.5,0.0,-0.5);
     draw_seleccion_color(piramide5,100+inc,100+inc,100+inc);
     glPopMatrix(); 
   glPopMatrix();   

}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{
glDrawBuffer(GL_FRONT);	//se borra la ventana se coloca la camara...
clear_window();
change_observer();
draw_axis();
draw_objects();	//objetos articulado


glDrawBuffer(GL_BACK);
clear_window();
change_observer();
draw_objects_seleccion();	//pintamos los  objetos otra vez cada pieza con un color distinto

glFlush();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

/*
void change_window_size(int Ancho1,int Alto1)
{
change_projection();
Ancho=Ancho1;
Alto=Alto1;
draw_scene();
}  
*/

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
UI_window_height=UI_window_width*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

if (toupper(Tecla1)=='Q') exit(0);
if (Tecla1=='+') 
   {factor*=0.9;
    glutPostRedisplay();}
if (Tecla1=='-') 
   {factor*=1.1;
    glutPostRedisplay();}
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
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
}

//poner un if --> si el botón es una rueda hacer zoom
//como? utilizando los mismos valores del zoom en la tecla
//factor*=0.9


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



//

/*************************************************************************/

void RatonMovido( int x, int y )
{
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
}


//***************************************************************************
// Funciones para la seleccion
//************************************************************************


void procesar_color(unsigned char color[3])
{
 int i;
 solido *obj;

 obj=(solido *)malloc(sizeof(solido));
 
 switch (color[0])
      {case 100: obj=piramide1;
                 if (modo[0]==0) 
                      {modo[0]=1;
                       cambio=1;
                      }
                  else 
                      {modo[0]=0;
                       cambio=0;
                      }
                  break; 
        case 120: obj=piramide2;
                  if (modo[1]==0) 
                       {modo[1]=1;
                        cambio=1;
                       }
                  else 
                       {modo[1]=0;
                        cambio=0;
                       } 
                  break;
        case 140: obj=piramide3;
                  if (modo[2]==0) 
                       {modo[2]=1;
                        cambio=1;
                       }
                  else 
                       {modo[2]=0;
                        cambio=0;
                       }
                  break; 
        case 160: obj=piramide4;
                  if (modo[3]==0) 
                       {modo[3]=1;
                        cambio=1;
                       }
                  else 
                       {modo[3]=0;
                        cambio=0;
                       }
                  break;
        case 180: obj=piramide5;
                  if (modo[4]==0) 
                       {modo[4]=1;
                        cambio=1;
                       }
                  else 
                       {modo[4]=0;
                        cambio=0;
                       }
                  break;
                }         
               
        if (cambio==1) 
                  {obj->r=0.3;
                   obj->g=0.9;
                   obj->b=0.3;
                  }
        if (cambio==0)
                  {obj->r=0.9;
                   obj->g=0.6;
                   obj->b=0.2;
                  }
                 
 }



void pick_color(int x, int y)
{
GLint viewport[4];
unsigned char pixel[3];
//si quisieramos leer 100 pixel[100][3]
glGetIntegerv(GL_VIEWPORT, viewport);	//me olvido y directamente pongo el tamaño grande x,alto
glReadBuffer(GL_BACK);
glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);	//nos lo da el punto en coord de dispositivo
//podriamos leer varios pixeles, 1,1, --> 100,100
printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

procesar_color(pixel);
glutPostRedisplay();
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=.5;
Window_height=.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=3*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);

for (int i=0;i<5;i++) modo[i]=0;
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
    // se llama a la inicialización de glut
    
    piramide1=(solido*)malloc(sizeof(solido));
    construir_piramide(0.5,0.8,piramide1);
    
    piramide2=(solido*)malloc(sizeof(solido));
    construir_piramide(0.5,0.8,piramide2);
    
    piramide3=(solido*)malloc(sizeof(solido));
    construir_piramide(0.5,0.8,piramide3);
    
    piramide4=(solido*)malloc(sizeof(solido));
    construir_piramide(0.5,0.8,piramide4);
    
    piramide5=(solido*)malloc(sizeof(solido));
    construir_piramide(0.5,0.8,piramide5);
    
    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de proDRAWfundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Ejemplo");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // eventos ratón
    glutMouseFunc( clickRaton );
    glutMotionFunc( RatonMovido );


    // funcion de inicialización
    initialize();

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}
