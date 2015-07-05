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

	void asignarValores (int navs, double nanr);

    //REQ: que el grafo este bien construido
    //EFE: inicializa todos los valores para llevar a cabo la simulacion
    void setup(int avesEstr);
    
    void asignarNR(double nNR);

    //REQ: que el grafo este preparado para la simulacion
    //EFE:simula el proceso de anidacion de aves
    void go(int cntItr);

	//EFE: Realiza una matriz con
	void creaMatrix ();

protected:
private:
	int avs;
	double NR = 0;
	double anr;
	vector<NdoAve::E>estados;
	vector<double>estreses;
};

#endif	/* SIMULADOR_H */

