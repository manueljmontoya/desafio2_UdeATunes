#include "Artista.h"
#include "Metricas.h"

Artista::Artista(string nomb, int id, int edad, const string& pais, int seguidores, int posicion){
    Metricas::iniciarMedicion("Constructor Artista");

    nombre=nomb;
    id=id;
    edad=edad;
    paisOrigen=pais;
    seguidores=seguidores;
    posicionTendencias=posicion;
    Metricas::agregarIteraciones(6);

    size_t memoria = sizeof(*this) +
                    Metricas::calcularMemoriaString(nombre) +
                    Metricas::calcularMemoriaString(paisOrigen);
    Metricas::agregarMemoria(memoria);

    Metricas::finalizarMedicion();

}


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

Artista::~Artista() {
    size_t memoria = sizeof(*this) +
                     Metricas::calcularMemoriaString(nombre) +
                     Metricas::calcularMemoriaString(paisOrigen);
    Metricas::removerMemoria(memoria);
}
