#ifndef ANUNCIO_H
#define ANUNCIO_H

#include <iostream>
#include <string>
using namespace std;

class Anuncio
{

private:
    string contenido;
    string categoria;
    int prioridad;
    Anuncio* siguiente;

public:

    Anuncio();
    Anuncio(string cont, int pri);
    ~Anuncio();

    string getContenido() const { return contenido; }
    string getCategoria() const { return categoria; }
    int getPrioridad() const { return prioridad; }
    Anuncio* getSiguiente() const { return siguiente; }

    void setContenido(string cont);
    void setPrioridad(int pri);
    void setSiguiente(Anuncio* sig) { siguiente = sig; }

    void calcularCategoria();

    bool operator==(const Anuncio& otro) const;
    friend ostream& operator<<(ostream& os, const Anuncio& anuncio);

};

#endif
