#include "NdoAve.h"
#include "GrafoGnr.h"
#include <iostream>
#include <chrono>
#include <memory>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <random>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <limits> // std::numeric_limits

using namespace std;

NdoAve::NdoAve(){
    e = S;
    azarizarTmpChqVrs();
}

NdoAve::NdoAve(const NdoAve& ave){
	e = ave.e;
	tmpChqVrs = ave.tmpChqVrs;
	cntChqVrs = ave.cntChqVrs;

}


NdoAve::~NdoAve()
{
    //dtor
}


NdoAve::E NdoAve::obtEst() const
{
        return e;
}

Vector3 NdoAve::obtColor()
{
	if (obtEst() == NdoAve::R) {
        return Vector3(1.0, 1.0, 1.0); //Color blanco -> ave relajada
    }
    if (obtEst() == NdoAve::S) {
        return Vector3(1.0, 0.0, 0.0); //Color rojo-> ave estresada
    }
    if (obtEst() == NdoAve::P) {
        return Vector3(1.0, 0.5, 0.0); //Color naranja-> ave ya terminada
    }
    return Vector3 (1.0, 1.0, 1.0); //BLANCO
}


int NdoAve::obtTmpChqVrs() const
{
    return tmpChqVrs;
}

int NdoAve::obtCntChVrs()const
{
    return cntChqVrs;
}

void NdoAve::modEst(E ne)
{
        e = ne;
}

void NdoAve::modTmpChqVrs(int nt)
{
    tmpChqVrs = nt;
}


void NdoAve::actCntChqVrs()
{
    if(cntChqVrs == tmpChqVrs)
        cntChqVrs = 0;
    else
    {
        cntChqVrs++;
    }
}

void NdoAve::azarizarTmpChqVrs()
{
    int randy = rand() % 5 + 1;
        tmpChqVrs = randy;
}

int NdoAve::calcEst(vector<VerticeGnr*>& ady) const // recibe un vector y devuelve la cardinalidad de las adyacencias
{
    return ady.size();
}

/*bool NdoAve::operator==(const VerticeGnr& vr) const
{

}*/
//crea una copia del vertice que r
/*void NdoAve::operator=(const VerticeGnr& vr) const
{
    NdoAve *ave = (NdoAve*)&vr;
    this->e = ave->obtEst() ;
}*/


