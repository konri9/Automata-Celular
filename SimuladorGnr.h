/*
 * File:   GrafoGnr.h
 * Author: alan.calderon
 *
 * Created on 4 de junio de 2015, 05:49 PM
 */

#ifndef SIMULADORGNR_H
#define	SIMULADORGNR_H

#include <random>
#include <ctime>
#include "GrafoGnr.h"

#ifndef NULL
#define NULL 0
#endif // NULL

using namespace std;
using namespace line_parse;


// Smldr es el tipo de vértice.
template < typename Sm>
class SimuladorGnr
{
public:
    // EFE: Construye un simulador que transformará al grafo g.
    SimuladorGnr(GrafoGnr<Sm>* g);

    // EFE: Construye un simulador que transformará al grafo g visualizando
    //      los cambios de estado por medio de v.
    //Simulador(Grafo* g);

    // Destruye a *this retornando toda la memoria asignada dinámicamente.
    ~SimuladorGnr();

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

    void asignarGrafo(GrafoGnr<Sm> *g);

    // EFE: Asigna las adyacencias del vertice vrt en el vector vec
    void obtAdy(int vrt, vector<Sm>& vec);
    //EFE: Inicializa los datos para la simulacion
    virtual void setup()=0;

    virtual void go() = 0;

private:
    GrafoGnr<Sm> *grafo;

};

bool prob(double probability) // probability < 1
{
    double result = (double)rand() / (double)RAND_MAX;
    if(result < probability)
        return true;
    return false;
}

template < typename Sm>
SimuladorGnr<Sm>::SimuladorGnr(GrafoGnr<Sm>* g) : grafo(g)
{

}

template < typename Sm>
SimuladorGnr<Sm>::~SimuladorGnr()
{
}

//ios: cantidad de vertices infectados
//vsc: probabilidad de infeccion
//vcf: checkeo de virus----> Ya no se ocupa entonces
//rc: probabilidad de recuperacion
//grc: probabilidad de obtener resistencia

template < typename Sm >
void SimuladorGnr<Sm>::asignarGrafo(GrafoGnr<Sm>* g)
{
    grafo = g;
}

template < typename Sm >
void SimuladorGnr<Sm>::obtAdy(vector<Sm>& vec)
{
    vec.clear();
    vector<int> ady;
    grafo->obtAdy(vrt, ady);
    for (int i = 0; i < grafo->obtCntAdy(vrt); i++)
    {
        vec.push_back(grafo[ady[i]]);
    }
}

template < typename Sm >
void SimuladorGnr<Sm>::obtEstadosTotales(vector<Sm>& vec)
{
    vec.clear();
    vector<NdoVrt::e> estados;
    grafo->obtAdy(vrt, ady);
    for (int i = 0; i < grafo->obtTotVrt(); i++)
    {
        vec.push_back(grafo[ady[i]]);
    }
}


#endif	/* VISUALIZADORGNR_H */

