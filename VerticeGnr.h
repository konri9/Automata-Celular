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
    //EFE: Devuelve el color del vertice dependiendo de su estado
    virtual Vector3 obtColor() = 0;
};

//Puntero de vertice generico
//vector<VerticeGrn*>ne
//ne[i]->metodo();







#endif // NDOVRT_H
