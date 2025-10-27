#include <iostream>
#ifndef LISTACANCIONES_H
#define LISTACANCIONES_H
#include "cancion.h"
#include "Metricas.h"

class ListaCanciones{

private:

    Cancion** canciones;
    int capacidad;
    int cantidad;
    void redimensionar();

public:

    ListaCanciones():capacidad(0),cantidad(0){

        size_t memoria = sizeof(*this);
        Metricas::agregarMemoria(memoria);

    }

    ~ListaCanciones();
    void setCapacidad(int capacidad_);
    bool agregar(Cancion* c);
    bool eliminar(int idCancion);
    Cancion* buscarCancion(int idCancion)const;
    int getCantidad()const;
    Cancion* getCancion(int pos)const;

};

#endif // LISTACANCIONES_H
