/*
 * File:   VisualizadorAves.cpp
 * Author: Alan
 *
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


#ifndef NULL
#define NULL 0
#endif
using namespace std;

VisualizadorAves::VisualizadorAves(const GrafoGnr<NdoAve>& g) : VisualizadorGnr<NdoAve>(g) {
}

VisualizadorAves::~VisualizadorAves() {
    ptr = NULL;
}
void VisualizadorAves::asignaColor()
{


}
