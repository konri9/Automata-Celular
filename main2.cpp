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
#include "NdoVrt.h"
#include "SimuladorGnr.h"
#include "SimuladorVrs.h"
#include "VisualizadorGnr.h"
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

template <typename V>
class NuevoSimulador : public SimuladorGnr<V>
{
public:
    NuevoSimulador()
    {

    };

    void go()
    {

    };

    void setup()
    {

    };
};

extern bool dibujando;
int *gargc;
char **gargv;

#ifdef _WIN32 || WIN32
void loop(void *arg)
#else
void *loop(void *arg)
#endif
{
    GrafoGnr<NdoVrt> *grafo = NULL;
    SimuladorVrs<NdoVrt> sv(grafo);
    cout << "Automata Celular\n";
    while (true)
    {
        string linea;
        cout << ">>";
        getline(cin, linea);
        int cant_elementos = cantidad_elementos(linea, ' ');
        if (cant_elementos > 0)
        {
            string prim = parametro(linea, 0, ' ');

            if (prim == "red de virus")
            {
                getline(cin, linea);
                string prin = parametro(linea,0.' ');
                parserVrs(prin);
            }
            else if (prim == "red de aves")
            {
                getline(cin, linea);
                string prin = parametro(linea,0.' ');
                parserAves(prin);
            }

        }
    }
}



void parserVrs(string prim)
{
    if (prim == "cargar")
    {
        if (cant_elementos == 2)
        {
            cout << "Cargando grafo...\n";
            string param = remover_comillas(parametro(linea, 1, ' '));
            try
            {
                if (grafo != NULL) delete grafo;
                grafo = new GrafoGnr<NdoVrt>(param.c_str());
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
            double p2 = elemento(linea, 2, ' ');
            if (p1 >= 10 && p2 <1 )// 0 <= prbAdy < 1
            {
                if (grafo != NULL) delete grafo;
                grafo = new GrafoGnr<NdoVrt>(p1, p2);
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
                SimuladorVrs<NdoVrt> s(grafo);
                s.simular(it, ios, vsc, rc, grc);
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
                VisualizadorGnr<NdoVrt> v(*grafo);
                int it = elemento(linea, 1, ' '), ios = elemento(linea, 2, ' ');//, vcf = elemento(linea, 4, ' ');
                double vsc = elemento_double(linea, 3, ' '), rc = elemento_double(linea, 4, ' '), grc = elemento_double(linea, 5, ' ');
                //   sv.simular(it, ios, vsc, rc, grc);

                v.visualizar(it, ios, vsc, rc, grc);
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
                VisualizadorGnr<NdoVrt> v(*grafo);
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
            cout << "cargar\t-carga el grafo a partir del parametro %nArch" << endl <<
                 "crear\t-crea el grafo a partir de dos parametros" << endl <<
                 "simular\t " << endl <<
                 "simular-visualizar\t-fjasklf" << endl <<
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
        return 0;
#endif
    }
    else
    {
        cout << "Comando incorrecto\n";
    }
}


void parserAves(string prim)
{
    if (prim == "cargar")
    {
        if (cant_elementos == 2)
        {
            cout << "Cargando grafo...\n";
            string param = remover_comillas(parametro(linea, 1, ' '));
            try
            {
                if (grafo != NULL) delete grafo;
                grafo = new GrafoGnr<NdoVrt>(param.c_str());
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
            double p2 = elemento(linea, 2, ' ');
            if (p1 >= 10 && p2 <1 )// 0 <= prbAdy < 1
            {
                if (grafo != NULL) delete grafo;
                grafo = new GrafoGnr<NdoVrt>(p1, p2);
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
                SimuladorVrs<NdoVrt> s(grafo);
                s.simular(it, ios, vsc, rc, grc);
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
                VisualizadorGnr<NdoVrt> v(*grafo);
                int it = elemento(linea, 1, ' '), ios = elemento(linea, 2, ' ');//, vcf = elemento(linea, 4, ' ');
                double vsc = elemento_double(linea, 3, ' '), rc = elemento_double(linea, 4, ' '), grc = elemento_double(linea, 5, ' ');
                //   sv.simular(it, ios, vsc, rc, grc);

                v.visualizar(it, ios, vsc, rc, grc);
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
                VisualizadorGnr<NdoVrt> v(*grafo);
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
            cout << "cargar\t-carga el grafo a partir del parametro %nArch" << endl <<
                 "crear\t-crea el grafo a partir de dos parametros" << endl <<
                 "simular\t " << endl <<
                 "simular-visualizar\t-fjasklf" << endl <<
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
        return 0;
#endif
    }
    else
    {
        cout << "Comando incorrecto\n";
    }
}



int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(750, 500);
    int winPos = glutGet(GLUT_SCREEN_WIDTH) / 2;
    winPos = 750 / 2;
    glutInitWindowPosition(winPos, 0);
    glutCreateWindow("Automata-Celular");
    glutDisplayFunc(VisualizadorGnr<NdoVrt>::display);
    //glutIdleFunc(Visualizador::idle);
    glutKeyboardFunc(VisualizadorGnr<NdoVrt>::keyboard);
#ifdef _WIN32 || WIN32
    _beginthread(loop, 0, (void*)0 );
#else // _WIN32
    int bn = 0;
    pthread_t thread;
    pthread_create(&thread, NULL, loop, &bn);
#endif
    glutMainLoop();
    return 0;
}

