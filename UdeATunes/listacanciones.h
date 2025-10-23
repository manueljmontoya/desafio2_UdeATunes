#include <iostream>
#ifndef LISTACANCIONES_H
#define LISTACANCIONES_H
#include "Cancion.h"

class ListaCanciones{

private:

    Cancion** canciones;
    int capacidad;
    int cantidad;
    void redimensionar();

public:

    ListaCanciones():capacidad(100),cantidad(0),canciones(new Cancion*[capacidad]){}
    ~ListaCanciones();
    bool agregar(Cancion* c);
    bool eliminar(int idCancion);
    Cancion* buscarCancion(int idCancion)const;
    int getCantidad()const;
    Cancion* getCancion(int pos)const;

};

#endif // LISTACANCIONES_H
