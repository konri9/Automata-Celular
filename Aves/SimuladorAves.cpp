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

void SimuladorAves::setup(int cntIter)
{
    if (obtGrafo() == NULL) return;
    srand(time(NULL));
    int cont = 0, cant_estresados = 0, cant_prd = 0;
    estados.clear();
    estados.resize(obtGrafo()->obtTotVrt());
    int id = rand() % obtGrafo()->obtTotVrt();
    for (int i = 0; i < estados.size(); i++) //Llena el vector de estados
    {
       NdoAve *nodo_av = &(*obtGrafo())[i];
        estados[i] = nodo_av->obtEst();
        if(nodo_av ->obtEst() == NdoAve::S)
        {
            cant_estresados++;
        }
        else if (nodo_av->obtEst()== NdoAve::R)
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

void SimuladorAves::go(int cntItr)
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
                vector<int>ady, radio_adyac;
                obtGrafo()->obtAdy(j,ady);
                obtGrafo()->obtRadioAdy(j, radio_adyac);
                //nodo_av->calcEst(j);
                  //deberia de ser == 4 y que calc est devuelva un valor... asi le puedo mandar el radioAdy
                // se analiza el nuevo estado (deveria retornar e)
                // si inmediatamente adyacentes estan estresados entonces se estresa

                if (ady.size() == 4) // vecinos estresador => ave estresada
                {
                    estados[j] = NdoAve::S;
                }
                if(radio_adyac.size() == 7) // todos los que le rodean estan estresados entonces pone un huevo :D
                {
                    estados[j] = NdoAve::P;
                    cont_paridos++;
                }
                if (cont_paridos == obtGrafo()->obtTotVrt())dele = false;

            }
        }
    }

for (int i = 0; i < estados.size(); i++)
    {
        NdoAve *nodo_av = &(*obtGrafo())[i];
        nodo_av->modEst(estados[i]);
    }
}
