/*
 * File:   GrafoGnr.h
 * Author: alan.calderon
 *
 * Created on 4 de junio de 2015, 05:49 PM
 */

#ifndef GRAFOGNR_H
#define	GRAFOGNR_H

#include "Parse.h"

#include <chrono>
#include <memory>
#include <string>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include <limits> // std::numeric_limits

#ifndef NULL
#define NULL 0
#endif // NULL

using namespace std;
using namespace line_parse;


// V es el tipo de vértice.
template < typename V >
class GrafoGnr
{
    // Representa la red compleja sobre la cual se desarrollará la simulación.

public:

    enum E  // representa el tipo de estados de la red de infección
    {
        S, // representa un vértice susceptible de infección
        I, // representa un vértice infectado
        R, // representa un vértice resistente
    };

    /* CONSTRUCTORES */
    // REQ: ( cntVrt >= 10 ) && ( 0 <= prbAdy < 1  )
    // Construye una red al azar no vacía. La probabilidad de que exista una adyacencia (i,j) es prbAdy.
    GrafoGnr(int cntVrt, double prbAdy);

    // Construye una copia idéntica a orig.
    GrafoGnr(const GrafoGnr< V >& orig);

    // Construye una red con base en los datos en el archivo de nombre nArch.
    // El archivo debe ser *.txt con datos separados por comas.
    // En la primera línea aparecerá un entero que representa la cantidad de vértices.
    // Luego en cada línea aparecerá primero el estado de un vértice y las posiciones
    // de los adyacentes, todo separado por comas.
    GrafoGnr(string nArch);

    // Destruye a *this retornando toda la memoria asignada dinámicamente.
    ~GrafoGnr();

    /* MÉTODOS OBSERVADORES BÁSICOS */

    // EFE: retorna true si existe un vértice con índice vrt.
    bool xstVrt(int vrt) const;

    // REQ: existan en *this vértices con índices vrtO y vrtD.
    // EFE: retorna true si existe un arco entre los vértices con índice vrtO y vrtD.
    bool xstAdy(int vrtO, int vrtD) const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna un vector de enteros con las posiciones de los vértices
    //      adyacentes al vértice indicado por vrt.
    int obtTotVrt();


    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna un vector de enteros con las posiciones de los vértices
    //      adyacentes al vértice indicado por vrt.
    void obtAdy(int vrt, vector<int>& vec)const;


    // EFE: retorna el total de vértices en *this.
    int obtTotVrt() const;

    // EFE: retorna el total de adyacencias en *this.
    int obtTotAdy() const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el vértice con índice vrt.
    V& operator[](int vrt);

    // EFE: retorna true si *this == o, false en caso contrario.
    bool operator==(const GrafoGnr& o) const;

    /* MÉTODOS OBSERVADORES ESPECIALES */

    // EFE: retorna el promedio de las longitudes de los caminos más cortos
    //      entre cada pareja de vértices de *this.
    double promLongCmnsCrts() const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el "local clustering coefficient" o coeficiente local de agrupamiento
    //      para el vértice indicado por vrt.
    //      La definición aparece en: http://en.wikipedia.org/wiki/Clustering_coefficient
    //      Se calcula como el cociente entre la cantidad efectiva de arcos entre los
    //      vecinos del vértice indicado por vrt dividida por la cantidad total de posibles
    //      arcos entre todos los vecinos del vértice indicado por vrt.
    double coeficienteAgrupamiento(int vrt) const;

    int **Floyd_Warshall() const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el estado del vértice con índice vrt.
    E obtEst(int vrt) const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el valor del temporizador de chequeo de antivirus del vértice con índice vrt.
    int obtTmpChqVrs(int vrt) const;

    // REQ: que exista en *this un vértice con índice vrt.
    // EFE: retorna el valor del contador de chequeo de antivirus del vértice con índice vrt.
    int obtCntChVrs(int vrt) const;


    /* MÉTODOS MODIFICADORES */

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: cambia el estado del vértice cuyo índice es vrt a ne.
    void modEst(int vrt, E ne);

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: cambia el valor del temporizador de chequeo de virus del vértice vrt por el valor nt.
    void modTmpChqVrs(int vrt, int nt);

    // REQ: que exista en *this un vértice con índice vrt.
    // MOD: *this.
    // EFE: actualiza el valor del contador de chequeo de virus para la siguiente iteración.
    void actCntChqVrs(int vrt);

    // REQ: ios << this->obtTotVrt().
    // MOD: *this.
    // EFE: cambia el estado a I (infectado) a ios vértices escogidos al azar.
    //      ios o initial-outbreak-size: cantidad inicial de nodos infectados.
    void infectar(int ios);

    // MOD: *this
    // EFE: asigna el valor del temporizador para cada vértice con un número al azar entre 1 y maxTmp.
    //      vcf o virus-check-frecuency: frecuencia máxima de chequeo antivirus.
    void azarizarTmpChqVrs(int vcf);

    int **Floyd_Warshall();

private:
    struct NdoVrt
    {
        V vrt;
        E e; // representa el estado del vértice
        int tmpChqVrs; // representa el temporizador de chequeo de virus
        int cntChqVrs; // representa el contador de chequeo de virus: va de 0 a tmpChqVrs
        NdoVrt(): e(S), tmpChqVrs(1) {};
        vector <int> lstAdy;

    };
    // Escoja entre <vector>, <list> y <forward_list> para representar la lista de adyacencias del vértice.

    int cntVrt; // representa la cantidad total de vértices
    int vcf = 5;
    double prmAdy;
    vector<NdoVrt>arrVrt;// Escoja entre <vector>, <map> y <unordered_map> en lugar del arreglo de nodos de vértices.


};

template < typename V >
GrafoGnr< V >::GrafoGnr(int cntVrt, double prbAdy)
{
    if ((cntVrt >= 10) && (0 <= prbAdy < 1))
    {
        {
            this->cntVrt = cntVrt;
            arrVrt.resize(cntVrt);
            srand(time(NULL));
            default_random_engine generador(rand());
            normal_distribution<double> distribucion(prbAdy, 2.0);
            for (int i = 0; i < this->cntVrt; i++)
            {
                arrVrt[i].tmpChqVrs = 0;

                arrVrt[i].cntChqVrs = 0;
                int rnum = distribucion(generador);
                if (!xstAdy(i, rnum) && xstVrt(rnum))
                {
                    arrVrt[i].lstAdy.push_back(rnum);
                    arrVrt[rnum].lstAdy.push_back(i);
                }
            }
            azarizarTmpChqVrs(vcf);
        }
       return;
       throw 1;
    }
}


    template < typename V >
    GrafoGnr< V >::GrafoGnr(const GrafoGnr< V >& orig)
    {
        if (orig.cntVrt > 0)
        {
            this->cntVrt = orig.cntVrt;
            arrVrt.resize(this->cntVrt);
            for (int i = 0; i < this->cntVrt; i++)
            {
                arrVrt[i].e = orig.obtEst(i);
                arrVrt[i].tmpChqVrs = orig.obtTmpChqVrs(i);
                arrVrt[i].cntChqVrs = orig.arrVrt[i].cntChqVrs;
                for (int j = 0; j < orig.arrVrt[i].lstAdy.size(); j++)
                    arrVrt[i].lstAdy.push_back(orig.arrVrt[i].lstAdy[j]);
            }
            return;
            throw 1;
        }
    }

    template < typename V >
    GrafoGnr< V >::GrafoGnr(string nArch)
    {
        ifstream file;
        file.open(nArch.c_str(), ios::in);
        if (file.is_open() && file.good())
        {
            char line[256];
            memset(&line, 0, 256);//poner memoria en 0
            file.getline(line, 256); //primera linea
            string inits = line;
            cntVrt = totalDeVertices(inits);
            prmAdy = promedioAdy(inits);
            if (cntVrt < 0) return; // error
            arrVrt.resize(cntVrt);
            int count = 0;
            while (!file.eof() && count < cntVrt)
            {
                memset(&line, 0, 256); //volver a poner en 0 el char
                file.getline(line, 256);
                string linea = line;
                size_t cant = cantidad_elementos(linea);
                if (cant > 0)
                {
                    arrVrt[count].e = S;
                    arrVrt[count].tmpChqVrs = 0;
                    arrVrt[count].cntChqVrs = 0;
                    for (int j = 0; j < cant; j++)
                    {
                        arrVrt[count].lstAdy.push_back(elemento(linea, j));
                    }
                    count++;
                }
                azarizarTmpChqVrs(vcf);
            }
            return;
            throw 1;
        }

    }

    template < typename V >
    GrafoGnr< V >::~GrafoGnr()
    {

    }

    template < typename V >
    bool GrafoGnr< V >::xstVrt(int vrt) const
    {
        return (vrt < cntVrt && vrt >= 0); // Devuelve true si vrt esta entre 0 y cntVrt
    }

    template < typename V >
    bool GrafoGnr< V >::xstAdy(int vrtO, int vrtD) const
    {
        if (xstVrt(vrtO) && xstVrt(vrtD)) // Comprueba que el indice del vertice existe
        {
            int cantidad_adyacencias = arrVrt[vrtO].lstAdy.size();
            if (cantidad_adyacencias == 0) return false; // No hay adyacencias, por lo tanto la adyacencia no existe
            for (int i = 0; i < arrVrt[vrtO].lstAdy.size(); i++)
            {
                if (arrVrt[vrtO].lstAdy[i] == vrtD) return true;
            }
            return false;
        }
        return false; // No se encontro adyacencia o el vertice no existe
    }


    template < typename V >
    void GrafoGnr< V >::obtAdy(int vrt, vector<int>& vec) const
    {
        if (xstVrt(vrt))
        {
            vec.clear();
            for (int i = 0; i < arrVrt[vrt].lstAdy.size(); i++)
            {
                vec.push_back(arrVrt[vrt].lstAdy[i]);
            }
        }
    }


    template < typename V >
    int GrafoGnr< V >::obtTotVrt() const
    {
        return cntVrt;
    }


    template < typename V >
    int GrafoGnr< V >::obtTotAdy() const
    {
        int cant = 0;
        for (int i = 0; i < cntVrt; i++)
        {
            cant += arrVrt[i].lstAdy.size();
        }
        return cant;
    }


    template < typename V >
    V& GrafoGnr< V >::operator[](int vrt)
    {
        if (xstVrt(vrt)) return V(vrt);
    }

    template < typename V >
    bool GrafoGnr< V >::operator==(const GrafoGnr& grf) const
    {
        if (this->cntVrt != grf.cntVrt) return false;
        for (int i = 0; i < this->cntVrt; i++)
        {
            if (arrVrt[i].lstAdy.size() != grf.arrVrt[i].lstAdy.size()) return false;
            vector<int>ady, adygrf;
            obtAdy(i, ady);
            grf.obtAdy(i, adygrf);
            for (int j = 0; j < arrVrt[i].lstAdy.size(); j++)
            {
                if (ady[j] != adygrf[j])
                {
                    return false;
                }
            }
        }
        return true;
    }



    template < typename V >
    double GrafoGnr< V >::promLongCmnsCrts() const
    {
        int sum = 0, total = cntVrt * (cntVrt - 1) / 2;
        int **matriz = Floyd_Warshall();
        for (int i = 0; i < cntVrt; i++)
        {
            for (int j = i; j < cntVrt; j++)
            {
                if (xstAdy(i, j))
                    sum += matriz[i][j];
            }
        }
        for (int i = 0; i < cntVrt; i++)
        {
            delete[] matriz[i];
        }
        delete[] matriz;
        return ((double) sum / (double) total);
    }
    template <typename V>
    int **GrafoGnr<V>::Floyd_Warshall() const
    {
        int** path;
        path = new int*[cntVrt];
        for (int i = 0; i < cntVrt; i++)
        {
            path[i] = new int[cntVrt];
            path[i][i] = 0;
        }
        for (int i = 0; i < cntVrt; i++)
        {
            for (int j = 0; j < cntVrt; j++)
            {
                if (xstAdy(i, j))
                {
                    path[i][j] = 1;
                }
                else
                {
                    path[i][j] = std::numeric_limits<int>::max();
                }
            }
        }
        for (int k = 0; k < cntVrt; k++)
            for (int i = 0; i < cntVrt; i++)
                for (int j = 0; j < cntVrt; j++)
                {
                    if (path[i][k] == std::numeric_limits<int>::max() || path[k][j] == std::numeric_limits<int>::max()) continue;
                    int dt = path[i][k] + path[k][j];
                    if (path[i][j] > dt)
                        path[i][j] = dt;
                }

        return path;
    }


    template < typename V >
    double GrafoGnr< V >::coeficienteAgrupamiento(int vrt) const
    {
        if (xstVrt(vrt))
        {
            double cant = (double) arrVrt[vrt].lstAdy.size(), triangles = 0.0;
            if (cant == 0 || cant == 1) return 0;
            double t_g = (cant * (cant - 1)) / 2;
            vector<int>ady;
            obtAdy(vrt, ady);
            for (int i = 0; i < cant; i++)
            {
                for (int j = i + 1; j < cant; j++)
                {
                    if (xstAdy(ady[i], ady[j]))
                    {
                        triangles++;
                    }
                }
            }
            return (triangles / t_g);
        }
        return 0;
    }

    /*template < typename V >
    GrafoGnr < V > ::E GrafoGnr< V >::obtEst(int vrt) const
    {
        if (xstVrt(vrt) == true)
        {
            return arrVrt[vrt].e;
        }
    }*/

    template < typename V >
    int GrafoGnr< V >::obtTmpChqVrs(int vrt) const
    {
        return arrVrt[vrt].tmpChqVrs;
    }

    template < typename V >
    int GrafoGnr< V >::obtCntChVrs(int vrt)const
    {

        return arrVrt[vrt].cntChqVrs;

    }

    template < typename V >
    void GrafoGnr< V >::modEst(int vrt, E ne)
    {
        if (xstVrt(vrt))
        {
            arrVrt[vrt].e = ne;
        }
    }

    template < typename V >
    void GrafoGnr< V >::modTmpChqVrs(int vrt, int nt)
    {
        if(xstVrt(vrt)) arrVrt[vrt].tmpChqVrs = nt;
    }


    template < typename V >
    void GrafoGnr< V >::actCntChqVrs(int vrt)
    {
        if(xstVrt(vrt)&& arrVrt[vrt].cntChqVrs == arrVrt[vrt].tmpChqVrs)
            arrVrt[vrt].cntChqVrs = 0;
        else
        {
            arrVrt[vrt].cntChqVrs++;
        }
    }


    template < typename V >
    void GrafoGnr< V >::infectar(int ios)
    {
        if (ios < obtTotVrt())
        {
            vector<int>infectemos;
            int randy;
            bool esta = true;
            for (int i = 0; i < ios; i++)
            {
                while (esta)
                {
                    randy = rand() % obtTotVrt();
                    esta = false;
                    for (int j = 0; j < infectemos.size(); j++)
                    {
                        if(infectemos[j] == randy) esta = true;
                    }
                }
                infectemos.push_back(randy);
                esta = true;
            }
            for (int i=0; i<infectemos.size(); i++)
            {
                arrVrt[infectemos[i]].e = I;
            }
        }
    }


    template < typename V >
    void GrafoGnr< V >::azarizarTmpChqVrs(int vcf)
    {
        int randy;
        for (int i = 0; i < obtTotVrt(); i++)
        {
            randy = rand() % vcf + 1;
            arrVrt[i].tmpChqVrs = randy;
        }
    }


#endif	/* GRAFOGNR_H */

