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

	void asignarValores (int nios, double nvsc, double nrc, double ngrc);

    //REQ: que el grafo este bien construido
    //EFE: inicializa todos los valores para llevar a cabo la simulacion
    void setup(int avesEstr);

    //REQ: que el grafo este preparado para la simulacion
    //EFE:simula el proceso de anidacion de aves
    void go(int cntItr, double NR);

	//EFE: Realiza una matriz con
	void creaMatrix ();

protected:
private:
	int ios;
	double vsc, rc, grc;
	vector<NdoAve::E>estados;
};

#endif	/* SIMULADOR_H */

