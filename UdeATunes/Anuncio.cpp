#include "Anuncio.h"
#include "Metricas.h"
#include <iostream>
using namespace std;

Anuncio::Anuncio() {
    Metricas::iniciarMedicion("Constructor Anuncio por defecto");

    contenido = "Anuncio por defecto";
    prioridad = 1;
    calcularCategoria();
    siguiente = nullptr;

    size_t memoria = sizeof(*this) + Metricas::calcularMemoriaString(contenido) + Metricas::calcularMemoriaString(categoria);
    Metricas::agregarMemoria(memoria);

    Metricas::finalizarMedicion();
}


Anuncio::Anuncio(string cont, int pri) {

    Metricas::iniciarMedicion("Constructor Anuncio Parametrizado");

    if (cont.length() > 500) {
        Metricas::agregarIteraciones(1);
        contenido = cont.substr(0, 500);
        Metricas::agregarIteraciones(1);
    } else {
        Metricas::agregarIteraciones(1);
        contenido = cont;
        Metricas::agregarIteraciones(1);
    }

    if (pri >= 1 && pri <= 6) {
        Metricas::agregarIteraciones(1);
        prioridad = pri;
        Metricas::agregarIteraciones(1);
    } else {
        Metricas::agregarIteraciones(1);
        prioridad = 6;
        Metricas::agregarIteraciones(1);
    }

    siguiente = nullptr;
    calcularCategoria();
    Metricas::agregarIteraciones(1);

    size_t memoria = sizeof(*this) + Metricas::calcularMemoriaString(contenido) + Metricas::calcularMemoriaString(categoria);
    Metricas::agregarMemoria(memoria);

    Metricas::finalizarMedicion();
}


Anuncio::~Anuncio() {

    size_t memoria = sizeof(*this) + Metricas::calcularMemoriaString(contenido) + Metricas::calcularMemoriaString(categoria);
    Metricas::removerMemoria(memoria);

}

void Anuncio::calcularCategoria() {
    Metricas::iniciarMedicion("Calcular Categoria Anuncio");

    if (prioridad >= 1 && prioridad <= 3) {
        Metricas::agregarIteraciones(1);
        categoria = "AAA";
        Metricas::agregarIteraciones(1);
    } else if (prioridad >= 4 && prioridad <= 5) {
        Metricas::agregarIteraciones(1);
        categoria = "B";
        Metricas::agregarIteraciones(1);
    } else {
        Metricas::agregarIteraciones(1);
        categoria = "C";
        Metricas::agregarIteraciones(1);
    }
    Metricas::finalizarMedicion();
}

void Anuncio::setContenido(string cont) {
    Metricas::iniciarMedicion("Set Contenido Anuncio");

    if (cont.length() > 500) {
        Metricas::agregarIteraciones(1);
        contenido = cont.substr(0, 500);
        Metricas::agregarIteraciones(1);

    } else {
        Metricas::agregarIteraciones(1);
        contenido = cont;
        Metricas::agregarIteraciones(1);
    }
    Metricas::finalizarMedicion();
}

void Anuncio::setPrioridad(int pri) {
    Metricas::iniciarMedicion("Set Prioridad Anuncio");

    if (pri >= 1 && pri <= 6) {
        Metricas::agregarIteraciones(1);
        prioridad = pri;
        calcularCategoria();
        Metricas::agregarIteraciones(2);
    }
    else Metricas::agregarIteraciones(1);

    Metricas::finalizarMedicion();
}

bool Anuncio::operator==(const Anuncio& otro) const {
    return (contenido == otro.contenido && categoria == otro.categoria);
}

ostream& operator<<(ostream& os, const Anuncio& anuncio) {

    os << " - Anuncio: " << anuncio.contenido;
    os << "Categoria [" << anuncio.categoria << "]";

    return os;
}
