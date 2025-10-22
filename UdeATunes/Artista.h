#ifndef ARTISTA_H
#define ARTISTA_H

#include <string>
using namespace std;

class Artista {
private:
    int id;                    // Código identificador (5 dígitos)
    int edad;
    string paisOrigen;         // País de origen
    int seguidores;           // Cantidad de seguidores en la plataforma
    int posicionTendencias;   // Posición en lista de tendencias global

public:
    // Constructor
    Artista(int id, int edad, const string& pais, int seguidores, int posicion);

    // Constructor de copia (default)
    Artista(const Artista& other) = default;

    // Destructor (default)
    ~Artista() = default;

    // Getters
    int getId() const;
    int getEdad() const;
    const string& getPaisOrigen() const;
    int getSeguidores() const;
    int getPosicionTendencias() const;

    // Setters
    void setEdad(int nuevaEdad);
    void setSeguidores(int nuevosSeguidores);
    void setPosicionTendencias(int nuevaPosicion);
    void setPaisOrigen(const string& nuevoPais);

    // Sobrecarga del operador de asignación (default)
    Artista& operator=(const Artista& other) = default;

    // Sobrecarga del operador de igualdad
    bool operator==(const Artista& other) const;
};

#endif
