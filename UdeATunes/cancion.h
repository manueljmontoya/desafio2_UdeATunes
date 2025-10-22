#include <iostream>
#ifndef CANCION_H
#define CANCION_H
#include <string>
#include "creditos.h"
#include "album.h"

class Cancion{

private:

    int idCancion;
    float duracion;
    int reproducciones;
    Creditos creditos;
    string ruta128;
    string ruta320;
    string nombre;
    Album album;

public:

    Cancion( int id,float duracion_,int repro,Creditos credit,string ruta1,
            string ruta2, string nombre_, Album album_):idCancion(id),duracion(duracion_),
        reproducciones(repro),creditos(credit),ruta128(ruta1),ruta320(ruta2),
        nombre(nombre_),album(album_){}
    void reproducir(int calidad);

};

#endif // CANCION_H
