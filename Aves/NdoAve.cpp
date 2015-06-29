#include "NdoAve.h"
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

NdoAve::NdoAve(){
    e = S;
    azarizarTmpChqVrs();
}

NdoAve::~NdoAve()
{
    //dtor
}


NdoAve::E NdoAve::obtEst() const
{
        return e;
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

void NdoAve::calcEst(vector<VerticeGnr*>& ady)
{
    int cont = 0;
    for(int i=0; i<ady.size(); i++)
    {
        NdoAve *ave = (NdoAve*)ady[i];
        if (ave->obtEst() != NdoAve::S) return;
        if(ave->obtEst() == NdoAve::SS) cont++;
        if (cont == ady.size()) modEst(NdoAve::SSS);
    }
}
