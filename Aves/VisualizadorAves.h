/*
 * File:   VisualizadorAves.h
 * Author: Alan
 *
 * Created on 2 de abril de 2015, 07:42 PM
 */

#ifndef VISUALIZADORAVES_H
#define	VISUALIZADORAVES_H

#ifdef _WIN32 || WIN32
#include <windows.h>
#endif

#include <memory>
using namespace std;

#include "../GrafoGnr.h"
#include "SimuladorAves.h"
#include "../VisualizadorGnr.h"
#include "NdoAve.h"

class VisualizadorAves : public VisualizadorGnr<NdoAve>{
public:
    VisualizadorAves(const GrafoGnr<NdoAve>& g);
    ~VisualizadorAves();
    void asignaColor();
    void DrawEllipse(double rX, double rY, double x, double y);
    void printMatrix();
private:
};

#endif	/* VISUALIZADORAVES_H */

