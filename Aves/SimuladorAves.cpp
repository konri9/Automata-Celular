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
void  SimuladorAves::asignarValores(int nios, double nvsc, double nrc, double ngrc)
{
    ios = nios;
    vsc = nvsc;
    rc = nrc;
    grc = ngrc;
}

void SimuladorAves::setup(int cntAves)
{
    if (obtGrafo() == NULL) return;
    srand(time(NULL));
    int cont = 0, cant_estresados = 0, cant_prd = 0; // REPARTIR ACA LOS
    estados.clear();
    estados.resize(obtGrafo()->obtTotVrt());
    int id = rand() % obtGrafo()->obtTotVrt();
    for (int i = 0; i < estados.size(); i++) //Llena el vector de estados
    {
        NdoAve *nodo_av = &(*obtGrafo())[i];
        estados[i] = nodo_av->obtEst();
        if(nodo_av ->obtEst() == NdoAve::R)
        {
            cant_estresados++;
        }
        else if (nodo_av->obtEst()== NdoAve::S)
        {
            cant_prd++;
        }
    }
    //Estresador() jaja
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

void SimuladorAves::go(int cntItr, double NR)
{
    if (obtGrafo() == NULL) return;
    int cont_paridos = 0;
    bool dele = true;
    {
        while (dele)
            for (int i = 0; i < cntItr; i++)
            {
                for (int j = 0; j < obtGrafo()->obtTotVrt(); j++)
                {
                    NdoAve *nodo_av = &(*obtGrafo())[j];
                    vector<int>ady;
                    obtGrafo()->obtAdy(j,ady);
                    int varas = ady.size();
                    double estreses [varas]; // -.-
                    for(int k = 0; k< sizeof(estreses);k++)
                    {
                        NdoAve *ave = &(*obtGrafo())[ady[i]];
                        estreses[i] = ave->obtEstres();
                    }
                   nodo_av->niv_strs = nodo_av->calcEstres(nodo_av->obtEstres(), NR, estreses);

                    if(0 < nodo_av->niv_strs < 1.5){
                        estados[j] = NdoAve::R; // relajada
                    }

                    if(1.5 < nodo_av->niv_strs < 4){
                        estados[j] = NdoAve::S; //estresada
                    }

                    if(nodo_av->niv_strs >= 4 ){
                        estados[j] = NdoAve::P; // se estreso tanto que pario
                        cont_paridos++;
                    }

                    if(nodo_av->obtEst() == NdoAve::P){
                        nodo_av->modEst(NdoAve::N); // ya pario entonces se pone en negro

                    }
                    if (cont_paridos == obtGrafo()->obtTotVrt()) dele = false;

                }
            }
    }

    for (int i = 0; i < estados.size(); i++)
    {
        NdoAve *nodo_av = &(*obtGrafo())[i];
        nodo_av->modEst(estados[i]);
    }
}
