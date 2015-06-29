#ifndef SIMULADORVRS_H
#define SIMULADORVRS_H

#include "../SimuladorGnr.h"
#include "NdoVrs.h"
#include <memory>
using namespace std;

#include "GrafoGnr.h"

class SimuladorVrs : public SimuladorGnr<NdoVrs>
{
public:
    SimuladorVrs(GrafoGnr<NdoVrs>* g);
    //~SimuladorVrs();

    void asignarValores(int nios, double nvsc, double nrc, double ngrc);

    //REQ: que el grafo este bien construido
    //EFE: inicializa todos los valores para llevar a cabo la simulacion
    void setup(int vrtInf);

    //REQ: que el grafo este preparado para la simulacion
    //EFE:simula el proceso de infeccion de virus en una red de computadores
    void go(int cntItr);
protected:
private:
    int ios;
    double vsc, rc, grc;
    vector<NdoVrs::E> estados;
};

//hacer un metodo virtual puro que asigne el color

#endif // SIMULADORVRS_H

