#ifndef NDOVRT_H
#define NDOVRT_H

#include <memory>
#include <vector>
#include <string>

#include "GrafoGnr.h"

using namespace std;

class NdoVrt
{

public:

    enum E  // representa el tipo de estados de la red de infección
    {
        S, // representa un vértice susceptible de infección
        I, // representa un vértice infectado
        R, // representa un vértice resistente
    };

    NdoVrt();
    virtual ~NdoVrt();

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el estado del vértice con índice vrt.
    E obtEst(int vrt) const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el valor del temporizador de chequeo de antivirus del vértice con índice vrt.
    int obtTmpChqVrs(int vrt) const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el valor del contador de chequeo de antivirus del vértice con índice vrt.
    int obtCntChVrs(int vrt) const;


    /* MÉTODOS MODIFICADORES */

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: cambia el estado del vértice cuyo índice es vrt a ne.
    void modEst(int vrt, E ne);

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: cambia el valor del temporizador de chequeo de virus del vértice vrt por el valor nt.
    void modTmpChqVrs(int vrt, int nt);

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: actualiza el valor del contador de chequeo de virus para la siguiente iteración.
    void actCntChqVrs(int vrt);

    // REQ: ios << this->obtTotVrt().
    // MOD: *this.
    // EFE: cambia el estado a I (infectado) a ios vértices escogidos al azar.
    //      ios o initial-outbreak-size: cantidad inicial de nodos infectados.
    void infectar(int ios);

    // MOD: *this
    // EFE: asigna el valor del temporizador para cada vértice con un número al azar entre 1 y maxTmp.
    //      vcf o virus-check-frecuency: frecuencia máxima de chequeo antivirus.
    void azarizarTmpChqVrs(int vcf);

    //MOD:*this
    //EFE: calcula el estado de un vertice a partir de sus vecinos
    void calcEst(int vrt);


protected:

private:

struct Ndo {
        E e; // representa el estado del vértice
        int tmpChqVrs; // representa el temporizador de chequeo de virus
        int cntChqVrs; // representa el contador de chequeo de virus: va de 0 a tmpChqVrs
        vector <int> lstAdy;  // Escoja entre <vector>, <list> y <forward_list> para representar la lista de adyacencias del vértice.
        Ndo(): e(S), tmpChqVrs(1){};
        // No va a ser necesario un destructor porque ahora todo se manejará automáticamente
    };

    vector<Ndo>arrVrt;

};

#endif // NDOVRT_H
