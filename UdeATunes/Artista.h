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
    string nombre;

public:
    Artista(string nomb,int id, int edad, const string& pais, int seguidores, int posicion);

    Artista(const Artista& other) = default;

    ~Artista();

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

    string getNombre(){return nombre;}
};

#endif
