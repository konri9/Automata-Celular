#ifndef PARSE_H
#define PARSE_H

#include <string>
#include <vector>
namespace line_parse
{
bool nola (int element, std::vector<int>&vec);  // Este metodo es para saber que no estoy reescribiendo una adyacencia
unsigned int cantidad_elementos(const std::string& linea, char rem = ',');
std::string remover_comillas(const std::string& str);
std::string parametro(std::string linea, int indice, char rem = ',');
int elemento(std::string linea, int indice, char rem = ',');
double elemento_double(std::string linea, int indice, char rem);
int totalDeVertices(std::string data);
double promedioAdy(std::string data);
}

#endif
