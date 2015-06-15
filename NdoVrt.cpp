#include "NdoVrt.h"
#include"GrafoGnr.h"
#include<iostream>
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

NdoVrt::NdoVrt(){

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


void NdoVrt::actCntChqVrs(int vrt)
{
    if(cntChqVrs == tmpChqVrs)
        cntChqVrs = 0;
    else
    {
        cntChqVrs++;
    }
}
/*
// cambiar por infectar un vertice
void NdoVrt::infectar(int ios)
{
    if (ios < grafo.obtTotVrt())
    {
        vector<int>infectemos;
        int randy;
        bool esta = true;
        for (int i = 0; i < ios; i++)
        {
            while (esta)
            {
                randy = rand() % grafo.obtTotVrt();
                esta = false;
                for (int j = 0; j < infectemos.size(); j++)
                {
                    if(infectemos[j] == randy) esta = true;
                }
            }
            infectemos.push_back(randy);
            esta = true;
        }
        for (int i=0; i<infectemos.size(); i++)
        {
            arrVrt[infectemos[i]].e = I;
        }
    }
}

*/
void NdoVrt::azarizarTmpChqVrs(int vcf)
{
    int randy = rand() % vcf + 1;
        tmpChqVrs = randy;
}

/*
void NdoVrt::calcEst(int vrt)
{
    for(int i=0; i<arrVrt[vrt].lstAdy.size(); i++)
    {
    if (obtEst(vrt) != GrafoGnr::S) return;
    int cont = 0;
        if(arrVrt[vrt].lstAdy[i].obtEst() == GrafoGnr::I) cont++;
        if (cont == arrVrt[vrt].lstAdy.size()) modEst(vrt, I);
    }
}
*/
