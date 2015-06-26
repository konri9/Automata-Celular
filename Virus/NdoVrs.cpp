#include "NdoVrs.h"
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

using namespace std;


bool prob(double probability) // probability < 1
{
    double result = (double)rand() / (double)RAND_MAX;
    if(result < probability)
        return true;
    return false;
}

NdoVrs::NdoVrs(){
    e = S;
    azarizarTmpChqVrs();
}

NdoVrs::~NdoVrs()
{
    //dtor
}


NdoVrs::E NdoVrs::obtEst() const
{
        return e;
}

Vector3 NdoVrs::obtColor()
{
    if (obtEst(vrt) == NdoVrs::S) {
        return Vector3(0.0, 1.0, 0.0); //Color verde -> vertice suceptible
    }
    if (obtEst(vrt) == NdoVrs::I) {
        return Vector3(1.0, 0.0, 0.0);//Color rojo -> vertice infectado
    }
    if (obtEst(vrt) == NdoVrs::R) {
        return Vector3(1.0, 0.5, 0.0); //Color naranja-> vertice resistente
    }
    return Vector3 (1.0, 1.0, 1.0); //BLANCO
}

int NdoVrs::obtTmpChqVrs() const
{
    return tmpChqVrs;
}

int NdoVrs::obtCntChVrs()const
{
    return cntChqVrs;
}

void NdoVrs::modEst(E ne)
{
        e = ne;
}

void NdoVrs::modTmpChqVrs(int nt)
{
    tmpChqVrs = nt;
}


void NdoVrs::actCntChqVrs()
{
    if(cntChqVrs == tmpChqVrs)
        cntChqVrs = 0;
    else
    {
        cntChqVrs++;
    }
}

void NdoVrs::azarizarTmpChqVrs()
{
    int randy = rand() % 5 + 1;
        tmpChqVrs = randy;
}


void NdoVrs::calcEst(vector<VerticeGnr*>& ady)
{
    for(int i=0; i<adyac.size(); i++)
    {
        if (obtEst() != NdoVrs::S) return;
        int cont = 0;
        if(obtEst() == NdoVrs::I) cont++;
        if (cont == adyac.size()) modEst(NdoVrs::I);
    }
}

