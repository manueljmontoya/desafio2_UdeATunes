#include <iostream>
#ifndef CREDITOS_H
#define CREDITOS_H
#include <string>

class Creditos{

private:

    int categoria;
    string nombre;
    int codigoAfiliacion;

public:

    Creditos(int categoria_, string nombre_, int cod):categoria(categoria_),
        nombre(nombre_),codigoAfiliacion(cod){}

};

#endif // CREDITOS_H
