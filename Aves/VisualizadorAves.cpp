/*
 * File:   VisualizadorAves.cpp
 *
 * Author: Alan
 * Created on 2 de abril de 2015, 07:42 PM
 */

#include "VisualizadorAves.h"
//#include <windows.h>
//#include <process.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <string>
#include <algorithm> //max element
#include <vector>

#ifndef DEG2RAD
#define DEG2RAD 3.14159/180.0
#endif // DEG2RAD

#ifndef NULL
#define NULL 0
#endif
using namespace std;

VisualizadorAves::VisualizadorAves(const GrafoGnr<NdoAve>& g) : VisualizadorGnr<NdoAve>(g) {
    this->ptr = this;
}

VisualizadorAves::~VisualizadorAves() {
    this->ptr = NULL;
}

void VisualizadorAves::asignaColor()
{

}


void VisualizadorAves::DrawEllipse(double rX, double rY, double x, double y)
//Dibuja los huevos
{
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i++)
    {
        double rad = i*DEG2RAD;
        glVertex2f(x+ (cos(rad)*rX), y+ (sin(rad)*rY));
    }
    glEnd();

}

void VisualizadorAves::recurCircles()
{
    int filas = obtGrafo()->obtFilas(), columnas = obtGrafo()->obtColumnas();
    double cantidad = filas*columnas;
    double tamaninfilas = (double)1/filas, tamanincolumnas = (double)1/columnas;
    for (double i = 0; i < filas; i++)
    {
        for (double j = 0; j < columnas; j++)
        {
            int vrt = i*filas + j;
            VerticeGnr *ver = &grafo[vrt];
            Vector3 vec = ver->obtColor();
            glColor3f(vec.x, vec.y, vec.z);
            DrawEllipse(tamaninfilas, tamanincolumnas, tamaninfilas - 1 + (2*i*tamaninfilas), -1*tamanincolumnas + 1 - (2*j*tamanincolumnas));
        }
    }
}

/*
void printMatrix()
{
    int fil = 17;
    int col = 17;
    int av = 78;
    Grafo grf(fil,col,av);
    int **mat = grf.obtMatrizAves();
    //int fil = grf.obtFilas();
   // int col = grf.obtCol();
    //int aves = grf.obtCntAves();
    // imprime el carton de huevos
    double lim = 0.9;//, limneg = ;

    // hay que adaptarlo a la cantidad de huevos...

    for(double i=-lim; i<lim; i+=0.1)
    {
        for(double j=-lim; j<lim; j+=0.1)
        {

            DrawEllipse(0.04,0.06,i,j);
        }
    }


    cout << mat[0][1]<< endl;
    for(int i =0; i<3 ;i++) cout << "matriz recibida" << mat[0][0]<< endl;


}



*/
/*
void VisualizadorAves:: display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glColor3f(1.0,0.0,0.0);
    //DrawEllipse(0.04,0.06,0.5,0.5);
    //DrawEllipse(0.04,0.06,-0.9,0.9);
    //DrawEllipse(0.04,0.06,-0.8,0.9);
    //DrawEllipse(0.04,0.06,0.9,0.9);
    double lim = 0.9;//, limneg = ;
    for(double i=-lim; i<lim; i+=0.1)
    {
        for(double j=-lim; j<lim; j+=0.1)
        {
            DrawEllipse(0.04,0.06,i,j);
        }
    }



    glEnd();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    Grafo grf(2,2,4);
    int **mat = grf.obtMatrizAves();
  //  cout << mat[0][1]<< endl;
    for(int i =0; i<3 ;i++) cout << "matriz recibida" << mat[0][0]<< endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Visualizador de Aves");
    glutDisplayFunc(display);
    //glutIdleFunc(display);
    glutMainLoop();
    //if
    return 0;
}*/

