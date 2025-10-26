#include <iostream>
#ifndef LISTAFAVORITOS_H
#define LISTAFAVORITOS_H
#include "Usuario.h"
#include "listacanciones.h"

using namespace std;

class ListaFavoritos{

private:

    Usuario* propietario;
    ListaCanciones canciones;

public:

    ListaFavoritos(Usuario* u):propietario(u),canciones(ListaCanciones()){}
    bool agregarCancion(Cancion* c);
    Cancion* buscarCancion(int idCancion);
    bool eliminarCancion(int idCancion);
    void fusionarListas(const ListaFavoritos& otra);
    Cancion* getCancion(int i);
    void setCapacidad(int capacidad_){canciones.setCapacidad(capacidad_);}

    int getCantidadCanciones()const{return canciones.getCantidad();}

};

#endif // LISTAFAVORITOS_H
