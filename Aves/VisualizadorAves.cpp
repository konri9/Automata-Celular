/*
 * File:   VisualizadorAves.cpp
 *
 * Author: Alan
 * Created on 2 de abril de 2015, 07:42 PM
 */

#include "VisualizadorAves.h"

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

void VisualizadorAves::DrawEllipse(double rX, double rY, double x, double y) //Dibuja los huevos
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
