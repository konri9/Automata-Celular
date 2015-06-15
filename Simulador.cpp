/*
 * File:   Simulador.cpp
 * Author: Alan
 *
 * Created on 2 de abril de 2015, 06:46 PM
 */

#include <random>
#include <ctime>
#include "Simulador.h"
#include "NdoVrt.h"


Simulador::Simulador(GrafoGnr<NdoVrt> *grf):grafo(grf) {
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
//    grafo.azarizarTmpChqVrs(vcf);
    vector<NdoVrt::E> estados;
    estados.resize(grafo->obtTotVrt());
    for (int i = 0; i < ios; i++) // asigna aleatoreamente ios cantidad de vertices infectados al azar
    {
        int id = rand() % grafo->obtTotVrt();
        if (grafo->xstVrt(id))
        {
            if (grafo->obtTotVrt() < ios)
            {
                for (int i = 0; i < grafo->obtTotVrt(); i++)
                {
                    NdoVrt ndo = (*grafo)[i];//.modEst(i, GrafoGnr::I);
                    ndo.modEst(NdoVrt::I);
                }
            }
            else
            {
                NdoVrt ndo = (*grafo)[id];//.modEst(i, GrafoGnr::I);
                while (ndo.obtEst() == NdoVrt::I) // si el que encontro ya esta infectado, pide e infecta otro...
                {
                    id = rand() % grafo->obtTotVrt();
                }
                   NdoVrt ndo2 = (*grafo)[i];//.modEst(i, GrafoGnr::I);
                  ndo2.modEst(NdoVrt::I);
            }
        }
    }

 //Aca son las iteraciones
    for (int i = 0; i < cntItr; i++)
    {
        for (int j = 0; j < grafo->obtTotVrt(); j++)
        {
            NdoVrt nodo = (*grafo)[j];
            if (nodo.obtEst() == NdoVrt::I)// si el vertice esta infectado
            {
                checkeo = nodo.obtTmpChqVrs(); //obtiene el temporizador de checkeo de virus
                vector<int>ady;
                grafo->obtAdy(j,ady);
                for (int k = 0; k < ady.size(); k++)
                {
                    NdoVrt nodo2 = (*grafo)[ady[k]];
                    if (nodo2.obtEst() != NdoVrt::R && prob(vsc))// y el adyacente no es resistente
                    {
                        nodo2.modEst(NdoVrt::I);//infecta los demas vertices
                    }
                }
                if (checkeo <= 0)// revisar como estaba en el anterior
                {
                    if (prob(rc))
                    {
                        nodo.modEst(NdoVrt::S);
                        if (prob(grc))
                        {
                            nodo.modEst(NdoVrt::R);
                        }
                    }
                }
                nodo.actCntChqVrs();
            }
        }
        for (int i = 0; i < estados.size(); i++)
        {
            NdoVrt nodo = (*grafo)[i];
            nodo.modEst(estados[i]);
        }
    }
}

void Simulador::asignarGrafo(GrafoGnr<NdoVrt>* g)
{
    grafo = g;
}
