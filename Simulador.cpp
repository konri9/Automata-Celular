/*
 * File:   Simulador.cpp
 * Author: Alan
 *
 * Created on 2 de abril de 2015, 06:46 PM
 */

#include <random>
#include <ctime>
#include "Simulador.h"

bool prob(double probability) // probability < 1
{
    double result = (double)rand() / (double)RAND_MAX;
    if(result < probability)
        return true;
    return false;
}

Simulador::Simulador(GrafoGnr<> & grf):grafo(g) {
} //ctor

Simulador::~Simulador() {
}

//ios: cantidad de vertices infectados
//vsc: probabilidad de infeccion
//vcf: checkeo de virus----> Ya no se ocupa entonces
//rc: probabilidad de recuperacion
//grc: probabilidad de obtener resistencia
void Simulador::simular(int cntItr, int ios, double vsc, double rc, double grc) {
    if (grafo == NULL) return;
    srand(time(NULL));
    int checkeo;
    GrafoGnr grafo2(*grafo);

    for (int i = 0; i < ios; i++) // asigna aleatoreamente ios cantidad de vertices infectados al azar
    {
        int id = rand() % grafo->obtTotVrt();
        if (grafo->xstVrt(id))
        {
            if (grafo->obtTotVrt() < ios)
            {
                for (int i = 0; i < grafo->obtTotVrt(); i++)
                {
                    grafo->modEst(i, GrafoGnr::I);
                }
            }
            else
            {
                while (grafo->obtEst(id) == Grafo::I) // si el que encontro ya esta infectado, pide e infecta otro...
                {
                    id = rand() % grafo->obtTotVrt();
                }
                grafo->modEst(id, GrafoGnr::I);
            }
        }
    }

 //Aca son las iteraciones
    for (int i = 0; i < cntItr; i++)
    {
        for (int j = 0; j < grafo->obtTotVrt(); j++)
        {
            if (grafo2.obtEst(j) == GrafoGnr::I)// si el vertice esta infectado
            {
                checkeo = grafo.obtTmpChqVrs(j); //obtiene el temporizador de checkeo de virus
                vector<int>ady;
                grafo->obtAdy(j,ady);
                for (int k = 0; k < ady.size(); k++)
                {
                    if (grafo2.obtEst(ady[k]) != GrafoGnr::R && prob(vsc))// y el adyacente no es resistente
                    {
                        grafo->modEst(ady[k], GrafoGnr::I);//infecta los demas vertices
                    }
                }
                if (chekeo <= 0)// revisar como estaba en el anterior
                {
                    if (prob(rc))
                    {
                        grafo->modEst(j, GrafoGnr::S);
                        if (prob(grc))
                        {
                            grafo->modEst(j, GrafoGnr::R);
                        }
                    }
                }
                grafo.modTmpChqVrs();
            }
        }

       //ACA tengo la duda....
        //if (checkeo <= 0) checkeo = vcf;
        //checkeo--;
    }
}

void Simulador::asignarGrafo(GrafoGnr* g)
{
    grafo = g;
}
