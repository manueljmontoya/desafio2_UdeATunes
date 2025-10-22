#ifndef SISTEMAANUNCIOS_H
#define SISTEMAANUNCIOS_H

#include "Anuncio.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class SistemaAnuncios {
private:

    Anuncio** anunciosAAA;
    Anuncio** anunciosB;
    Anuncio** anunciosC;

    int tamañoAAA, tamañoB, tamañoC;
    int cantidadAAA, cantidadB, cantidadC;

    Anuncio* ultimoAnuncioMostrado;

public:

    SistemaAnuncios();
    ~SistemaAnuncios();

    bool cargarAnunciosDesdeArchivos();
    bool cargarAnunciosAAA(string archivo);
    bool cargarAnunciosB(string archivo);
    bool cargarAnunciosC(string archivo);

    bool agregarAnuncioAAA(string mensaje);
    bool agregarAnuncioB(string mensaje);
    bool agregarAnuncioC(string mensaje);

    Anuncio* seleccionarAnuncioAleatorio();
    Anuncio* seleccionarAnuncioAAA();
    Anuncio* seleccionarAnuncioB();
    Anuncio* seleccionarAnuncioC();

    void mostrarAnuncioAleatorio();
    void mostrarEstadisticas() const;

    int getCantidadAAA() const { return cantidadAAA; }
    int getCantidadB() const { return cantidadB; }
    int getCantidadC() const { return cantidadC; }
    int getTotalAnuncios() const;
    bool puedeAgregarMasAnuncios() const;
};

#endif
