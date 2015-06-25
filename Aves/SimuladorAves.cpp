/*
 * File:   SimuladorAves.cpp
 * Author: Alan
 *
 * Created on 2 de abril de 2015, 06:46 PM
 */

#include <random>
#include <ctime>
#include "SimuladorAves.h"
#include "NdoAves.h"

SimuladorAves::SimuladorAves(GrafoGnr<NdoVrt> *grf):grafo(grf) {
} //ctor

SimuladorAves::~SimuladorAves() {
}

//ios: cantidad de vertices infectados
//vsc: probabilidad de infeccion
//vcf: checkeo de virus----> Ya no se ocupa entonces
//rc: probabilidad de recuperacion
//grc: probabilidad de obtener resistencia
void SimuladorAves::simular(int cntItr, int ios, double vsc, double rc, double grc) {
    if (grafo == NULL) return;
    srand(time(NULL));
    int tempor ,cont = 0, contemp;
    vector<NdoVrt::E> estados;
    estados.resize(grafo->obtTotVrt());
    int id = rand() % grafo->obtTotVrt();
    for (int i = 0; i < estados.size(); i++)
    {
        NdoVrt *nodo = &(*grafo)[i];
        estados[i] = nodo->obtEst();
    }
    while (cont<ios){
        NdoVrt *ndo = &(*grafo)[id];
        if (grafo->xstVrt(id)&& ndo->obtEst() == NdoVrt::S) {
        ndo->modEst(NdoVrt::I);
        estados[id] = NdoVrt::I;
        /*for (int i = 0; i < grafo->obtTotVrt(); i++)
        {
            NdoVrt nodo2 = (*grafo)[i];
            cout << "Nodo " << i << ": " << nodo2.obtEst() << endl;
        }*/
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
            NdoVrt *nodo = &(*grafo)[j];
            vector<int>ady;
            grafo->obtAdy(j,ady);
            if (nodo->obtEst() == NdoVrt::I)// si el vertice esta infectado
            {
                tempor = nodo->obtTmpChqVrs(); //obtiene el temporizador de checkeo de virus
                contemp = nodo->obtCntChVrs(); //obtiene el contador de chequeo de virus
                for (int k = 0; k < ady.size(); k++)
                {
                    NdoVrt *nodo2 = &(*grafo)[ady[k]];
                    if (nodo2->obtEst() != NdoVrt::R && nodo2->obtEst() != NdoVrt::I && prob(vsc))// y el adyacente no es resistente
                    {
                        nodo2->modEst(NdoVrt::I);//infecta los demas vertices
                        estados[k] = NdoVrt::I;
                    }
                }
                if (tempor == contemp)// si el temporizador es igual que el contador
                {
                    if (prob(rc))
                    {
                        nodo->modEst(NdoVrt::S);
                        estados[j] = NdoVrt::S;
                        if (prob(grc))
                        {
                            nodo->modEst(NdoVrt::R);
                            estados[j] = NdoVrt::R;
                        }
                    }
                }
                nodo->actCntChqVrs();
            }
        }

        for (int i = 0; i < estados.size(); i++)
        {
            NdoVrt *nodo = &(*grafo)[i];
            nodo->modEst(estados[i]);
        }
    }
}

void SimuladorAves::asignarGrafo(GrafoGnr<NdoVrt>* g)
{
    grafo = g;
}
