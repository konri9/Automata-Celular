#include "NdoAves.h"
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

NdoAves::NdoAves(){
    e = S;
    azarizarTmpChqVrs();
}

NdoAves::~NdoAves()
{
    //dtor
}


NdoAves::E NdoAves::obtEst() const
{
        return e;
}

int NdoAves::obtTmpChqVrs() const
{
    return tmpChqVrs;
}

int NdoAves::obtCntChVrs()const
{
    return cntChqVrs;
}

void NdoAves::modEst(E ne)
{
        e = ne;
}

void NdoAves::modTmpChqVrs(int nt)
{
    tmpChqVrs = nt;
}


void NdoAves::actCntChqVrs()
{
    if(cntChqVrs == tmpChqVrs)
        cntChqVrs = 0;
    else
    {
        cntChqVrs++;
    }
}

void NdoAves::azarizarTmpChqVrs()
{
    int randy = rand() % 5 + 1;
        tmpChqVrs = randy;
}


void NdoAves::calcEst(vector<int> adyac)
{
    for(int i=0; i<adyac.size(); i++)
    {
        if (obtEst() != NdoAves::S) return;
        int cont = 0;
        if(obtEst() == NdoAves::I) cont++;
        if (cont == adyac.size()) modEst(NdoAves::I);
    }
}

