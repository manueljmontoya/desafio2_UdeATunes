#include <iostream>
#ifndef SISTEMA_H
#define SISTEMA_H
#include <string>
#include "Usuario.h"
#include "listacanciones.h"
#include "cancion.h"
#include "Anuncio.h"
#include "Artista.h"

class Sistema{

    Usuario* usuarioActivo;
    Usuario** usuarios;
    int totalUsuarios;
    ListaCanciones* canciones;
    int totalCanciones;
    Anuncio** anuncios;
    int totalAnuncios;
    int contadorReproducciones;

public:
    Sistema();
    void ejecutar();
    void cargarDatos();
    void reproducirAleatorio();
    void reproducirAleatorio(ListaFavoritos* lista);
    void cargarLista();
    void reproducirLista(int modo);
};

#endif // SISTEMA_H
