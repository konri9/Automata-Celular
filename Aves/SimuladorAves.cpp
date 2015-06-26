#include <random>
#include <ctime>
#include "SimuladorAves.h"
#include "NdoAve.h"

SimuladorAves::SimuladorAves(GrafoGnr<NdoAve>* g): SimuladorGnr<NdoAve>(g)
{
    //ctor
}


//hacer un metodo virtual puro que asigne el color

//SimuladorAves::~SimuladorAves() {
//}


void SimuladorAves::setup()
{
    if (grafo == NULL) return;
    srand(time(NULL));
    int tempor ,cont = 0, contemp;
    vector<NdoAve::E> estados;
    estados.resize(grafo->obtTotVrt());
    int id = rand() % grafo->obtTotVrt();
    for (int i = 0; i < estados.size(); i++)
    {
        NdoAve *nodo = &(*grafo)[i];
        estados[i] = nodo->obtEst();
    }
    /*while (cont<ios)
    {
        NdoAve *ndo = &(*grafo)[id];
        if (grafo->xstVrt(id)&& ndo->obtEst() == NdoAve::S)
        {
            ndo->modEst(NdoAve::I);
            estados[id] = NdoAve::I;
            cont++;
        }
        else
        {
            id = rand() % grafo->obtTotVrt();
        }
    }*/
}

void SimuladorAves::go()
{
    /*for (int i = 0; i < cntItr; i++)
    {
        for (int j = 0; j < grafo->obtTotVrt(); j++)
        {
            go(j);//

            NdoAve *nodo = &(*grafo)[j];
            vector<int>ady;
            grafo->obtAdy(j,ady);
            if (nodo->obtEst() == NdoAve::I)// si el vertice esta infectado
            {
                tempor = nodo->obtTmpChqVrs(); //obtiene el temporizador de checkeo de virus
                contemp = nodo->obtCntChVrs(); //obtiene el contador de chequeo de virus
                for (int k = 0; k < ady.size(); k++)
                {
                    NdoAve *nodo2 = &(*grafo)[ady[k]];
                    if (nodo2->obtEst() != NdoAve::R && nodo2->obtEst() != NdoAve::I && prob(vsc))// y el adyacente no es resistente
                    {
                        nodo2->modEst(NdoAve::I);//infecta los demas vertices
                        estados[k] = NdoAve::I;
                    }
                }
                if (tempor == contemp)// si el temporizador es igual que el contador
                {
                    if (prob(rc))
                    {
                        nodo->modEst(NdoAve::S);
                        estados[j] = NdoAve::S;
                        if (prob(grc))
                        {
                            nodo->modEst(NdoAve::R);
                            estados[j] = NdoAve::R;
                        }
                    }
                }
                nodo->actCntChqVrs();
            }
        }

        for (int i = 0; i < estados.size(); i++)
        {
            NdoAve *nodo = &(*grafo)[i];
            nodo->modEst(estados[i]);
        }
    }*/
}
