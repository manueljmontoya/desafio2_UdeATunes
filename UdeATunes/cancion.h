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
    int creditos;
    string ruta128;
    string ruta320;
    string nombre;
    int idAlbum;

public:

    Cancion( int id,float duracion_,int repro,int credit,string ruta1,
            string ruta2, string nombre_, string album_):idCancion(id),duracion(duracion_),
        reproducciones(repro),creditos(credit),ruta128(ruta1),ruta320(ruta2),
        nombre(nombre_),album(album_){}
    void reproducir(int calidad);

};

#endif // CANCION_H
