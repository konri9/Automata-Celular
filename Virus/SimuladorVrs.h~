#ifndef SIMULADORVRS_H
#define SIMULADORVRS_H

#include "SimuladorGnr.h"


template <typename Vrs>

class SimuladorVrs : public SimuladorGnr<Vrs>
{
public:
    SimuladorVrs(GrafoGnr<Vrs>* g);
    //~SimuladorVrs();

    void setup();

    void go();

protected:
private:
};

template < typename Vrs>
SimuladorVrs<Vrs>::SimuladorVrs(GrafoGnr<Vrs>* g): SimuladorGnr<Vrs>(g)
{

}
//hacer un metodo virtual puro que asigne el color


template < typename Vrs>
void SimuladorVrs::setup()
{
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
        cont++;
            }
        else {
             id = rand() % grafo->obtTotVrt();
             }
        }
}




template < typename Vrs>
void SimuladorVrs::go()
{
    //Aca son las iteraciones
    for (int i = 0; i < cntItr; i++)
    {
        for (int j = 0; j < grafo->obtTotVrt(); j++)
        {
            go(j);//

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

#endif // SIMULADORVRS_H

