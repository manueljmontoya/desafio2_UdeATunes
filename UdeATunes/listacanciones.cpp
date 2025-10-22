#include <iostream>
#include "listacanciones.h"
#include "Cancion.h"

using namespace std;

Cancion* ListaCanciones::buscarCancion(int idCancion)const{

    for(int i=0; i<cantidad; i++){
        if (canciones[i]->getId() == idCancion){
            return canciones[i];
        }
    }
    return nullptr;

}

void ListaCanciones::redimensionar(){

    int nuevaCapacidad=capacidad+100;
    Cancion** temporal=new Cancion*[nuevaCapacidad];
    for (int i=0; i<cantidad; i++){
        temporal[i]=canciones[i];
    }
    delete[] canciones;
    canciones=temporal;
    capacidad=nuevaCapacidad;

}

bool ListaCanciones::agregar(Cancion *c){

    for (int i=0; i<cantidad; i++){

        if (canciones[i]->getId() == c->getId()){
            return false;
        }
    }
    if (cantidad==capacidad){
        redimensionar();
    }
    canciones[cantidad]=c;
    cantidad++;
    return true;

}

bool ListaCanciones::eliminar(int idCancion){

    for (int i=0; i<cantidad; i++){
        if (canciones[i]->getId() == idCancion){
            for(int j=i; j<cantidad-1; j++){
                canciones[j]=canciones[j+1];
            }
            cantidad--;
            return true;
        }
    }
    return false;

}

int ListaCanciones::getCantidad()const{

    return cantidad;

}

Cancion* ListaCanciones::getCancion(int pos)const{

    return canciones[pos];

}

ListaCanciones::~ListaCanciones(){

    delete[] canciones;

}
