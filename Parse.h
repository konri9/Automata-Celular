#ifndef PARSE_H
#define PARSE_H

#include <string>

namespace line_parse
{
unsigned int cantidad_elementos(const std::string& linea, char rem = ',');
std::string remover_comillas(const std::string& str);
std::string parametro(std::string linea, int indice, char rem = ',');
int elemento(std::string linea, int indice, char rem = ',');
double elemento_double(std::string linea, int indice, char rem);
int totalDeVertices(std::string data);
double promedioAdy(std::string data);
}

#endif
