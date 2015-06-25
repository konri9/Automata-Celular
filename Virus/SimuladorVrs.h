#ifndef SIMULADORVRS_H
#define SIMULADORVRS_H

#include "SimuladorGnr.h"
#include <memory>
using namespace std;

#include "GrafoGnr.h"

template <typename Vrs>
class SimuladorVrs : public SimuladorGnr<Vrs>
{
public:
    SimuladorVrs(GrafoGnr<Vrs>* g);
    //~SimuladorVrs();

    //REQ: que el grafo este bien construido
    //EFE: inicializa todos los valores para llevar a cabo la simulacion
    void setup();

    //REQ: que el grafo este preparado para la simulacion
    //EFE:simula el proceso de infeccion de virus en una red de computadores
    void go();

protected:
private:
};

//hacer un metodo virtual puro que asigne el color

#endif // SIMULADORVRS_H

