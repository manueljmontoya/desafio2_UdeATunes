#include <iostream>
#include "listacanciones.h"
#include "cancion.h"
#include "Metricas.h"

using namespace std;

Cancion* ListaCanciones::buscarCancion(int idCancion)const{
    Metricas::iniciarMedicion("Buscar Cancion");

    for(int i=0; i<cantidad; i++){
        Metricas::agregarIteraciones(1);
        if (canciones[i]->getId() == idCancion){
            Metricas::agregarIteraciones(2);
            Metricas::finalizarMedicion();
            return canciones[i];
        }
        else Metricas::agregarIteraciones(1);
    }
    Metricas::agregarIteraciones(1);
    Metricas::finalizarMedicion();
    return nullptr;

}

void ListaCanciones::setCapacidad(int capacidad_){
    Metricas::iniciarMedicion("Set Capacidad Lista");

    capacidad=capacidad_;
    canciones=new Cancion*[capacidad];
    Metricas::agregarIteraciones(2);

    size_t memoriaArray = sizeof(Cancion*) * capacidad;
    Metricas::agregarMemoria(memoriaArray);

    Metricas::finalizarMedicion();
}

void ListaCanciones::redimensionar(){
    Metricas::iniciarMedicion("Redimensionar Lista");

    int nuevaCapacidad=capacidad+100;
    Cancion** temporal=new Cancion*[nuevaCapacidad];
    Metricas::agregarIteraciones(2);

    size_t memoriaNuevo = sizeof(Cancion*) * nuevaCapacidad;
    Metricas::agregarMemoria(memoriaNuevo);

    for (int i=0; i<cantidad; i++){
        Metricas::agregarIteraciones(1);
        temporal[i]=canciones[i];
        Metricas::agregarIteraciones(1);
    }

    size_t memoriaViejo = sizeof(Cancion*) * capacidad;
    Metricas::removerMemoria(memoriaViejo);

    delete[] canciones;
    canciones=temporal;
    capacidad=nuevaCapacidad;
    Metricas::agregarIteraciones(3);

    Metricas::finalizarMedicion();
}

bool ListaCanciones::agregar(Cancion *c){
    Metricas::iniciarMedicion("Agregar Cancion");

    for (int i=0; i<cantidad; i++){
        Metricas::agregarIteraciones(1);

        if (canciones[i]->getId() == c->getId()){
            Metricas::agregarIteraciones(2);
            Metricas::finalizarMedicion();
            return false;
        }
        Metricas::agregarIteraciones(1);
    }
    if (cantidad==capacidad){
        Metricas::agregarIteraciones(1);
        redimensionar();
        Metricas::agregarIteraciones(1);
    }

    canciones[cantidad]=c;
    cantidad++;
    Metricas::agregarIteraciones(2);

    Metricas::finalizarMedicion();
    return true;

}

bool ListaCanciones::eliminar(int idCancion){
    Metricas::iniciarMedicion("Eliminar Cancion");

    for (int i=0; i<cantidad; i++){
        Metricas::agregarIteraciones(1);
        if (canciones[i]->getId() == idCancion){
            Metricas::agregarIteraciones(1);
            for(int j=i; j<cantidad-1; j++){
                Metricas::agregarIteraciones(1);
                canciones[j]=canciones[j+1];
                Metricas::agregarIteraciones(1);
            }
            cantidad--;
            Metricas::agregarIteraciones(1);
            Metricas::finalizarMedicion();
            return true;
        }
        Metricas::agregarIteraciones(1);
    }
    Metricas::agregarIteraciones(1);
    Metricas::finalizarMedicion();
    return false;

}

int ListaCanciones::getCantidad()const{

    return cantidad;

}

Cancion* ListaCanciones::getCancion(int pos)const{

    return canciones[pos];

}

ListaCanciones::~ListaCanciones(){

    size_t memoriaArray = sizeof(Cancion*) * capacidad;
    Metricas::removerMemoria(memoriaArray);

    delete[] canciones;

}
