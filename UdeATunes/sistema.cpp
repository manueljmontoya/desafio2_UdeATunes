#include <iostream>
#include <fstream>
#include "sistema.h"
#include <string>
#include "Usuario.h"
#include <cstdlib>
#include <thread>
#include <listafavoritos.h>

Sistema::Sitema() {

    usuarioActivo=nullptr;
    usuarios=nullptr;
    totalUsuarios=0;
    totalCanciones=0;
    anuncios=nullptr;
    totalAnuncios=0;
    contadorReproducciones=0;
    ListaCanciones canciones();

}

void Sistema::cargarDatos(){

    ifstream archivo("data/usuarios.txt");
    string linea;
    int contadorLinea=0;
    while (getline(archivo, linea)) {
        if (contadorLinea=0){
            int intLinea=stoi(linea);
            usuarios = new Usuario*[intLinea];
        }
        else{
            size_t pos1 = linea.find(';');
            size_t pos2 = linea.find(';', pos1 + 1);
            size_t pos3 = linea.find(';', pos2 + 1);
            size_t pos4 = linea.find(';', pos3 + 1);
            size_t pos5 = linea.find(';', pos4 + 1);

            string nickname = linea.substr(0, pos1);
            string tipo = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string ciudad = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            string pais = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            string fecha = linea.substr(pos4 + 1, pos5 - pos4 -1);
            string usuarioSiguiendo = linea.substr(pos5 + 1);

            usuarios[totalUsuarios] = new Usuario(nickname,tipo,ciudad,pais,fecha,usuarioSiguiendo);
            totalUsuarios++;
        }
    }
    archivo.close();

    ifstream archivo("data/canciones.txt");
    string linea;
    int contadorLinea=0;
    while (getline(archivo, linea)) {
        if (contadorLinea=0){
            int cantidadCanciones=stoi(linea);
            canciones->setCapacidad(cantidadCanciones);
        }
        else{
            size_t pos1 = linea.find(';');
            size_t pos2 = linea.find(';', pos1 + 1);
            size_t pos3 = linea.find(';', pos2 + 1);
            size_t pos4 = linea.find(';', pos3 + 1);
            size_t pos5 = linea.find(';', pos4 + 1);
            size_t pos6 = linea.find(';', pos5 + 1);
            size_t pos7 = linea.find(';', pos6 + 1);
            size_t pos8 = linea.find(';', pos7 + 1);

            string idCancion = linea.substr(0, pos1);
            string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string idAlbum = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            string duracion = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            string ruta1 = linea.substr(pos4 + 1, pos5 - pos4 - 1);
            string ruta2 = linea.substr(pos5 + 1, pos4 - pos5 - 1);
            string reproducciones = linea.substr(pos6 + 1, pos5 - pos6 - 1);
            string cantante = linea.substr(pos7 + 1, pos6 - pos7 - 1);
            string idCreditos = linea.substr(por8 + 1);

            Cancion* cancionActual= new Cancion(idCancion,duracion,reproducciones,
                                            idcreditos,ruta1,ruta2,nombre,idAlbum);
            bool agregada=canciones->agregar(cancionActual);
            if (agregada){
                totalCanciones++;
            }
        }
    }
    archivo.close();

}



void Sistema::reproducirAleatorio(){

    int calidad;
    if (usuarioActivo->getTipoMembresia() == "estandar"){
        calidad=1;
    }
    else{
        calidad=2;
    }

    while (true) {

        if (calidad=1 && (contadorReproducciones%3==0)){
            //mostrar anuncio
        }

        for (int i = 0; i < 5; i++) {
            int indiceAleatorio = rand() % totalCanciones;
            canciones->buscarCancion(indiceAleatorio)->reproducir(calidad);
            contadorReproducciones++;
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

}

void Sistema::reproducirAleatorio(ListaFavoritos* lista){

    int calidad;
    if (usuarioActivo->getTipoMembresia() == "estandar"){
        calidad=1;
    }
    else{
        calidad=2;
    }

    while (true) {

        if (calidad=1 && (contadorReproducciones%3==0)){
            //mostrar anuncio
        }

        for (int i = 0; i < 5; i++) {
            int indiceAleatorio = rand() % totalCanciones;
            lista->buscarCancion(indiceAleatorio)->reproducir(calidad);
            contadorReproducciones++;
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

}

void Sistema::cargarLista(){

    ListaFavoritos* listaUsuario = new ListaFavoritos(usuarioActivo);

    ifstream archivo("data/listas_favoritos.txt");
    string linea;

    while (getline(archivo, linea)) {
        size_t pos1 = linea.find(';');
        string propietario = linea.substr(0, pos1);

        if (propietario == usuarioActivo->getNickname()) {
            size_t inicio = pos1 + 1;
            size_t fin;

            while ((fin = linea.find(';', inicio)) != string::npos) {
                string idCancion = linea.substr(inicio, fin - inicio);
                int intIdCancion = toint(idCancion);
                listaUsuario->agregarCancion(canciones->buscarCancion(intIdCancion));
                inicio = fin + 1;
            }

            string ultimoIdCancion = linea.substr(inicio);
            if (!ultimoIdCancion.empty()) {
                int intIdCancion = toint(ultimoIdCancion);
                listaUsuario->agregarCancion(canciones->buscarCancion(intIdCancion));
            }
        }
    }
    archivo.close();

    usuarioActivo->setListaFavoritos(listaUsuario);

}


void Sistema::reproducirLista(int modo){

    if (modo==1){
        reproducirAleatorio(usuarioActivo->getListaFavoritos());
    }
    else{
        for (int i=0; i<usuarioActivo->getListaFavoritos()->getCantidadCanciones(); i++){
            int indiceAleatorio = rand() % totalCanciones;
            usuarioActivo->getListaFavoritos()->buscarCancion(indiceAleatorio)->reproducir(2);
            contadorReproducciones++;
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

}
