/* 
 * File:   GrafoGnr.h
 * Author: alan.calderon
 *
 * Created on 4 de junio de 2015, 05:49 PM
 */

#ifndef GRAFOGNR_H
#define	GRAFOGNR_H

#include <chrono>
#include <random>
#include <memory>
#include <vector>
#include <string>
using namespace std;

// V es el tipo de vértice.
template < typename V >
class GrafoGnr {
    // Representa la red compleja sobre la cual se desarrollará la simulación.
    
public:
 
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
    vector<int>& obtAdy(int vrt) const;

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
    
private:
    struct NdoVrt {
        V vrt;
        // Escoja entre <vector>, <list> y <forward_list> para representar la lista de adyacencias del vértice.
    };
    
    int cntVrt; // representa la cantidad total de vértices
    // Escoja entre <vector>, <map> y <unordered_map> en lugar del arreglo de nodos de vértices.
};

template < typename V >
GrafoGnr< V >::GrafoGnr(int n, double prbAdy) {

}

template < typename V >
GrafoGnr< V >::GrafoGnr(const GrafoGnr< V >& orig) {
    
}

template < typename V >
GrafoGnr< V >::GrafoGnr(string nArch) {
    
}

template < typename V >
GrafoGnr< V >::~GrafoGnr() {
    
}

template < typename V >
bool GrafoGnr< V >::xstVrt(int vrt) const {
    
}

template < typename V >
bool GrafoGnr< V >::xstAdy(int vrtO, int vrtD) const {
    
}

template < typename V >
vector<int>& GrafoGnr< V >::obtAdy(int vrt) const {
    
}

template < typename V >
int GrafoGnr< V >::obtTotVrt() const {
    
}

template < typename V >
int GrafoGnr< V >::obtTotAdy() const {
    
}

template < typename V >
V& GrafoGnr< V >::operator[](int vrt) {
    
}

template < typename V >
bool GrafoGnr< V >::operator==(const GrafoGnr& o) const {

}

template < typename V >
double GrafoGnr< V >::promLongCmnsCrts() const {
    
}

template < typename V >
double GrafoGnr< V >::coeficienteAgrupamiento(int vrt) const {
    
}

#endif	/* GRAFOGNR_H */

