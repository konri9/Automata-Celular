/*
 * File:   newsimpletest.cpp
 * Author: konrad
 *
 * Created on May 28, 2015, 10:29:12 AM
 */

#include <stdlib.h>
#include <iostream>
#include "GrafoGnr.h"
#include "NdoVrt.h"
using namespace std;

//Construye una red con la cantidad de vértices y el promedio de
//adyacencias por vértice correctos cuando cntVrt == 100 y prbAdy == 0.5.
//Construye una red con la cantidad de vértices y el promedio de
//adyacencias por vértice correctos cuando cntVrt == 1000 y prbAdy == 0.5.


void testConstructorGrafo()
{
    GrafoGnr< int > grafo (100,0.5);
    GrafoGnr< int >  grafo2(1000,0.5);
    if (grafo.obtTotVrt()!=100  || grafo2.obtTotVrt() != 1000)
    {
        std::cout << "%TEST_FAILED% FALLO EL CONSTRUCTOR DEL GRAFO(newsimpletest) message=ereror message sample" << std::endl;
    }
}


void testConstructorGrafo2()
{
    GrafoGnr< NdoVrt > grafo (100,0.5);
    GrafoGnr< NdoVrt >  grafo2(1000,0.5);
    if (grafo.obtTotVrt()!=100  || grafo2.obtTotVrt() != 1000)
    {
        std::cout << "%TEST_FAILED% FALLO EL CONSTRUCTOR DEL GRAFO(newsimpletest) message=ereror message sample" << std::endl;
    }
}

//Construye una copia idéntica a Grafo(100,0.5).
//Construye una copia idéntica a Grafo(1000,0.5).

void testConstructCopias()
{
    GrafoGnr< int > orig(100,15);
    GrafoGnr< int > grafo(orig);
    GrafoGnr< int > orig2(1000,15);
    GrafoGnr< int > grafo2(orig2);
    if (!(grafo.obtTotVrt() == orig.obtTotVrt()) || !(grafo2.obtTotVrt() == orig2.obtTotVrt()))
    {
        std::cout << "%TEST_FAILED% FALLO EL CONSTRUCTOR DE COPIAS (newsimpletest) message=error message sample" << std::endl;
    }
}

void testConstructCopias2()
{
    GrafoGnr< NdoVrt > orig(100,15);
    GrafoGnr< NdoVrt > grafo(orig);
    GrafoGnr< NdoVrt > orig2(1000,15);
    GrafoGnr< NdoVrt > grafo2(orig2);
    if (!(grafo.obtTotVrt() == orig.obtTotVrt()) || !(grafo2.obtTotVrt() == orig2.obtTotVrt()))
    {
        std::cout << "%TEST_FAILED% FALLO EL CONSTRUCTOR DE COPIAS (newsimpletest) message=error message sample" << std::endl;
    }
}



//Construye el grafo correcto con el “redMuyPeq.txt”.
//Construye el grafo correcto con el “redPeq.txt”.

void testConstructorString()
{
    GrafoGnr< int >  grafo("redMuyPeq.txt");
    GrafoGnr< int >  grafo2("redPeq.txt");
    if (grafo.obtTotVrt() != 10 || grafo2.obtTotVrt() != 100 ) //}|| grafo.obtAdy(0)[0] != 8 || grafo2.obtAdy(0)[0] != 2) {
    {
        std::cout << "%TEST_FAILED% FALLO EL CONSTRUCTOR A PARTIR DEL STRING (newsimpletest) message=error message sample" << std::endl;
    }
}

void testConstructorString2()
{
    GrafoGnr< NdoVrt >  grafo("redMuyPeq.txt");
    GrafoGnr< NdoVrt >  grafo2("redPeq.txt");
    if (grafo.obtTotVrt() != 10 || grafo2.obtTotVrt() != 100 ) //}|| grafo.obtAdy(0)[0] != 8 || grafo2.obtAdy(0)[0] != 2) {
    {
        std::cout << "%TEST_FAILED% FALLO EL CONSTRUCTOR A PARTIR DEL STRING (newsimpletest) message=error message sample" << std::endl;
    }
}

void testPromLongCmnsCrts()
{
    GrafoGnr< int >  grafo("redMuyPeq.txt");
    double res = grafo.promLongCmnsCrts();
    //cout<< "el promedio es "<<res<< endl;
    if (!(res <= 0.7))
    {
        std::cout << "%TEST_FAILED% FALLO EL METODO PromLongCmnsCrts(newsimpletest) message=error message sample" << std::endl;
    }
}

void testPromLongCmnsCrts2()
{
    GrafoGnr< NdoVrt >  grafo("redMuyPeq.txt");
    double res = grafo.promLongCmnsCrts();
    //cout<< "el promedio es "<<res<< endl;
    if (!(res <= 0.7))
    {
        std::cout << "%TEST_FAILED% FALLO EL METODO PromLongCmnsCrts(newsimpletest) message=error message sample" << std::endl;
    }
}


//Genera el valor correcto para el vértice indicado de un grafo muy pequeño.
void testCoeficienteAgrupamiento()
{
    GrafoGnr< int >  grafo("redMuyPeq.txt");
    double res = grafo.coeficienteAgrupamiento(0);
  //  cout<< "el coef es" << res << endl;
    if (!(res <= 0.7))
    {
        std::cout << "%TEST_FAILED% FALLO EL METODO CoeficienteAgrupamiento (newsimpletest) message=error message sample" << std::endl;
    }
}

void testCoeficienteAgrupamiento2()
{
    GrafoGnr< int >  grafo("redMuyPeq.txt");
    double res = grafo.coeficienteAgrupamiento(0);
  //  cout<< "el coef es" << res << endl;
    if (!(res <= 0.7))
    {
        std::cout << "%TEST_FAILED% FALLO EL METODO CoeficienteAgrupamiento (newsimpletest) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv)
{

    std::cout << "%SUITE_STARTING% newsimpletest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testConstructorGrafo (newsimpletest)" << std::endl;
    testConstructorGrafo();
    std::cout << "%TEST_FINISHED% testConstructorGrafo (newsimpletest)" << std::endl;

    std::cout << "%TEST_STARTED% testConstructorGrafo (newsimpletest)" << std::endl;
    testConstructorGrafo2();
    std::cout << "%TEST_FINISHED% testConstructorGrafo (newsimpletest)" << std::endl;

    cout << "%TEST_STARTED% testConstructCopias(newsimpletest)" << endl;
    testConstructCopias();
    cout << "%TEST_FINISHED% testConstructCopias (newsimpletest)" << endl;

    cout << "%TEST_STARTED% testConstructCopias(newsimpletest)" << endl;
    testConstructCopias2();
    cout << "%TEST_FINISHED% testConstructCopias (newsimpletest)" << endl;

    cout << "%TEST_STARTED% testConstructorString (newsimpletest)" << endl;
    testConstructorString();
    cout << "%TEST_FINISHED% testConstructorString (newsimpletest)" << endl;

    cout << "%TEST_STARTED% testConstructorString (newsimpletest)" << endl;
    testConstructorString2();
    cout << "%TEST_FINISHED% testConstructorString (newsimpletest)" << endl;

    cout << "%TEST_STARTED% testPromLongCmnsCrts (newsimpletest)" << endl;
    testPromLongCmnsCrts();
    cout << "%TEST_FINISHED% testPromLongCmnsCrts (newsimpletest)" << endl;

    cout << "%TEST_STARTED% testPromLongCmnsCrts (newsimpletest)" << endl;
    testPromLongCmnsCrts2();
    cout << "%TEST_FINISHED% testPromLongCmnsCrts (newsimpletest)" << endl;

    cout << "%TEST_STARTED% testCoeficienteAgrupamiento (newsimpletest)" << endl;
    testCoeficienteAgrupamiento();
    cout << "%TEST_FINISHED% testCoeficienteAgrupamiento (newsimpletest)" << endl;

    cout << "%TEST_STARTED% testCoeficienteAgrupamiento (newsimpletest)" << endl;
    testCoeficienteAgrupamiento2();
    cout << "%TEST_FINISHED% testCoeficienteAgrupamiento (newsimpletest)" << endl;
    cout << "%SUITE_FINISHED% time=0" << endl;

    //return (EXIT_SUCCESS);*/
    return 0;
}

