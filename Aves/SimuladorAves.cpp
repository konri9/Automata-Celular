#include "SimuladorAves.h"
#include "NdoAve.h"
#include <cstdlib>

bool proba(double probability) // probability < 1
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
void  SimuladorAves::asignarValores(int navs, double nanr)
{
    avs = navs;
    anr = nanr;
}

void SimuladorAves::setup(int cntAves)
{
    if (obtGrafo() == NULL) return;
    srand(time(NULL));
    int cont = 0, cant_estresados = 0, cant_prd = 0; // REPARTIR ACA LOS
    estados.clear();
    estreses.clear();
    estados.resize(obtGrafo()->obtTotVrt());
    estreses.resize(obtGrafo()->obtTotVrt());
    int id = rand() % obtGrafo()->obtTotVrt();
    for (int i = 0; i < estados.size(); i++) //Llena el vector de estados
    {
        NdoAve *nodo_av = &(*obtGrafo())[i];
        estados[i] = nodo_av->obtEst();
        estreses[i] = nodo_av->obtEstres();
        if(nodo_av ->obtEst() == NdoAve::R)
        {
            cant_estresados++;
        }
        else if (nodo_av->obtEst()== NdoAve::S)
        {
            cant_prd++;
        }
    }
    while (cont<avs && cant_estresados+cant_prd != obtGrafo()->obtTotVrt())
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

void SimuladorAves::asignarNR(double nNR)
{
    NR = nNR;
}

void SimuladorAves::go(int cntItr)
{
    if (obtGrafo() == NULL) return;
    int cont_paridos = 0;
    for (int i = 0; i < cntItr; i++)
    {
        for (int j = 0; j < obtGrafo()->obtTotVrt(); j++)
        {
            NdoAve *nodo_av = &(*obtGrafo())[j];
            vector<int>ady;
            obtGrafo()->obtAdy(j,ady);
            int varas = ady.size();
            vector<double> estresesaves;
            for(int k = 0; k < varas; k++)
            {
                NdoAve *ave = &(*obtGrafo())[ady[k]];
                //cout << "adyacencia: " << ady[k] << endl;
                estresesaves.push_back(ave->obtEstres());
                //cout << "Estres ave: " << estresesaves[k] << endl;
            }
            //ok
            estreses[j] = nodo_av->calcEstres(NR, estresesaves);

            if(0 < nodo_av->obtEstres() < 1.5)
            {
                estados[j] = NdoAve::R; // relajada
            }

            if(1.5 < nodo_av->obtEstres() < 4)
            {
                estados[j] = NdoAve::S; //estresada
            }

            if(nodo_av->obtEstres() >= 4 )
            {
                estados[j] = NdoAve::P; // se estreso tanto que pario
            }

            if(nodo_av->obtEst() == NdoAve::P)
            {
                nodo_av->modEst(NdoAve::M); // ya pario entonces se pone en negro
            }

            if(nodo_av->obtEst() == NdoAve::M)
            {
                cont_paridos++;
            }

            /*if (cont_paridos == obtGrafo()->obtTotVrt())
            {
                dele = false;
            }*/
        }
        for (int m = 0; m < estados.size(); m++)
        {
            NdoAve *nodo_av = &(*obtGrafo())[m];
            nodo_av->modEst(estados[m]);
            nodo_av->modEstres(estreses[m]);
        }
    }
}
