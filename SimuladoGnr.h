/*
 * File:   GrafoGnr.h
 * Author: alan.calderon
 *
 * Created on 4 de junio de 2015, 05:49 PM
 */

#ifndef GRAFOGNR_H
#define	GRAFOGNR_H

#include <random>
#include <ctime>
#include "Simulador.h"

#ifndef NULL
#define NULL 0
#endif // NULL

using namespace std;
using namespace line_parse;



/*go Y SETUP*/


// Smldr es el tipo de vértice.
template < typename Sm>

class SimuladorGnr {

    // EFE: Construye un simulador que transformará al grafo g.
    Simulador(Grafo* g);

    // EFE: Construye un simulador que transformará al grafo g visualizando
    //      los cambios de estado por medio de v.
    //Simulador(Grafo* g);

    // Destruye a *this retornando toda la memoria asignada dinámicamente.
    ~Simulador();

    // REQ: el grafo asociado (el pasado al constructor) esté bien construido.
    // MOD: el grafo asociado.
    // EFE: aplica al grafo asociado cntItr transformaciones con base en los
    //      siguientes parámetros:
    //      cItr > 1000: cantidad de iteraciones.
    //      ios o initial-outbreak-size [1..N], N cantidad de vértices: cantidad
    //           de vértices infectados al comienzo de la simulación.
    //      vsc o virus-spread-chance [0..0.1]: probabilidad de infección.
    //      vcf o virus-check-frecuency [1..20]: frecuencia de chequeo antivirus.
    //      rc o recovery-chance [0..0.1]: probabilidad de recuperación de infección.
    //      grc o gain-resistance-chance [0..1]: probabilidad de lograr resistencia.
    //      Aplica la siguiente regla de cambio de estado para los vértices:
    //      1. un vértice sólo puede ser infectado por alguno de sus vecinos infectados
    //         con probabilidad vsc.
    //      2. sólo un vértice infectado cuyo temporizador de chequeo de virus está en cero
    //         puede recuperarse con probabilidad rc.
    //      3. sólo un vértice recuperado puede ganar resistencia con probabilidad grc.
    //      4. Sólo las transformaciones #2 y #3 pueden ser simultáneas.
    void simular(int cItr, int ios, double vsc, double rc, double grc);

    void asignarGrafo(Grafo *g);

private:
    Grafo *grafo;

};

template < typename Sm>
bool prob(double probability) // probability < 1
{
    double result = (double)rand() / (double)RAND_MAX;
    if(result < probability)
        return true;
    return false;
}
template < typename Sm>
Simulador::Simulador(Grafo *g):grafo(g) {
}

template < typename Sm>
Simulador::~Simulador() {
}

//ios: cantidad de vertices infectados
//vsc: probabilidad de infeccion
//vcf: checkeo de virus----> Ya no se ocupa entonces
//rc: probabilidad de recuperacion
//grc: probabilidad de obtener resistencia

template < typename Sm>
void Simulador::simular(int cntItr, int ios, double vsc, double rc, double grc) {
    if (grafo == NULL) return;
    srand(time(NULL));
    int checkeo;
    Grafo grafo2(*grafo);

    for (int i = 0; i < ios; i++) // asigna aleatoreamente ios cantidad de vertices infectados al azar
    {
        int id = rand() % grafo->obtTotVrt();
        if (grafo->xstVrt(id))
        {
            if (grafo->obtTotVrt() < ios)
            {
                for (int i = 0; i < grafo->obtTotVrt(); i++)
                {
                    grafo->modEst(i, Grafo::I);
                }
            }
            else
            {
                while (grafo->obtEst(id) == Grafo::I) // si el que encontro ya esta infectado, pide e infecta otro...
                {
                    id = rand() % grafo->obtTotVrt();
                }
                grafo->modEst(id, Grafo::I);
            }
        }
    }

 //Aca son las iteraciones
    for (int i = 0; i < cntItr; i++)
    {
        for (int j = 0; j < grafo->obtTotVrt(); j++)
        {
            if (grafo2.obtEst(j) == Grafo::I)// si el vertice esta infectado
            {
                checkeo = grafo.obtTmpChqVrs(j); //obtiene el temporizador de checkeo de virus
                vector<int>ady;
                grafo->obtAdy(j,ady);
                for (int k = 0; k < ady.size(); k++)
                {
                    if (grafo2.obtEst(ady[k]) != Grafo::R && prob(vsc))// y el adyacente no es resistente
                    {
                        grafo->modEst(ady[k], Grafo::I);//infecta los demas vertices
                    }
                }
                if (chekeo <= 0)// revisar como estaba en el anterior
                {
                    if (prob(rc))
                    {
                        grafo->modEst(j, Grafo::S);
                        if (prob(grc))
                        {
                            grafo->modEst(j, Grafo::R);
                        }
                    }
                }
                grafo.modTmpChqVrs();
            }
        }
    }
}

template < typename Smldr >
void Simulador::asignarGrafo(Grafo* g)
{
    grafo = g;
}


#endif	/* VISUALIZADORGNR_H */

