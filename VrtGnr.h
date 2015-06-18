#ifndef VrtGnr_H
#define VrtGnr_H


#include "VrtGnr.h"
#include "GrafoGnr.h"

#include <iostream>
#include <chrono>
#include <memory>
#include <string>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include <limits> // std::numeric_limits


bool prob(double probability);

using namespace std;

template < typename VG >
class VrtGnr
{

public:

    enum E  // representa el tipo de estados de la red de infección
    {
        S, // representa un vértice susceptible de infección
        I, // representa un vértice infectado
        R, // representa un vértice resistente
    };


    VrtGnr();
    // NdoVrt(string str);
    virtual ~VrtGnr();

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el estado del vértice con índice vrt.
    E obtEst() const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el valor del temporizador de chequeo de antivirus del vértice con índice vrt.
    int obtTmpChqVrs() const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el valor del contador de chequeo de antivirus del vértice con índice vrt.
    int obtCntChVrs() const;


    /* MÉTODOS MODIFICADORES */

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: cambia el estado del vértice cuyo índice es vrt a ne.
    void modEst(E ne);

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: cambia el valor del temporizador de chequeo de virus del vértice vrt por el valor nt.
    void modTmpChqVrs(int nt);

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: actualiza el valor del contador de chequeo de virus para la siguiente iteración.
    void actCntChqVrs();

    // MOD: *this
    // EFE: asigna el valor del temporizador para cada vértice con un número al azar entre 1 y maxTmp.
    //      vcf o virus-check-frecuency: frecuencia máxima de chequeo antivirus.
    void azarizarTmpChqVrs();

    //MOD:*this
    //EFE: calcula el estado de un vertice a partir de sus vecinos
    void calcEst(vector<int>adyac);


protected:

private:
    E e; // representa el estado del vértice
    int tmpChqVrs; // representa el temporizador de chequeo de virus
    int cntChqVrs; // representa el contador de chequeo de virus: va de 0 a tmpChqVrs
    // No va a ser necesario un destructor porque ahora todo se manejará automáticamente
};
template < typename VG >
bool prob(double probability) // probability < 1
{
    double result = (double)rand() / (double)RAND_MAX;
    if(result < probability)
        return true;
    return false;
}
template < typename VG >
VrtGnr::VrtGnr()
{
    e = S;
    azarizarTmpChqVrs();
}
template < typename VG >
VrtGnr::~VrtGnr()
{
    //dtor
}

template < typename VG >
VrtGnr::E VrtGnr::obtEst() const
{
    return e;
}

int VrtGnr::obtTmpChqVrs() const
{
    return tmpChqVrs;
}

int VrtGnr::obtCntChVrs()const
{
    return cntChqVrs;
}

void VrtGnr::modEst(E ne)
{
    e = ne;
}

void VrtGnr::modTmpChqVrs(int nt)
{
    tmpChqVrs = nt;
}


void VrtGnr::actCntChqVrs()
{
    if(cntChqVrs == tmpChqVrs)
        cntChqVrs = 0;
    else
    {
        cntChqVrs++;
    }
}

void VrtGnr::azarizarTmpChqVrs()
{
    int randy = rand() % 5 + 1;
    tmpChqVrs = randy;
}


void VrtGnr::calcEst(vector<int> adyac)
{
    for(int i=0; i<adyac.size(); i++)
    {
        if (obtEst() != VrtGnr::S) return;
        int cont = 0;
        if(obtEst() == VrtGnr::I) cont++;
        if (cont == adyac.size()) modEst(VrtGnr::I);
    }
}


void VrtGnr::calcEst(vector<int> adyac)
{
    for(int i=0; i<adyac.size(); i++)
    {
        if (obtEst() != VrtGnr::S) return;
        int cont = 0;
        if(obtEst() == VrtGnr::I) cont++;
        if (cont == adyac.size()) modEst(VrtGnr::I);
    }
}








#endif // VrtGnr_H
