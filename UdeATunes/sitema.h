#include <iostream>
#ifndef SITEMA_H
#define SITEMA_H
#include <string>
#include "usuaio.h"
#include "listacanciones.h"
#include "cancion.h"
#include "anuncio.h"
#include "artista.h"

class Sitema{

    Usuario* usuarioActivo;
    Usuario** usuarios;
    int totalUsuarios;
    Cancion** canciones;
    int totalCanciones;
    Anuncio** anuncios;
    int totalAnuncios;
    int contadorReproducciones;

public:
    Sitema();
    void ejecutar();
    void cargarDatos();
};

#endif // SITEMA_H
