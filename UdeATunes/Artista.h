#ifndef ARTISTA_H
#define ARTISTA_H

#include <string>
using namespace std;

class Artista {
private:
    int id;
    int edad;
    string paisOrigen;
    int seguidores;
    int posicionTendencias;

public:
    Artista(int id, int edad, const string& pais, int seguidores, int posicion);

    Artista(const Artista& other) = default;

    ~Artista() = default;

    int getId() const;
    int getEdad() const;
    const string& getPaisOrigen() const;
    int getSeguidores() const;
    int getPosicionTendencias() const;

    void setEdad(int nuevaEdad);
    void setSeguidores(int nuevosSeguidores);
    void setPosicionTendencias(int nuevaPosicion);
    void setPaisOrigen(const string& nuevoPais);

    Artista& operator=(const Artista& other) = default;

    bool operator==(const Artista& other) const;
};

#endif
