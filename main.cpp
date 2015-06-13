/*
 * File:   newsimpletest.cpp
 * Author: konrad
 *
 * Created on May 28, 2015, 10:29:12 AM
 */

#include <stdlib.h>
#include <iostream>
#include "GrafoGnr.h"
using namespace std;

/*
 * Simple C++ Test Suite
 */


//Construye una red con la cantidad de vértices y el promedio de
//adyacencias por vértice correctos cuando cntVrt == 100 y prmAdy == 15.
//Construye una red con la cantidad de vértices y el promedio de
//adyacencias por vértice correctos cuando cntVrt == 1000 y prmAdy == 15.

void testConstructorGrafo() {
    GrafoGnr grafo(100,0.5);
    Grafo grafo2(1000,0.5);
    if (grafo.obtTotVrt()!=100  || grafo2.obtTotVrt() != 1000){
        std::cout << "%TEST_FAILED% FALLO EL CONSTRUCTOR DEL GRAFO(newsimpletest) message=ereror message sample" << std::endl;
    }
 //  cout << grafo.obtTotVrt() << endl;
 // cout << grafo2.obtTotVrt() << endl;

}

//Construye una copia idéntica a Grafo(100,15).
//Construye una copia idéntica a Grafo(1000,15).

void testConstructCopias() {
    GrafoGnr orig(100,15);
    GrafoGnr grafo(orig);
    GrafoGnr orig2(1000,15);
    GrafoGnr grafo2(orig2);
    if (!(grafo.obtTotVrt() == orig.obtTotVrt()) || !(grafo2.obtTotVrt() == orig2.obtTotVrt())) {
        std::cout << "%TEST_FAILED% FALLO EL CONSTRUCTOR DE COPIAS (newsimpletest) message=error message sample" << std::endl;
    }
}

//Construye el grafo correcto con el “redMuyPeq.txt”.
//Construye el grafo correcto con el “redPeq.txt”.

void testConstructorString() {
    GrafoGnr grafo("redMuyPeq.txt");
    GrafoGnr grafo2("redPeq.txt");
    if (grafo.obtTotVrt() != 10 || grafo2.obtTotVrt() != 100 ){//}|| grafo.obtAdy(0)[0] != 8 || grafo2.obtAdy(0)[0] != 2) {
        std::cout << "%TEST_FAILED% FALLO EL CONSTRUCTOR A PARTIR DEL STRING (newsimpletest) message=error message sample" << std::endl;
    }
}


//void infectar(int ios) efectivamente “infecta” la cantidad correcta de vértices

void testInfectar() {
    GrafoGnr grafo("redMuyPeq.txt");
    grafo.infectar(5);
    int cont = 0;
    for(int i=0;i<grafo.obtTotVrt();i++) {
        if(grafo.obtEst(i)==Grafo::I) cont++;
    }
    if (cont != 5) {
        std::cout << "%TEST_FAILED% FALLO EL METODO Infectar (newsimpletest) message=error message sample" << std::endl;
    }
}

//void azarizarTmpChqVrs(int vcf) efectivamente asigna valores
//iniciales al temporizador de chequeo en el rango [1..vcf] para todos los vértices.
void testAzarizarTmpChqVrs() {
    GrafoGnr grafo("redMuyPeq.txt");
    grafo.azarizarTmpChqVrs(5);
    for(int i=0;i<grafo.obtTotVrt();i++)
    if (grafo.obtTmpChqVrs(i) == NULL) {
        std::cout << "%TEST_FAILED% FALLO EL METODO AzarizarTmpChqVrs (newsimpletest) message=error message sample" << std::endl;
    }
}

//Genera el valor correcto con un grafo muy pequeño.

void testPromLongCmnsCrts() {
    GrafoGnr grafo("redMuyPeq.txt");
    double res = grafo.promLongCmnsCrts();
    if (!(0.4 > res > 0)) {
        std::cout << "%TEST_FAILED% FALLO EL METODO PromLongCmnsCrts(newsimpletest) message=error message sample" << std::endl;
    }
}

//Genera el valor correcto para el vértice indicado de un grafo muy pequeño.

void testCoeficienteAgrupamiento() {
    GrafoGnr grafo("redMuyPeq.txt");
    double res = grafo.coeficienteAgrupamiento(0);
    if (!(res == 0)) {
        std::cout << "%TEST_FAILED% FALLO EL METODO CoeficienteAgrupamiento (newsimpletest) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv) {

    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testConstructorGrafo (newsimpletest)" << std::endl;
    testConstructorGrafo();
    std::cout << "%TEST_FINISHED% testConstructorGrafo (newsimpletest)" << std::endl;

    cout << "%TEST_STARTED% testConstructCopias(newsimpletest)" << endl;
    testConstructCopias();
    cout << "%TEST_FINISHED% testConstructCopias (newsimpletest)" << endl;

    cout << "%TEST_STARTED% testConstructorString (newsimpletest)" << endl;
    testConstructorString();
    cout << "%TEST_FINISHED% testConstructorString (newsimpletest)" << endl;

    cout << "%TEST_STARTED% testInfectar (newsimpletest)" << endl;
    testInfectar();
    cout << "%TEST_FINISHED% testInfectar (newsimpletest)" << endl;

    cout << "%TEST_STARTED% testAzarizarTmpChqVrs (newsimpletest)" << endl;
    testAzarizarTmpChqVrs();
    cout << "%TEST_FINISHED% testAzarizarTmpChqVrs (newsimpletest)" << endl;

    cout << "%TEST_STARTED% testPromLongCmnsCrts (newsimpletest)" << endl;
    testPromLongCmnsCrts();
    cout << "%TEST_FINISHED% testPromLongCmnsCrts (newsimpletest)" << endl;

    cout << "%TEST_STARTED% testCoeficienteAgrupamiento (newsimpletest)" << endl;
    testCoeficienteAgrupamiento();
    cout << "%TEST_FINISHED% testCoeficienteAgrupamiento (newsimpletest)" << endl;

    cout << "%SUITE_FINISHED% time=0" << endl;

    //return (EXIT_SUCCESS);
    return 0;
}

