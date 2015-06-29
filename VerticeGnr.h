#ifndef VERTICEGNR_H
#define VERTICEGNR_H

#include <memory>
#include <vector>
#include <string>

#include "GrafoGnr.h"

bool prob(double probability);

using namespace std;

// Para definir el color del vertice
struct Vector3
{
    double x, y, z;
    Vector3()
    {
        x = 0; y = 0; z = 0;
    };

    Vector3(double nx, double ny, double nz)
    {
        x = nx; y = ny; z = nz;
    };
};

class VerticeGnr
{

public:

    //MOD:*this
    //EFE: calcula el estado de un vertice a partir de sus vecinos
    //Metodo virtual puro
    virtual void calcEst(vector<VerticeGnr*>& ady) = 0;

    //EFE: Devuelve el color del vertice dependiendo de su estado
    virtual Vector3 obtColor() = 0;

     // EFE: retorna true si *this == o, false en caso contrario.
     //comparador
    // metodo virtual puro
//*    virtual void operator=(const VerticeGnr& vr) = 0;

    //asignador
    //metodo virtual puro
    //virtual void asignador() = 0;

    //cambio de estado
    //virtual void modEst() = 0 ;
};

//Puntero de vertice generico
//vector<VerticeGrn*>ne
//ne[i]->metodo();







#endif // NDOVRT_H
