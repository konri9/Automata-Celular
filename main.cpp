/*
 * File:   main.cpp
 * Author: Alan
 *
 * Created on 1 de abril de 2015, 06:52 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>

#include "Parse.h"
#include "GrafoGnr.h"
//#include "NdoVrt.h"
#include "Virus/SimuladorVrs.h"
#include "Virus/VisualizadorVrs.h"
#include "Aves/SimuladorAves.h"
#include "Aves/VisualizadorAves.h"
#ifdef _WIN32 || WIN32
#include <windows.h>
#include <process.h>
#else
#include <pthread.h>
#endif // _WIN32
#include <GL/glut.h>

using namespace std;
using namespace line_parse;

/*
 *
 */

//extern bool dibujando;
int *gargc;
char **gargv;

#ifdef _WIN32 || WIN32
void loopaves(void *arg)
#else
void *loopaves(void *arg)
#endif
{
    GrafoGnr<NdoAve> *grafo = NULL;
    SimuladorAves sv(grafo);
    while (true)
    {
        string linea;
        cout << ">>";
        getline(cin, linea);
        int cant_elementos = cantidad_elementos(linea, ' ');
        if (cant_elementos > 0)
        {
            string prim = parametro(linea, 0, ' ');
            if (prim == "cargar")
            {
                if (cant_elementos == 2)
                {
                    cout << "Cargando grafo...\n";
                    string param = remover_comillas(parametro(linea, 1, ' '));
                    try
                    {
                        if (grafo != NULL) delete grafo;
                        grafo = new GrafoGnr<NdoAve>(param.c_str());
                        cout << "Grafo cargado\n";
                        cout << "Vertices: " << grafo->obtTotVrt() << endl;
                    }
                    catch (int exc)
                    {
                        delete grafo;
                        cout << "Error cargando el grafo\n";
                        grafo = NULL;
                    }
                }
                else
                {
                    cout << "Este comando requiere 2 parametros\n";
                }
            }
            else if (prim == "crear")
            {
                if (cant_elementos == 4)
                {
                    int p1 = elemento(linea, 1, ' ');
                    int p2 = elemento(linea, 2, ' ');
                    int p3 = elemento(linea, 3, ' ');
                    if (p1 >= 1 && p2 >=1 && p3 >= 1 && p3 <= p1*p2)// 0 <= prbAdy < 1
                    {
                        if (grafo != NULL) delete grafo;
                        grafo = new GrafoGnr<NdoAve>(p1, p2, p3);
                        cout << "Grafo creado\n";
                    }
                    else
                    {
                        cout << "Error creando el grafo\n";
                    }
                }
                else
                {
                    cout << "Este comando requiere 2 parametros\n";
                }
            }
            else if (prim == "simular")
            {
                if (cant_elementos == 6)
                {
                    if (grafo != NULL)
                    {
                        int it = elemento(linea, 1, ' '), ios = elemento(linea, 2, ' ');//, vcf = elemento(linea, 4, ' ');
                        double vsc = elemento_double(linea, 3, ' '), rc = elemento_double(linea, 4, ' '), grc = elemento_double(linea, 5, ' ');
                        sv.asignarGrafo(grafo);
                        sv.asignarValores(ios, vsc, rc, grc);
                        sv.setup(ios);
                        sv.go(it);
                    }
                    else
                    {
                        cout << "Error, el grafo no esta creado\n";
                    }
                }
                else
                {
                    cout << "Este comando requiere 5 parametros\n";
                }
            }
            else if (prim == "simular-visualizar")
            {
                if (cant_elementos == 6)
                {
                    if (grafo != NULL)
                    {
                        dibujando = true;
                        VisualizadorAves v(*grafo);
                        int it = elemento(linea, 1, ' '), ios = elemento(linea, 2, ' ');//, vcf = elemento(linea, 4, ' ');
                        double vsc = elemento_double(linea, 3, ' '), rc = elemento_double(linea, 4, ' '), grc = elemento_double(linea, 5, ' ');

                        v.asignarSimulador(&sv);
                        sv.asignarValores(ios, vsc, rc, grc);
                        sv.setup(ios);
                        v.visualizar(it);
                        while (dibujando) {}
                    }
                    else
                    {
                        cout << "Error, el grafo no esta creado\n";
                    }
                }
                else
                {
                    cout << "Este comando requiere 6 parametros\n";
                }
            }
            else if (prim == "visualizar")
            {
                if (cant_elementos == 1)
                {
                    if (grafo != NULL)
                    {
                        dibujando = true;
                        VisualizadorAves v(*grafo);
                        v.visualizar();
                        while (dibujando) {};
                    }
                    else
                    {
                        cout << "Error, el grafo no esta creado\n";
                    }
                }
                else
                {
                    cout << "Este comando no requiere parametros\n";
                }
            }
            else if (prim == "calcular-promedio-longitud-caminos-cortos")
            {
                if (cant_elementos == 1)
                {
                    if (grafo != NULL)
                    {
                        cout << "Promedio: " << grafo->promLongCmnsCrts() << endl;
                    }
                    else
                    {
                        cout << "Error, el grafo no esta creado\n";
                    }
                }
                else
                {
                    cout << "Este comando no requiere parametros\n";
                }
            }
            else if (prim == "calcular-centralidad-intermedial")
            {
                cout << "Este metodo no esta implementado\n";
            }
            else if (prim == "calcular-coeficiente-agrupamiento")
            {
                if (cant_elementos == 2)
                {
                    if (grafo != NULL)
                    {
                        int p1 = elemento(linea, 1, ' ');
                        cout << "Promedio: " << grafo->coeficienteAgrupamiento(p1) << endl;
                    }
                    else
                    {
                        cout << "Error, el grafo no esta creado\n";
                    }
                }
                else
                {
                    cout << "Este comando requiere 1 parametro\n";
                }
            }
            else if (prim == "ayuda")
            {
                if (cant_elementos == 1)
                {
                    cout << "cargar\t" << endl <<
                         "crear\t" << endl <<
                         "simular\t " << endl <<
                         "simular-visualizar\t" << endl <<
                         "visualizar\t" << endl <<
                         "calcular-promedio-longitud-caminos-cortos\t" << endl <<
                         "calcular-centralidad-intermedial\t" << endl <<
                         "calcular-coeficiente-agrupamiento\t" << endl <<
                         "salir" << endl;
                }
                else
                {
                    cout << "Este comando no requiere parametros\n";
                }
            }
            else if (prim == "salir")
            {
#ifdef _WIN32 || WIN32
                HWND hwnd = FindWindow(NULL, "Automata-Celular");
                ShowWindow(hwnd, SW_HIDE);
                CloseHandle(hwnd);
                return;
#else
                return;
#endif
            }
            else
            {
                cout << "Comando incorrecto\n";
            }
        }
    }
}

#ifdef _WIN32 || WIN32
void loopvrs(void *arg)
#else
void *loopvrs(void *arg)
#endif
{
    GrafoGnr<NdoVrs> *grafo = NULL;
    SimuladorVrs sv(grafo);
    while (true)
    {
        string linea;
        cout << ">>";
        getline(cin, linea);
        int cant_elementos = cantidad_elementos(linea, ' ');
        if (cant_elementos > 0)
        {
            string prim = parametro(linea, 0, ' ');
            if (prim == "cargar")
            {
                if (cant_elementos == 2)
                {
                    cout << "Cargando grafo...\n";
                    string param = remover_comillas(parametro(linea, 1, ' '));
                    try
                    {
                        if (grafo != NULL) delete grafo;
                        grafo = new GrafoGnr<NdoVrs>(param.c_str());
                        cout << "Grafo cargado\n";
                        cout << "Vertices: " << grafo->obtTotVrt() << endl;
                    }
                    catch (int exc)
                    {
                        delete grafo;
                        cout << "Error cargando el grafo\n";
                        grafo = NULL;
                    }
                }
                else
                {
                    cout << "Este comando requiere 2 parametros\n";
                }
            }
            else if (prim == "crear")
            {
                if (cant_elementos == 3)
                {
                    int p1 = elemento(linea, 1, ' ');
                    double p2 = elemento_double(linea, 2, ' ');
                    cout << p2;
                    if (p1 >= 10 && p2 <1 )// 0 <= prbAdy < 1
                    {
                        if (grafo != NULL) delete grafo;
                        grafo = new GrafoGnr<NdoVrs>(p1, p2);
                        cout << "Grafo creado\n";
                    }
                    else
                    {
                        cout << "Error creando el grafo\n";
                    }
                }
                else
                {
                    cout << "Este comando requiere 2 parametros\n";
                }
            }
            else if (prim == "simular")
            {
                if (cant_elementos == 6)
                {
                    if (grafo != NULL)
                    {
                        int it = elemento(linea, 1, ' '), ios = elemento(linea, 2, ' ');//, vcf = elemento(linea, 4, ' ');
                        double vsc = elemento_double(linea, 3, ' '), rc = elemento_double(linea, 4, ' '), grc = elemento_double(linea, 5, ' ');
                        sv.asignarGrafo(grafo);
                        sv.asignarValores(ios, vsc, rc, grc);
                        sv.setup(ios);
                        sv.go(it);
                    }
                    else
                    {
                        cout << "Error, el grafo no esta creado\n";
                    }
                }
                else
                {
                    cout << "Este comando requiere 5 parametros\n";
                }
            }
            else if (prim == "simular-visualizar")
            {
                if (cant_elementos == 6)
                {
                    if (grafo != NULL)
                    {
                        dibujando = true;
                        VisualizadorVrs v(*grafo);
                        int it = elemento(linea, 1, ' '), ios = elemento(linea, 2, ' ');//, vcf = elemento(linea, 4, ' ');
                        double vsc = elemento_double(linea, 3, ' '), rc = elemento_double(linea, 4, ' '), grc = elemento_double(linea, 5, ' ');

                        v.asignarSimulador(&sv);
                        sv.asignarValores(ios, vsc, rc, grc);
                        sv.setup(ios);
                        v.visualizar(it);
                        while (dibujando) {}
                    }
                    else
                    {
                        cout << "Error, el grafo no esta creado\n";
                    }
                }
                else
                {
                    cout << "Este comando requiere 6 parametros\n";
                }
            }
            else if (prim == "visualizar")
            {
                if (cant_elementos == 1)
                {
                    if (grafo != NULL)
                    {
                        dibujando = true;
                        VisualizadorVrs v(*grafo);
                        v.visualizar();
                        while (dibujando) {};
                    }
                    else
                    {
                        cout << "Error, el grafo no esta creado\n";
                    }
                }
                else
                {
                    cout << "Este comando no requiere parametros\n";
                }
            }
            else if (prim == "calcular-promedio-longitud-caminos-cortos")
            {
                if (cant_elementos == 1)
                {
                    if (grafo != NULL)
                    {
                        cout << "Promedio: " << grafo->promLongCmnsCrts() << endl;
                    }
                    else
                    {
                        cout << "Error, el grafo no esta creado\n";
                    }
                }
                else
                {
                    cout << "Este comando no requiere parametros\n";
                }
            }
            else if (prim == "calcular-centralidad-intermedial")
            {
                cout << "Este metodo no esta implementado\n";
            }
            else if (prim == "calcular-coeficiente-agrupamiento")
            {
                if (cant_elementos == 2)
                {
                    if (grafo != NULL)
                    {
                        int p1 = elemento(linea, 1, ' ');
                        cout << "Promedio: " << grafo->coeficienteAgrupamiento(p1) << endl;
                    }
                    else
                    {
                        cout << "Error, el grafo no esta creado\n";
                    }
                }
                else
                {
                    cout << "Este comando requiere 1 parametro\n";
                }
            }
            else if (prim == "ayuda")
            {
                if (cant_elementos == 1)
                {
                    cout << "cargar\t" << endl <<
                         "crear\t" << endl <<
                         "simular\t " << endl <<
                         "simular-visualizar\t" << endl <<
                         "visualizar\t" << endl <<
                         "calcular-promedio-longitud-caminos-cortos\t" << endl <<
                         "calcular-centralidad-intermedial\t" << endl <<
                         "calcular-coeficiente-agrupamiento\t" << endl <<
                         "salir" << endl;
                }
                else
                {
                    cout << "Este comando no requiere parametros\n";
                }
            }
            else if (prim == "salir")
            {
#ifdef _WIN32 || WIN32
                HWND hwnd = FindWindow(NULL, "Automata-Celular");
                ShowWindow(hwnd, SW_HIDE);
                CloseHandle(hwnd);
                return;
#else
                return;
#endif
            }
            else
            {
                cout << "Comando incorrecto\n";
            }
        }
    }
}

int main(int argc, char** argv)
{
    cout << "Automata Celular\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(750, 500);
    int winPos = glutGet(GLUT_SCREEN_WIDTH) / 2;
    winPos = 750 / 2;
    glutInitWindowPosition(winPos, 0);
    glutCreateWindow("Automata-Celular");
    cout << "Escoja el tipo de simulacion:\n1-Virus\n2-Aves\n";
    int ch = 1;
    cin >> ch;
    switch (ch)
    {
    case 1:
        glutDisplayFunc(VisualizadorVrs::display);
        glutKeyboardFunc(VisualizadorVrs::keyboard);
    case 2:
        glutDisplayFunc(VisualizadorAves::display);
        glutKeyboardFunc(VisualizadorAves::keyboard);
    }
#ifdef _WIN32 || WIN32
    switch (ch)
    {
    default:
    case 1:
        _beginthread(loopvrs, 0, (void*)0 );
        break;
    case 2:
        _beginthread(loopaves, 0, (void*)0 );
        break;
    }
#else // _WIN32
    int banano = 0;
    pthread_t thread;
    switch (ch)
    {
    default:
    case 1:
        pthread_create(&thread, NULL, loopvrs, &banano);
        break;
    case 2:
        pthread_create(&thread, NULL, loopaves, &banano);
        break;
    }
#endif
    glutMainLoop();
    return 0;
}

