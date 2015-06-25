#ifndef VERTICEGNR_H
#define VERTICEGNR_H

#include <memory>
#include <vector>
#include <string>

#include "GrafoGnr.h"

bool prob(double probability);

using namespace std;

class NdoVrt
{

public:

    //MOD:*this
    //EFE: calcula el estado de un vertice a partir de sus vecinos
    //Metodo virtual puro
    void calcEst(vector<int>adyac) = 0;

     // EFE: retorna true si *this == o, false en caso contrario.
     //comparador
    // metodo virtual puro
    bool operator==(const VerticeGnr& o) const = 0;

    //asignador
    //metodo virtual puro

    void asignador() = 0;

    //cambio de estado
    void modEst() = 0 ;
};

//Puntero de vertice generico
//vector<VerticeGrn*>ne
//ne[i]->metodo();

VerticeGnr::void calcEst(vector<int>adyac)
{
    for(int i=0; i<adyac.size(); i++)
    {
        if (obtEst() != NdoVrt::S) return;
        int cont = 0;
        if(obtEst() == NdoVrt::I) cont++;
        if (cont == adyac.size()) modEst(NdoVrt::I);
    }
}


}



#endif // NDOVRT_H
