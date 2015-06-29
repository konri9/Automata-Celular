#include "SimuladorVrs.h"
#include "NdoVrs.h"
#include <cstdlib>

bool prob(double probability) // probability < 1
{
    double result = (double)rand() / (double)RAND_MAX;
    if(result <= probability)
    {
        return true;
    }
    return false;
}

SimuladorVrs::SimuladorVrs(GrafoGnr<NdoVrs>* g): SimuladorGnr<NdoVrs>(g)
{
    //ctor
}
//SimuladorVrs::~SimuladorVrs() {
//}

void SimuladorVrs::asignarValores(int nios, double nvsc, double nrc, double ngrc)
{
    ios = nios;
    vsc = nvsc;
    rc = nrc;
    grc = ngrc;
}

void SimuladorVrs::setup(int vrtInf)
{
    if (obtGrafo() == NULL) return;
    srand(time(NULL));
    int tempor ,cont = 0, contemp, cant_infectados = 0, cant_resistentes = 0;
    estados.clear();
    estados.resize(obtGrafo()->obtTotVrt());
    int id = rand() % obtGrafo()->obtTotVrt();
    for (int i = 0; i < estados.size(); i++)
    {
        NdoVrs *nodo = &(*obtGrafo())[i];
        estados[i] = nodo->obtEst();
        if (nodo->obtEst() == NdoVrs::I)
        {
            cant_infectados++;
        }
        else if (nodo->obtEst() == NdoVrs::R)
        {
            cant_resistentes++;
        }
    }
    while (cont<ios && cant_infectados + cant_resistentes != obtGrafo()->obtTotVrt())
    {
        NdoVrs *ndo = &(*obtGrafo())[id];
        if (obtGrafo()->xstVrt(id)&& ndo->obtEst() == NdoVrs::S)
        {
            ndo->modEst(NdoVrs::I);
            estados[id] = NdoVrs::I;
            cont++;
            cant_infectados++;
        }
        else
        {
            id = rand() % obtGrafo()->obtTotVrt();
        }
    }
}

void SimuladorVrs::go(int cntItr)
{
    if (obtGrafo() == NULL) return;
    int tempor, contemp;
    for (int i = 0; i < cntItr; i++)
    {
        for (int j = 0; j < obtGrafo()->obtTotVrt(); j++)
        {
            NdoVrs *nodo = &(*obtGrafo())[j];
            vector<int>ady;
            obtGrafo()->obtAdy(j,ady);
            if (nodo->obtEst() == NdoVrs::I)// si el vertice esta infectado
            {
                tempor = nodo->obtTmpChqVrs(); //obtiene el temporizador de checkeo de virus
                contemp = nodo->obtCntChVrs(); //obtiene el contador de chequeo de virus
                for (int k = 0; k < ady.size(); k++)
                {
                    NdoVrs *nodo2 = &(*obtGrafo())[ady[k]];
                    if (nodo2->obtEst() != NdoVrs::R && nodo2->obtEst() != NdoVrs::I && prob(vsc))// y el adyacente no es resistente
                    {
                        //nodo2->modEst(NdoVrs::I);//infecta los demas vertices
                        estados[ady[k]] = NdoVrs::I;
                    }
                }
                if (tempor == contemp)// si el temporizador es igual que el contador
                {
                    if (prob(rc))
                    {
                        //nodo->modEst(NdoVrs::S);
                        estados[j] = NdoVrs::S;
                        if (prob(grc))
                        {
                            //nodo->modEst(NdoVrs::R);
                            estados[j] = NdoVrs::R;
                        }
                    }
                }
                nodo->actCntChqVrs();
            }
        }

        for (int i = 0; i < estados.size(); i++)
        {
            NdoVrs *nodo = &(*obtGrafo())[i];
            nodo->modEst(estados[i]);
        }
    }
}
