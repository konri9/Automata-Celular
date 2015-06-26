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

#include "../VisualizadorGnr.h"
#include "../GrafoGnr.h"
#include "SimuladorAves.h"
#include "NdoAve.h"

class VisualizadorAves : public VisualizadorGnr<NdoAve>{
    // Permite la visualizaci�n gr�fica de una instancia de Grafo.

public:
    VisualizadorAves(const GrafoGnr<NdoAve>& g);
    ~VisualizadorAves();

    void asignaColor();
private:
};

#endif	/* VISUALIZADORAVES_H */

