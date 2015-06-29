/*
 * File:   GrafoGnr.h
 * Author: alan.calderon
 *
 * Created on 4 de junio de 2015, 05:49 PM
 */

#ifndef VISUALIZADORGNR_H
#define	VISUALIZADORGNR_H


#include "GrafoGnr.h"
#include "SimuladorGnr.h"

#ifdef _WIN32 || WIN32
#include <windows.h>
#include <process.h>
#endif


#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <string>
#include <algorithm> //max element
#include "VerticeGnr.h"


#ifndef NULL
#define NULL 0
#endif

using namespace std;

extern bool dibujando;
extern char grafostr[];

// Vslzdr es el tipo de vértice.
template < typename Vsz >
class VisualizadorGnr
{
    // Representa la red compleja sobre la cual se desarrollará la simulación.

public:
    VisualizadorGnr(const GrafoGnr<Vsz>& g);
    ~VisualizadorGnr();

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
    void visualizar(int cItr);
    GrafoGnr<Vsz> *obtGrafo() { return &grafo;};
    void asignarSimulador(SimuladorGnr<Vsz> *sim) { simulador = sim; simulador->asignarGrafo(&grafo);};

//hacer un metodo virtual puro que asigne el color
//si pero eso en visualizador
    //REQ:
    //EFE:
    virtual void asignaColor() = 0;

private:
    GrafoGnr<Vsz> grafo;

    void simular();

    /*Estos son mis metodos*/

    /*Genera una posicion aleatoria para las coordenadas)*/

    //EFE:
    //REQ:
    double generaPos();

    /* Rellena los vectores con valores generados al azar*/

    //EFE:
    //REQ:
    void atragantador();

    /*Dibuja un circulo a partir del radio y las coordenadas*/

    //EFE:
    //REQ:
    void dibujar_circulo(double radio, double x, double y);

    /*Genera las lineas entre vertices*/

    //EFE:
    //REQ:
    void linker(int lineas, vector<int>& arrV, int vrt);

    /*Dibuja los circulos, basandose en las posiciones ya generadas */

    //EFE:
    //REQ:
    virtual void recurCircles();

    /*Revisa toda la lista de adyacencia y devuelve el indice del vertice con mas adyacencias*/
    int vrtPopular();

    //EFE: Asigna colores dependiendo del estado del vertice del grafo
    //REQ:

    /*Asigna el color al circulo, dependiendo de su estado*/
    void estadoVrt(int vrt);

    /*Tipo de main para las figuras*/
public:
    static void display(void);
    static void idle(void);
    static void keyboard(unsigned char key, int x, int y);
    static VisualizadorGnr *ptr;

    int *argc;
    char **argv;

    /*Variables globales que contienen las posiciones asignadas*/
    int cntVrt = 0;
    vector <int> arrAdy;
    vector<double>posX, posY;

    SimuladorGnr<Vsz> *simulador;

#ifdef _WIN32 || WIN32
    HWND hwnd;
#endif

    bool sim = false;
};

template < typename Vsz >
VisualizadorGnr<Vsz> *VisualizadorGnr<Vsz>::ptr;

template < typename Vsz >
VisualizadorGnr<Vsz>::VisualizadorGnr(const GrafoGnr<Vsz>& g) : grafo(g)
{
    cntVrt = grafo.obtTotVrt();
    arrAdy.resize(cntVrt);
    posX.resize(cntVrt);
    posY.resize(cntVrt);
#ifdef _WIN32 || WIN32
    hwnd = FindWindow(NULL, "Automata-Celular");
    //ShowWindow(hwnd, SW_HIDE);
#endif
    /*this->argc = argc;
    this->argv = argv;*/
    atragantador();
    ptr = this;
}

template < typename Vsz >
VisualizadorGnr<Vsz>::~VisualizadorGnr()
{
    ptr = NULL;
}

template < typename Vsz >
void VisualizadorGnr<Vsz>::visualizar() const
{
#ifdef _WIN32 || WIN32
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
#endif
    glutPostRedisplay();
}

template < typename Vsz >
void VisualizadorGnr<Vsz>::visualizar(int cItr)
{
    simulador->go(cItr);
    sim = true;
    string line = "";
    cout << "Digite cualquier caracter y presione enter para realizar una iteracion\nO bien, presione enter en la ventana del grafo para realizar una iteracion\nEscriba \"salir\" para terminar la simulacion\n";
    do
    {
        visualizar();
        cin >> line;
        simular();
#ifdef _WIN32 || WIN32
        SetForegroundWindow(hwnd);
        SetFocus(hwnd);
#endif // _WIN32
    }
    while (line != "salir");
}

template < typename Vsz >
void VisualizadorGnr<Vsz>::simular()
{
    simulador->go(1);
    glutPostRedisplay();
}

template < typename Vsz >
double VisualizadorGnr<Vsz>::generaPos()
{
    double rando = (double) rand() / (double) RAND_MAX;
    double rando2 = (double) rand() / (double) RAND_MAX;
    if (rando2 < 0.5)
    {
        rando = rando *-1;
    }
    return rando;
}

template < typename Vsz >
void VisualizadorGnr<Vsz>::atragantador()
{
    double generadorX, generadorY;
    for (int i = 0; i < grafo.obtTotVrt(); i++)
    {
        generadorX = generaPos();//0.2
        generadorY = generaPos();//-0.3
        posX[i] = generadorX;
        posY[i] = generadorY;
    }

    for (int i = 0; i < cntVrt; i++)
    {
        int cant = grafo.obtCntAdy(i);
        arrAdy[i] = cant;
    }

}

template < typename Vsz >
void VisualizadorGnr<Vsz>::dibujar_circulo(double radio, double x, double y)
{
    glBegin(GL_POLYGON);
    for (double i = 0; i < 2 * 3.1415; i += (3.1415 / 24))
        glVertex2f(x + cos(i) * radio, y + sin(i) * radio);
    glEnd();
}

template < typename Vsz >
void VisualizadorGnr<Vsz>::linker(int lineas, vector<int>& arrV, int vrt)
{
    for (int i = 0; i < lineas; i++)
    {
        glLineWidth(2.0);
        glColor3f(1.0, 1.0, 1.0); //BLANCO
        glBegin(GL_LINES);
        glVertex2f(posX[vrt], posY[vrt]);
        glVertex2f(posX[arrV[i]], posY[arrV[i]]);
        glEnd();
    }
}

template < typename Vsz >
void VisualizadorGnr<Vsz>::recurCircles()
{
    int cntAdy;
    cntVrt = grafo.obtTotVrt();
    for (int i = 0; i < cntVrt; i++)
    {
        //int vrt = vrtPopular();
        vector<int> arr;
        grafo.obtAdy(i, arr);
        cntAdy = grafo.obtCntAdy(i);
        linker(cntAdy, arr, i);
    }
    for (int i = 0; i < cntVrt; i++)
    {
        estadoVrt(i);
        dibujar_circulo(0.02, posX[i], posY[i]);
    }
}

template < typename Vsz >
int VisualizadorGnr<Vsz>::vrtPopular()
{
    int vrtPop, cont = 0;
    while (cont < cntVrt)
    {
        for (int i = 0; i < cntVrt - 1; i++)
        {
            if (arrAdy[i] > arrAdy[i + 1])
            {
                vrtPop = i;
            }
            else
            {
                vrtPop = i+1;
            }
        }
        cont++;
    }
    arrAdy[vrtPop] = 0;
    return vrtPop;
}

template < typename Vsz >
void VisualizadorGnr<Vsz>::estadoVrt(int vrt)
{
    VerticeGnr *ver = &grafo[vrt];
    Vector3 vec = ver->obtColor();
    glColor3f(vec.x, vec.y, vec.z);
}

template < typename Vsz >
void VisualizadorGnr<Vsz>::keyboard(unsigned char key, int x, int y)
{
    if (ptr == NULL) return;
    if (ptr->sim)
    {
        if (key == 13)
        {
            //ptr->info.vcf--;
            //if (ptr->info.vcf < 0) ptr->info.vcf = ptr->info.vcfmax;
            ptr->simular();
        }
    }
}

template < typename Vsz >
void VisualizadorGnr<Vsz>::display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (ptr != NULL)
    {
        ptr->recurCircles();
        dibujando = false;
        glutSwapBuffers();
        return;
        //if (!ptr->sim) ptr = NULL;
    }
    else
    {
        //Escribe texto en la pantalla
        glColor3d(1.0, 0.0, 0.0);
        unsigned int len = strlen(grafostr);
        double width = 0;
        for (unsigned int i = 0; i < len; i++)
        {
            width += glutBitmapWidth(GLUT_BITMAP_9_BY_15, grafostr[i]);
        }
        width = width / (double)glutGet(GLUT_WINDOW_WIDTH);
        glRasterPos2d(-width, 0);
        for (unsigned int i = 0; i < len; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, grafostr[i]);
        }
    }
    glutSwapBuffers();
}

template < typename Vsz >
void VisualizadorGnr<Vsz>::idle(void)
{
    if (ptr != NULL)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ptr->recurCircles();
        glutSwapBuffers();
    }
}

#endif	/* VISUALIZADORGNR_H */
