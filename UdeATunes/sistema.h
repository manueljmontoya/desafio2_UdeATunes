#include <iostream>
#ifndef SISTEMA_H
#define SISTEMA_H
#include <string>
#include "Usuario.h"
#include "listacanciones.h"
#include "cancion.h"
#include "Anuncio.h"
#include "Artista.h"
#include "SistemaAnuncios.h"

class Sistema{

    Usuario* usuarioActivo;
    Usuario** usuarios;
    int totalUsuarios;
    ListaCanciones* canciones;
    int totalCanciones;
    int contadorReproducciones;
    SistemaAnuncios* anuncios;
    int totalAnuncios;

public:
    Sistema();
    void ejecutar();
    void cargarDatos();
    void reproducirAleatorio();
    void reproducirAleatorio(ListaFavoritos* lista);
    void cargarLista();
    void reproducirLista(int modo);

    bool login(string nickname);
    void cerrarSesion();
    void mostrarMenuLogin();
    void mostrarMenuPrincipal();
    void mostrarMenuReproduccion();
    void mostrarMenuFavoritos();

    int leerOpcion(int min, int max);
};

#endif // SISTEMA_H
