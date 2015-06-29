#include "SimuladorAves.h"
#include "NdoAve.h"
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

SimuladorAves::SimuladorAves(GrafoGnr<NdoAve>* g): SimuladorGnr<NdoAve>(g)
{
    //ctor
}
//SimuladorAves::~SimuladorAves() {
//}
void  SimuladorAves::asignarValores(int nios, double nvsc, double nrc, double ngrc)
{
	ios = nios;
	vsc = nvsc;
	rc = nrc;
	grc = ngrc;
}

void SimuladorAves::setup(int cntIter)
{
    if (obtGrafo() == NULL) return;
    srand(time(NULL));
    int cont = 0, cant_estresados = 0, cant_prd = 0;
    estados.clear();
    estados.resize(obtGrafo()->obtTotVrt());
    int id = rand() % obtGrafo()->obtTotVrt();
    for (int i = 0; i < estados.size(); i++)
    {
        NdoAve *nodo = &(*obtGrafo())[i];
        estados[i] = nodo->obtEst();
		if(nodo ->obtEst() == NdoAve::S)
		{
			cant_estresados++;
    	}
		else if (nodo->obtEst()== NdoAve::R)
		{
			cant_prd++;
		}
	}
    while (cont<ios && cant_estresados+cant_prd != obtGrafo()->obtTotVrt())
    {
        NdoAve *ndo = &(*obtGrafo())[id];
        if (obtGrafo()->xstVrt(id)&& ndo->obtEst() == NdoAve::R)
        {
            ndo->modEst(NdoAve::S);
            estados[id] = NdoAve::S;
            cont++;
			cant_estresados++;
        }
        else
        {
            id = rand() % obtGrafo()->obtTotVrt();
        }
    }
}

void SimuladorAves::go(int cntItr)
{
	if (obtGrafo() == NULL) return;
	int tempor ,contemp;
    for (int i = 0; i < cntItr; i++)
    {
        for (int j = 0; j < obtGrafo()->obtTotVrt(); j++)
        {
            NdoAve *nodo = &(*obtGrafo())[j];
            vector<int>ady;
            grafo->obtAdy(j,ady);
            if (nodo->obtEst() == NdoAve::S)// si el ave esta estresada
            {
                tempor = nodo->obtTmpChqVrs(); //obtiene el temporizador de checkeo de virus
                contemp = nodo->obtCntChVrs(); //obtiene el contador de chequeo de virus
                for (int k = 0; k < ady.size(); k++)
                {
                    NdoAve *nodo2 = &(*obtGrafo())[ady[k]];
                    if (nodo2->obtEst() != NdoAve::P && nodo2->obtEst() != NdoAve::S && prob(vsc))// y el adyacente no es resistente
                    {
                        //nodo2->modEst(NdoAve::I);//infecta los demas vertices
                        estados[ady[k]] = NdoAve::S;
                    }
                }
                if (tempor == contemp)// si el temporizador es igual que el contador
                {
                    if (prob(rc))
                    {
                        //nodo->modEst(NdoAve::S);
                        estados[j] = NdoAve::R;
                        if (prob(grc))
                        {
                          //  nodo->modEst(NdoAve::P);
                            estados[j] = NdoAve::P;
                        }
                    }
                }
                nodo->actCntChqVrs();
            }
        }

        for (int i = 0; i < estados.size(); i++)
        {
            NdoAve *nodo = &(*obtGrafo())[i];
            nodo->modEst(estados[i]);
        }
    }
}
