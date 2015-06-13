/*
 * File:   Visualizador.cpp
 * Author: Alan
 *
 * Created on 2 de abril de 2015, 07:42 PM
 */

#include "Visualizador.h"
#include <windows.h>
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

Visualizador *Visualizador::ptr;
bool dibujando = false;
char grafostr[] = "No hay grafo cargado! por favor cree o cargue un grafo para visualizar";

Visualizador::Visualizador(const Grafo& g) : grafo(g), simulador(&grafo) {
    cntVrt = grafo.obtTotVrt();
   // vector<int>arrAdy;
    arrAdy.resize(cntVrt);
    //arrAdy = new int [cntVrt];
   // vector <double> posX, posY;
    posX.resize(cntVrt);
    posY.resize(cntVrt);
    //posX = new double [cntVrt];
    //posY = new double [cntVrt];
    hwnd = FindWindow(NULL, "Automata-Celular");
    //ShowWindow(hwnd, SW_HIDE);
    /*this->argc = argc;
    this->argv = argv;*/
    atragantador();
    ptr = this;
}

Visualizador::~Visualizador() {
    ptr = NULL;
}

void Visualizador::visualizar() const {
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

void Visualizador::visualizar(int cItr, int ios, double vsc, double rc, double grc)
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
    do {
        visualizar();
        cin >> line;
        simular();
        SetForegroundWindow(hwnd);
        SetFocus(hwnd);
    } while (line != "salir");
}

void Visualizador::simular()
{
    simulador.simular(info.cItr, info.ios, info.vsc, info.rc, info.grc);
    glutPostRedisplay();
}

double Visualizador::generaPos() {
    double rando = (double) rand() / (double) RAND_MAX;
    double rando2 = (double) rand() / (double) RAND_MAX;
    if (rando2 < 0.5) {
        rando = rando *-1;
    }
    return rando;
}

void Visualizador::atragantador() {
    double generadorX, generadorY;
    for (int i = 0; i < grafo.obtTotVrt(); i++) {
        generadorX = generaPos();//0.2
        generadorY = generaPos();//-0.3
        posX[i] = generadorX;
        posY[i] = generadorY;
    }

    for (int i = 0; i < cntVrt; i++) {
       int cant = grafo.obtCntAdy(i);
        arrAdy[i] = cant;
    }

}

void Visualizador::dibujar_circulo(double radio, double x, double y) {
    glBegin(GL_POLYGON);
    for (double i = 0; i < 2 * 3.1415; i += (3.1415 / 24))
        glVertex2f(x + cos(i) * radio, y + sin(i) * radio);
    glEnd();
}

void Visualizador::linker(int lineas, vector<int>& arrV, int vrt) {
    for (int i = 0; i < lineas; i++) {
        glLineWidth(2.0);
        glColor3f(1.0, 1.0, 1.0); //BLANCO
        glBegin(GL_LINES);
        glVertex2f(posX[vrt], posY[vrt]);
        glVertex2f(posX[arrV[i]], posY[arrV[i]]);
        glEnd();
    }
}

void Visualizador::recurCircles() {
    int cntAdy;
    cntVrt = grafo.obtTotVrt();
    for (int i = 0; i < cntVrt; i++) {
        //int vrt = vrtPopular();
        vector<int> arr;
        grafo.obtAdy(i, arr);
        cntAdy = grafo.obtCntAdy(i);
        linker(cntAdy, arr, i);
    }
    for (int i = 0; i < cntVrt; i++) {
        estadoVrt(i);
        dibujar_circulo(0.02, posX[i], posY[i]);
    }
}

int Visualizador::vrtPopular() {
    int vrtPop, cont = 0;
    while (cont < cntVrt) {
        for (int i = 0; i < cntVrt - 1; i++) {
            if (arrAdy[i] > arrAdy[i + 1]) {
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

void Visualizador::estadoVrt(int vrt) {
    if (grafo.obtEst(vrt) == Grafo::S) {
        glColor3f(0.0, 1.0, 0.0); //Color verde -> vertice suceptible
    }
    if (grafo.obtEst(vrt) == Grafo::I) {
        glColor3f(1.0, 0.0, 0.0); //Color rojo -> vertice infectado
    }
    if (grafo.obtEst(vrt) == Grafo::R) {
        glColor3f(1.0, 0.5, 0.0); //Color naranja-> vertice resistente
    }
}

void Visualizador::keyboard(unsigned char key, int x, int y)
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

void Visualizador::display(void) {
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

void Visualizador::idle(void) {
    if (ptr != NULL)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ptr->recurCircles();
        glutSwapBuffers();
    }
}
