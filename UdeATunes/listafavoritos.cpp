#include <iostream>
#include "listafavoritos.h"
#include "Usuario.h"
#include "listacanciones.h"

using namespace std;

Cancion* ListaFavoritos::buscarCancion(int idCancion){

   return canciones.buscarCancion(idCancion);

}

bool ListaFavoritos::agregarCancion(Cancion *c){

    if (canciones.getCantidad()>=10000){
        return false;
    }
    return canciones.agregar(c);

}

bool ListaFavoritos::eliminarCancion(int idCancion){

    return canciones.eliminar(idCancion);

}

void ListaFavoritos::fusionarListas(const ListaFavoritos &otra){

    for (int i=0; i<otra.canciones.getCantidad(); i++){
        Cancion* c=otra.canciones.getCancion(i);
        canciones.agregar(c);
    }

}
