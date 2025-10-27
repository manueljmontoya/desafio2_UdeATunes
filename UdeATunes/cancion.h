#include <iostream>
#ifndef CANCION_H
#define CANCION_H
#include <string>
#include "creditos.h"
#include "album.h"
#include "Metricas.h"

class Cancion{

private:

    int idCancion;
    float duracion;
    int reproducciones;
    string ruta128;
    string ruta320;
    string nombre;
    int idAlbum;
    Creditos* creditosCancion;

public:

    Cancion( int id,float duracion_,int repro,string ruta1,
            string ruta2, string nombre_, int album_):idCancion(id),
        duracion(duracion_),reproducciones(repro),ruta128(ruta1),
        ruta320(ruta2),nombre(nombre_),idAlbum(album_),creditosCancion(nullptr){

        size_t memoria = sizeof(*this) +
                        Metricas::calcularMemoriaString(nombre) +
                        Metricas::calcularMemoriaString(ruta128) +
                        Metricas::calcularMemoriaString(ruta320);
        Metricas::agregarMemoria(memoria);


    }
    void reproducir(int calidad);
    int getId(){return idCancion;}

    ~Cancion() {
        size_t memoria = sizeof(*this) +
                         Metricas::calcularMemoriaString(nombre) +
                         Metricas::calcularMemoriaString(ruta128) +
                         Metricas::calcularMemoriaString(ruta320);
        Metricas::removerMemoria(memoria);

        if (creditosCancion != nullptr) {
            delete creditosCancion;
        }
    }

};

#endif // CANCION_H
