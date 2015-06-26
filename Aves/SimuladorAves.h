#ifndef SIMULADORAVES_H
#define SIMULADORAVES_H

#include "NdoAve.h"
#include "../SimuladorGnr.h"
#include <memory>
using namespace std;

#include "GrafoGnr.h"

class SimuladorAves : public SimuladorGnr<NdoAve>
{
public:
    SimuladorAves(GrafoGnr<NdoAve>* g);
    //~SimuladorAves();

    //REQ: que el grafo este bien construido
    //EFE: inicializa todos los valores para llevar a cabo la simulacion
    void setup();

    //REQ: que el grafo este preparado para la simulacion
    //EFE:simula el proceso de anidacion de aves
    void go();

	//EFE: Realiza una matriz con
	void creaMatrix ();

protected:
private:
    GrafoGnr<NdoAve> *grafo;
    enum Nest { A, X, }; // A indica que hay adyacencia, X indica que no.

};

#endif	/* SIMULADOR_H */

