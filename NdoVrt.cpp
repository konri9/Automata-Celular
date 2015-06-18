#include "NdoVrt.h"
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

NdoVrt::NdoVrt()
{
    e = S;
    azarizarTmpChqVrs();
}

NdoVrt::~NdoVrt()
{
    //dtor
}


NdoVrt::E NdoVrt::obtEst() const
{
    return e;
}

int NdoVrt::obtTmpChqVrs() const
{
    return tmpChqVrs;
}

int NdoVrt::obtCntChVrs()const
{
    return cntChqVrs;
}

void NdoVrt::modEst(E ne)
{
    e = ne;
}

void NdoVrt::modTmpChqVrs(int nt)
{
    tmpChqVrs = nt;
}


void NdoVrt::actCntChqVrs()
{
    if(cntChqVrs == tmpChqVrs)
        cntChqVrs = 0;
    else
    {
        cntChqVrs++;
    }
}

void NdoVrt::azarizarTmpChqVrs()
{
    int randy = rand() % 5 + 1;
    tmpChqVrs = randy;
}


void NdoVrt::calcEst(vector<int> adyac)
{
    for(int i=0; i<adyac.size(); i++)
    {
        if (obtEst() != NdoVrt::S) return;
        int cont = 0;
        if(obtEst() == NdoVrt::I) cont++;
        if (cont == adyac.size()) modEst(NdoVrt::I);
    }
}

