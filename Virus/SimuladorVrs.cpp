#include "SimuladorGnr.h"
#include "NdoVrs.h"

template < typename Vrs>
SimuladorVrs::SimuladorVrs(GrafoGnr<NdoVrs>* g): SimuladorGnr<Vrs>(g)
{
    //ctor
}
//hacer un metodo virtual puro que asigne el color

//SimuladorVrs::~SimuladorVrs() {
//}

void SimuladorVrs::setup()
{
    if (grafo == NULL) return;
    srand(time(NULL));
    int tempor ,cont = 0, contemp;
    vector<NdoVrs::E> estados;
    estados.resize(grafo->obtTotVrt());
    int id = rand() % grafo->obtTotVrt();
    for (int i = 0; i < estados.size(); i++)
    {
        NdoVrs *nodo = &(*grafo)[i];
        estados[i] = nodo->obtEst();
    }
    while (cont<ios)
    {
        NdoVrs *ndo = &(*grafo)[id];
        if (grafo->xstVrt(id)&& ndo->obtEst() == NdoVrs::S)
        {
            ndo->modEst(NdoVrs::I);
            estados[id] = NdoVrs::I;
            cont++;
        }
        else
        {
            id = rand() % grafo->obtTotVrt();
        }
    }
}




template < typename Vrs>
void SimuladorVrs::go()
{
    for (int i = 0; i < cntItr; i++)
    {
        for (int j = 0; j < grafo->obtTotVrt(); j++)
        {
            go(j);//

            NdoVrs *nodo = &(*grafo)[j];
            vector<int>ady;
            grafo->obtAdy(j,ady);
            if (nodo->obtEst() == NdoVrs::I)// si el vertice esta infectado
            {
                tempor = nodo->obtTmpChqVrs(); //obtiene el temporizador de checkeo de virus
                contemp = nodo->obtCntChVrs(); //obtiene el contador de chequeo de virus
                for (int k = 0; k < ady.size(); k++)
                {
                    NdoVrs *nodo2 = &(*grafo)[ady[k]];
                    if (nodo2->obtEst() != NdoVrs::R && nodo2->obtEst() != NdoVrs::I && prob(vsc))// y el adyacente no es resistente
                    {
                        nodo2->modEst(NdoVrs::I);//infecta los demas vertices
                        estados[k] = NdoVrs::I;
                    }
                }
                if (tempor == contemp)// si el temporizador es igual que el contador
                {
                    if (prob(rc))
                    {
                        nodo->modEst(NdoVrs::S);
                        estados[j] = NdoVrs::S;
                        if (prob(grc))
                        {
                            nodo->modEst(NdoVrs::R);
                            estados[j] = NdoVrs::R;
                        }
                    }
                }
                nodo->actCntChqVrs();
            }
        }

        for (int i = 0; i < estados.size(); i++)
        {
            NdoVrs *nodo = &(*grafo)[i];
            nodo->modEst(estados[i]);
        }
    }
}
