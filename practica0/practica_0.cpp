#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

/*
Dar los vertices en sentido contrario a las agujas del reloj (en 2D no importa pero en ·D sí)
en 2D como sabemos si un objeto tapa a otro? en el orden en el que se van llamando
si queremos pintar un sistema más complejo como por ejemplo los ojos --> usar funcion circulo
incorporarlo al código
desde el punto de vista de la inf grafica está mal pq no nos serviria para otro sistema gráfico,
salvo que almacenemos los vértices en otra matriz --> estructura de datos para almacenar los vértices

código de la pract 1 --> hay dos códigos, genérico o del grupo C --> podemos usar el que queramos

--> código de la práctica 1
usar std para manejar los datos
añadir vector vertex y stdlib
CLASE PUNTO --> la clase minima


*/


void Ejes (int width)
{   
    glLineWidth(width);
    glBegin(GL_LINES);
       glColor3f(1.0,0.0,0.0);	//pq el mundo está entre -1,1, el color se puede poner en sitios distintos
       glVertex3f(-1.0,0.0,0.0);	//la anchura solo se puede poner dentro y afecta a todas las lineas que yo ponga
       glVertex3f(1.0,0.0,0.0);
 
       glColor3f(0.0,1.0,0.0);	//el orden en el que se pintan los vértices da igual	//lo estoy pintando en verde
       glVertex3f(0.0,-1.0,0.0);
       glColor3f(1.0,1.0,0.0);	//pero  aquí lo pongo amarillo por lo que sobreescribe al verde
       glVertex3f(0.0,1.0,0.0);   
    glEnd();
   
       
}


void Monigote ()
{
  
 
// cara
   glLineWidth(1);
   glColor3f(1.0,0.8,0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);	//nos toca hacer la cara
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 


	//es lo mismo pero estamos pintando LINE --> el borde de la cara
   glColor3f(0.0,0.0,0.);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 
   
   //poligonos --> concavos y convexos. en open gl no podemos usar poligonos concavos --> por eso no podríamos pintar un sombrero
   
}


static void Init( )
{

   glShadeModel( GL_FLAT);	//puedo poner GL_SMOOTH
}


static void Reshape( int width, int height )
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho (-1.0, 1.0,-1.0, 1.0, -10, 10.0);
    //espacio en el que se va a trabajar
    //ortho --> espacio en coordenadas mundiales en el que se va a trabajar -1,-1 hasta 1, 1
    
}

static void Display( )
{

  glClearColor(0.5,0.5,0.5,0.0);	//borrar la pantalla poniendo un color gris
  glClear( GL_COLOR_BUFFER_BIT );
   
  //aquí pinto lo que yo quiero
   
   Ejes(6);	//estructura de crear informacion en opengl
   Monigote();
   
   //para que se cree la imagen del modelo en la salida gráfica
   glFlush();
}


static void Keyboard(unsigned char key, int x, int y )
{
 
  if (key==27)	//escape
      exit(0);
  if (key=='a')
    {glShadeModel(GL_SMOOTH);
  		Display();}
  if (key=='b')
  		{glShadeModel(GL_FLAT);
  		Display();}

}


int main( int argc, char **argv )
{
   glutInit(&argc,argv);
   glutInitDisplayMode( GLUT_RGB );

   glutInitWindowPosition( 20, 100 );
   glutInitWindowSize(500, 500 );
   glutCreateWindow("Practica 0 IG");


   Init(); // decir si queremos trabajar con el modo fly (todo mismo color)
	
	
   glutReshapeFunc(Reshape);
   glutDisplayFunc(Display); //volver a pintar la ventana
   glutKeyboardFunc(Keyboard);
  
   glutMainLoop( );

   return 0;
}

