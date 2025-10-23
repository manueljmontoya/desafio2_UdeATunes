#include <iostream>
#ifndef LISTAFAVORITOS_H
#define LISTAFAVORITOS_H
#include "usuario.h"
#include "listacanciones.h"

using namespace std;

class ListaFavoritos{

private:

    Usuario* propietario;
    ListaCanciones canciones;

public:

    ListaFavoritos(Usuario* u):propietario(u){}
    bool agregarCancion(Cancion* c);
    Cancion* buscarCancion(int idCancion);
    bool eliminarCancion(int idCancion);
    void fusionarListas(const ListaFavoritos& otra);

    int getCantidadCanciones()const{return canciones.getCantidad();}

};

#endif // LISTAFAVORITOS_H
