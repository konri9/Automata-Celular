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
    azarizarEstres();
}

NdoAve::NdoAve(const NdoAve& ave){
	e = ave.e;
	niv_strs = ave.niv_strs;
	cnt_niv_strs = ave.cnt_niv_strs;

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


double NdoAve::obtEstres() const
{
    return niv_strs;
}

double NdoAve::obtCntEstres()const
{
    return cnt_niv_strs;
}

void NdoAve::modEst(E ne)
{
        e = ne;
}

void NdoAve::modEstres(double n_estres)
{
    niv_strs = n_estres;
}


void NdoAve::actCntEstres()
{
    if(cnt_niv_strs == niv_strs) //
        cnt_niv_strs = 0;
    else
    {
        cnt_niv_strs++;
    }
}

void NdoAve::azarizarEstres()
{
    double randy =(double) (rand() % 5 + 1);
        niv_strs = randy;
}

// calcula el nuevo estado con la relacion
// La relacion es os = NR*oslanterior  (1+NR) * promedio del nivel de estres de los vecinos
double NdoAve::calcEstres(double osl, double NR, double niveles_str[])//const;
{
    double sum, res;
    for(int i=0; i<sizeof(niveles_str); i++) sum+= niveles_str[i];
    double promedio = (sum * sizeof(niveles_str))/100;
    res = NR*osl*(1+NR)*promedio;
   return res;
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


