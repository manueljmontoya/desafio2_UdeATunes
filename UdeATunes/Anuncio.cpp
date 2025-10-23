#include "Anuncio.h"
#include <iostream>
using namespace std;

Anuncio::Anuncio() {
    contenido = "Anuncio por defecto";
    prioridad = 1;
    calcularCategoria();
    siguiente = nullptr;
}


Anuncio::Anuncio(string cont, int pri) {

    if (cont.length() > 500) {
        contenido = cont.substr(0, 500);
    } else {
        contenido = cont;
    }

    if (pri >= 1 && pri <= 6) {
        prioridad = pri;
    } else {
        prioridad = 1;
    }

    siguiente = nullptr;
    calcularCategoria();
}

Anuncio::~Anuncio() {

}

void Anuncio::calcularCategoria() {

    if (prioridad >= 1 && prioridad <= 3) {
        categoria = "AAA";
    } else if (prioridad >= 4 && prioridad <= 5) {
        categoria = "B";
    } else {
        categoria = "C";
    }
}

void Anuncio::setContenido(string cont) {
    if (cont.length() > 500) {
        contenido = cont.substr(0, 500);
    } else {
        contenido = cont;
    }
}

void Anuncio::setPrioridad(int pri) {
    if (pri >= 1 && pri <= 6) {
        prioridad = pri;
        calcularCategoria();
    }
}

bool Anuncio::operator==(const Anuncio& otro) const {
    return (contenido == otro.contenido && categoria == otro.categoria);
}

ostream& operator<<(ostream& os, const Anuncio& anuncio) {

    os << " - Anuncio: " << anuncio.contenido;
    os << "Categoria [" << anuncio.categoria << "]";

    return os;
}
