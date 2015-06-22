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
    void simular(int cItr, int ios, double vsc, double rc, double grc);

    void asignarGrafo(GrafoGnr<Sm> *g);

    virtual void go() = 0;
    virtual void setup() = 0;

private:
    GrafoGnr<Sm> *grafo;

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

template < typename Sm>
void SimuladorGnr<Sm>::simular(int cntItr, int ios, double vsc, double rc, double grc)
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
        /*for (int i = 0; i < grafo->obtTotVrt(); i++)
        {
            NdoVrt nodo2 = (*grafo)[i];
            cout << "Nodo " << i << ": " << nodo2.obtEst() << endl;
        }*/
        cont++;
            }
        else {
             id = rand() % grafo->obtTotVrt();
             }
        }

 //Aca son las iteraciones
    for (int i = 0; i < cntItr; i++)
    {
        for (int j = 0; j < grafo->obtTotVrt(); j++)
        {
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

template < typename Sm >
void SimuladorGnr<Sm>::asignarGrafo(GrafoGnr<Sm>* g)
{
    grafo = g;
}


#endif	/* VISUALIZADORGNR_H */

