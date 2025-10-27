#include <iostream>
#include "listafavoritos.h"
#include "Usuario.h"
#include "listacanciones.h"
#include "Metricas.h"

using namespace std;

Cancion* ListaFavoritos::buscarCancion(int idCancion){

   return canciones.buscarCancion(idCancion);

}

bool ListaFavoritos::agregarCancion(Cancion *c){
    Metricas::iniciarMedicion("Agregar Cancion Favoritos");

    if (canciones.getCantidad()>=10000){
        Metricas::agregarIteraciones(1);
        Metricas::finalizarMedicion();
        return false;
    }

    Metricas::agregarIteraciones(1);

    bool resultado = canciones.agregar(c);
    Metricas::finalizarMedicion();
    return resultado;
}

Cancion* ListaFavoritos::getCancion(int i){

    return canciones.getCancion(i);

}

bool ListaFavoritos::eliminarCancion(int idCancion){

    return canciones.eliminar(idCancion);

}

void ListaFavoritos::fusionarListas(const ListaFavoritos &otra){

     Metricas::iniciarMedicion("Fusionar Listas Favoritos");

    for (int i=0; i<otra.canciones.getCantidad(); i++){
        Metricas::agregarIteraciones(1);

        Cancion* c=otra.canciones.getCancion(i);
        canciones.agregar(c);
        Metricas::agregarIteraciones(1);
    }
    Metricas::finalizarMedicion();
}
