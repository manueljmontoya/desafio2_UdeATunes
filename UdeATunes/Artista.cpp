#include "Artista.h"

Artista::Artista(int id, int edad, const string& pais, int seguidores, int posicion)
    : id(id), edad(edad), paisOrigen(pais), seguidores(seguidores),
    posicionTendencias(posicion) {}


int Artista::getId() const {
    return id;
}

int Artista::getEdad() const {
    return edad;
}

const string& Artista::getPaisOrigen() const {
    return paisOrigen;
}

int Artista::getSeguidores() const {
    return seguidores;
}

int Artista::getPosicionTendencias() const {
    return posicionTendencias;
}

void Artista::setEdad(int nuevaEdad) {
    edad = nuevaEdad;
}

void Artista::setSeguidores(int nuevosSeguidores) {
    seguidores = nuevosSeguidores;
}

void Artista::setPosicionTendencias(int nuevaPosicion) {
    posicionTendencias = nuevaPosicion;
}

void Artista::setPaisOrigen(const string& nuevoPais) {
    paisOrigen = nuevoPais;
}

bool Artista::operator==(const Artista& other) const {
    return id == other.id;
}
