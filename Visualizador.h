/*
 * File:   Visualizador.h
 * Author: Alan
 *
 * Created on 2 de abril de 2015, 07:42 PM
 */

#ifndef VISUALIZADOR_H
#define	VISUALIZADOR_H

//#include <windows.h>

#include <memory>
using namespace std;

#include "GrafoGnr.h"
#include "Simulador.h"
#include"NdoVrt.h"

class Visualizador {
    // Permite la visualizaci�n gr�fica de una instancia de Grafo.

public:
    Visualizador(const GrafoGnr<NdoVrt>& g);
    ~Visualizador();

    // REQ: que el grafo asociado en el constructor est� bien construido.
    // EFE: muestra gr�ficamente al grafo asociado diferenciando con distintos
    //      colores los estados de los v�rtices.
    void visualizar() const;

    // REQ: *this haya sido construido con un grafo y un simulador asociado.
    // MOD: el grafo asociado por medio del simulador miembro.
    // EFE: aplica al grafo asociado cntItr transformaciones con base en los
    //      siguientes par�metros (por medio del simulador asociado):
    //      cItr > 1000: cantidad de iteraciones.
    //      ios o initial-outbreak-size [1..N], N cantidad de v�rtices: cantidad
    //           de v�rtices infectados al comienzo de la simulaci�n.
    //      vsc o virus-spread-chance [0..0.1]: probabilidad de infecci�n.
    //      vcf o virus-check-frecuency [1..20]: frecuencia de chequeo antivirus.
    //      rc o recovery-chance [0..0.1]: probabilidad de recuperaci�n de infecci�n.
    //      grc o gain-resistance-chance [0..1]: probabilidad de lograr resistencia.
    //      Aplica la siguiente regla de cambio de estado para los v�rtices:
    //      1. un v�rtice s�lo puede ser infectado por alguno de sus vecinos infectados
    //         con probabilidad vsc.
    //      2. s�lo un v�rtice infectado cuyo temporizador de chequeo de virus est� en cero
    //         puede recuperarse con probabilidad rc.
    //      3. s�lo un v�rtice recuperado puede ganar resistencia con probabilidad grc.
    //      4. S�lo las transformaciones #2 y #3 pueden ser simult�neas.
    // EFE: muestra gr�ficamente al grafo asociado diferenciando con distintos
    //      colores los estados de los v�rtices.
    void visualizar(int cItr, int ios, double vsc, double rc, double grc);

private:
    GrafoGnr<NdoVrt> grafo;

    void simular();

    /*Estos son mis metodos*/

    /*Genera una posicion aleatoria para las coordenadas)*/
    double generaPos();

    /* Rellena los vectores con valores generados al azar*/
    void atragantador();

    /*Dibuja un circulo a partir del radio y las coordenadas*/
    void dibujar_circulo(double radio, double x, double y);

    /*Genera las lineas entre vertices*/
    void linker(int lineas, vector<int>& arrV, int vrt);

    /*Dibuja los circulos, basandose en las posiciones ya generadas */
    void recurCircles ();

    /*Revisa toda la lista de adyacencia y devuelve el indice del vertice con mas adyacencias*/
    int vrtPopular();

    /*Asigna el color al circulo, dependiendo de su estado*/
    void estadoVrt(int vrt);

    /*Tipo de main para las figuras*/
    public:
    static void display(void);
    static void idle(void);
    static void keyboard(unsigned char key, int x, int y);
    static Visualizador *ptr;

    int *argc;
    char **argv;

    /*Variables globales que contienen las posiciones asignadas*/
    int cntVrt = 0;
    vector <int> arrAdy;
    vector<double>posX, posY;

   // double *posX = NULL;// vector con las posiciones en X
    //double *posY = NULL;// vector con las posiciones en Y
    //int numVrt = grafo.obtTotVrt();
    //int *arrAdy = NULL;
    Simulador simulador;

    struct infosim{
        int cItr, ios, vcfmax;
        double vsc, rc, grc;
    };

    #ifdef _WIN32 || WIN32
    HWND hwnd;
    #endif

    bool sim = false;
    infosim info;
};

#endif	/* VISUALIZADOR_H */

