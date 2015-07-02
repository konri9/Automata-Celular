/*
 * File:   VisualizadorVrs.cpp
 * Author: Alan
 *
 * Created on 2 de abril de 2015, 07:42 PM
 */

#include "VisualizadorVrs.h"
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

VisualizadorVrs::VisualizadorVrs(const GrafoGnr<NdoVrs>& g) : VisualizadorGnr<NdoVrs>(g) {
    ptr = this;
}

VisualizadorVrs::~VisualizadorVrs() {
    ptr = NULL;
}

void VisualizadorVrs::asignaColor()
{

}
