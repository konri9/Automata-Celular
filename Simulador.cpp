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
    int checkeo,cont = 0;
    vector<NdoVrt::E> estados;
    estados.resize(grafo->obtTotVrt());
    int id = rand() % grafo->obtTotVrt();
    NdoVrt ndo = (*grafo)[id];
    while (cont<ios){
        if (grafo->xstVrt(id)&& ndo.obtEst() != NdoVrt::I) {
        ndo.modEst(NdoVrt::I);
        cont++;
            }
        else {
             id = rand() % grafo->obtTotVrt();
             }
        }

 //Aca son las iteraciones
    for (int i = 0; i < cntItr; i++)
    {
        for (int j = 0; j < grafo->obtTotVrt(); j++)
        {
            NdoVrt nodo = (*grafo)[j];
            nodo.azarizarTmpChqVrs();
            cout<< "el temp es"<<nodo.obtTmpChqVrs()<<endl;
            vector<int>ady;
            grafo->obtAdy(j,ady);
            nodo.calcEst(ady);
            if (nodo.obtEst() == NdoVrt::I)// si el vertice esta infectado
            {
                checkeo = nodo.obtTmpChqVrs(); //obtiene el temporizador de checkeo de virus
                for (int k = 0; k < ady.size(); k++)
                {
                    NdoVrt nodo2 = (*grafo)[ady[k]];
                    if (nodo2.obtEst() != NdoVrt::R && prob(vsc))// y el adyacente no es resistente
                    {
                        nodo2.modEst(NdoVrt::I);//infecta los demas vertices
                    }
                }
                if (checkeo <= 0)
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
