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
//#include <windows.h>
#include <process.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <string>
#include <algorithm> //max element


#ifndef NULL
#define NULL 0
#endif

using namespace std;


// Vslzdr es el tipo de vértice.
template < typename Vsz >
class VisualizadorGnr
{
    // Representa la red compleja sobre la cual se desarrollará la simulación.

public:
    Visualizador(const Grafo& g);
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
    void visualizar(int cItr, int ios, double vsc, int vcf, double rc, double grc);

private:
    Grafo grafo;

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
    void recurCircles ();

    /*Revisa toda la lista de adyacencia y devuelve el indice del vertice con mas adyacencias*/
    int vrtPopular();

    //EFE:
    //REQ:
    void asignaColor();

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

    int *arrAdy = NULL;
    Simulador simulador;

    struct infosim
    {
        int cItr, ios, vcfmax;
        double vsc, rc, grc;
    };

    HWND hwnd;

    bool sim = false;
    infosim info;
};


VisualizadorGnr *Visualizador::ptr;
bool dibujando = false;
char grafostr[] = "No hay grafo cargado! por favor cree o cargue un grafo para visualizar";

template < typename Vsz >
VisualizadorGnr< V >::VisualizadorGnr

template < typename Vsz >
VisualizadorGnr::Visualizador(const Grafo& g) : grafo(g), simulador(&grafo)
{
    cntVrt = grafo.obtTotVrt();
    arrAdy.resize(cntVrt);
    posX.resize(cntVrt);
    posY.resize(cntVrt);
    hwnd = FindWindow(NULL, "Automata-Celular");
    /*this->argc = argc;
    this->argv = argv;*/
    atragantador();
    //ShowWindow(hwnd, SW_HIDE);
    ptr = this;
}

template < typename Vsz >
VisualizadorGnr::~Visualizador()
{
    ptr = NULL;
}

template < typename Vsz >
void VisualizadorGnr::visualizar() const
{
    //glutCreateWindow("Automata-Celular @tete94 @konri9");
    /*glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(750, 500);
    int winPos = glutGet(GLUT_SCREEN_WIDTH) / 2;
    winPos = 750 / 2;
    glutInitWindowPosition(winPos, 0);
    glutCreateWindow("Automata-Celular @tete94 @konri9");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();*/
    /*glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);*/
    glutPostRedisplay();
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
}

template < typename Vsz >
void VisualizadorGnr::visualizar(int cItr, int ios, double vsc, double rc, double grc)
{
    simulador.simular(cItr, ios, vsc, rc, grc);
    sim = true;
    info.cItr = cItr;
    info.grc = grc;
    info.ios = ios;
    info.rc = rc;
    //info.vcf = vcf;
    //info.vcfmax = vcf;
    info.vsc = vsc;
    string line = "";
    cout << "Digite cualquier caracter y presione enter para realizar una iteracion\nO bien, presione enter en la ventana del grafo para realizar una iteracion\nEscriba \"salir\" para terminar la simulacion\n";
    do
    {
        visualizar();
        cin >> line;
        simular();
        SetForegroundWindow(hwnd);
        SetFocus(hwnd);
    }
    while (line != "salir");
}

template < typename Vsz >
void VisualizadorGnr::simular()
{
    simulador.simular(info.cItr, info.ios, info.vsc, info.rc, info.grc);
    glutPostRedisplay();
}

template < typename Vsz >
double VisualizadorGnr::generaPos()
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
void VisualizadorGnr::atragantador()
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
void VisualizadorGnr::dibujar_circulo(double radio, double x, double y)
{
    glBegin(GL_POLYGON);
    for (double i = 0; i < 2 * 3.1415; i += (3.1415 / 24))
        glVertex2f(x + cos(i) * radio, y + sin(i) * radio);
    glEnd();
}

template < typename Vsz >
void VisualizadorGnr::linker(int lineas, vector<int>& arrV, int vrt)
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
void VisualizadorGnr::recurCircles()
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
int VisualizadorGnr::vrtPopular()
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
void VisualizadorGnr::estadoVrt(int vrt)
{
    if (grafo.obtEst(vrt) == Grafo::S)
    {
        glColor3f(0.0, 1.0, 0.0); //Color verde -> vertice suceptible
    }
    if (grafo.obtEst(vrt) == Grafo::I)
    {
        glColor3f(1.0, 0.0, 0.0); //Color rojo -> vertice infectado
    }
    if (grafo.obtEst(vrt) == Grafo::R)
    {
        glColor3f(1.0, 0.5, 0.0); //Color naranja-> vertice resistente
    }
}

template < typename Vsz >
void VisualizadorGnr::keyboard(unsigned char key, int x, int y)
{
    if (ptr == NULL) return;
    if (ptr->sim)
    {
        if (key == 13)
        {
            ptr->info.ios = 0;
            ptr->info.vcf--;
            if (ptr->info.vcf < 0) ptr->info.vcf = ptr->info.vcfmax;
            ptr->simular();
        }
    }
}

template < typename Vsz >
void VisualizadorGnr::display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (ptr != NULL)
    {
        ptr->recurCircles();
        glutSwapBuffers();
        dibujando = false;
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
void VisualizadorGnr::idle(void)
{
    if (ptr != NULL)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ptr->recurCircles();
        glutSwapBuffers();
    }
}



#endif	/* VISUALIZADORGNR_H */

