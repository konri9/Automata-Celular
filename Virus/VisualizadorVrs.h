/*
 * File:   VisualizadorVrs.h
 * Author: Alan
 *
 * Created on 2 de abril de 2015, 07:42 PM
 */

#ifndef VISUALIZADORVRS_H
#define	VISUALIZADORVRS_H

#ifdef _WIN32 || WIN32
#include <windows.h>
#endif

#include <memory>
using namespace std;

#include "../GrafoGnr.h"
#include "../SimuladorGnr.h"
#include "../VisualizadorGnr.h"
#include"NdoVrs.h"

class VisualizadorVrs : public VisualizadorGnr<NdoVrs>{
public:
    VisualizadorVrs(const GrafoGnr<NdoVrs>& g);
    ~VisualizadorVrs();
    void asignaColor();
};

#endif	/* VISUALIZADOR_H */

