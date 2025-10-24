#include <iostream>
#include <fstream>
#include "sistema.h"
#include <string>
#include "Usuario.h"
#include <cstdlib>
#include <thread>
#include <listafavoritos.h>
#include <listacanciones.h>
#include <SistemaAnuncios.h>

using namespace std;

Sistema::Sistema() {

    usuarioActivo=nullptr;
    usuarios=nullptr;
    totalUsuarios=0;
    totalCanciones=0;
    anuncios=nullptr;
    totalAnuncios=0;
    contadorReproducciones=0;
    *canciones=ListaCanciones();
    *anuncios=SistemaAnuncios();

}

void Sistema::cargarDatos(){

    ifstream archivo1("data/usuarios.txt");
    string linea;
    int contadorLinea=0;
    while (getline(archivo1, linea)) {
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
    archivo1.close();

    ifstream archivo2("data/canciones.txt");
    linea="";
    contadorLinea=0;
    while (getline(archivo2, linea)) {
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

            string strId = linea.substr(0, pos1);
            int id = stoi(strId);
            string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string strIdAlbum = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            int idAlbum = stoi(strIdAlbum);
            string strDuracion = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            float duracion = stof(strDuracion);
            string ruta1 = linea.substr(pos4 + 1, pos5 - pos4 - 1);
            string ruta2 = linea.substr(pos5 + 1, pos4 - pos5 - 1);
            string strRepro = linea.substr(pos6 + 1, pos5 - pos6 - 1);
            int reproducciones = stoi(strRepro);

            Cancion* cancionActual= new Cancion(id,duracion,reproducciones,ruta1,ruta2,
                                                 nombre,idAlbum);
            bool agregada=canciones->agregar(cancionActual);
            if (agregada){
                totalCanciones++;
            }
        }
    }
    archivo2.close();

    anuncios->cargarAnunciosDesdeArchivos();

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
            anuncios->mostrarAnuncioAleatorio();
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
            anuncios->mostrarAnuncioAleatorio();
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
                int intIdCancion = stoi(idCancion);
                listaUsuario->agregarCancion(canciones->buscarCancion(intIdCancion));
                inicio = fin + 1;
            }

            string ultimoIdCancion = linea.substr(inicio);
            if (!ultimoIdCancion.empty()) {
                int intIdCancion = stoi(ultimoIdCancion);
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

bool Sistema::login(string nickname) {

    if (usuarios == nullptr || totalUsuarios == 0) {
        cout << "No hay usuarios en el sistema" << endl;
        return false;
    }
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i]->getNickname() == nickname) {
            usuarioActivo = usuarios[i];
            return true;
        }
    }
    return false;
}

void Sistema::cerrarSesion() {
    usuarioActivo = nullptr;
}

void Sistema::mostrarMenuLogin() {
    int opcion;

    while (true) {
        cout << "\n--- UdeATunes ---" << endl;
        cout << "1. Entrar" << endl;
        cout << "2. Salir" << endl;
        cout << "Opcion > ";
        cin >> opcion;

        if (opcion == 1) {
            string nickname;
            cout << "Usuario: ";
            cin >> nickname;

            if (login(nickname)) {
                cout << "Hola " << nickname << "!" << endl;
                mostrarMenuPrincipal();
                break;
            }
        }
        else if (opcion == 2) {
            break;
        }
    }
}

void Sistema::mostrarMenuPrincipal() {
    int opcion;

    while (usuarioActivo != nullptr) {
        cout << "\n--- UdeATunes ---" << endl;
        cout << "Usuario: " << usuarioActivo->getNickname() << endl;

        if (usuarioActivo->esPremium()) {
            cout << "Tipo: Premium" << endl;
        } else {
            cout << "Tipo: Estandar" << endl;
        }

        if (usuarioActivo->esPremium()) {

            cout << "1. Reproducir aleatorio" << endl;
            cout << "2. Reproducir mis favoritos" << endl;
            cout << "3. Cerrar sesion" << endl;
            cout << "Opcion > ";
            cin >> opcion;

            if (opcion == 1) {
                cout << "Reproduciendo musica aleatoria..." << endl;
            }
            else if (opcion == 2) {
                cout << "Accediendo a mis favoritos..." << endl;
            }
            else if (opcion == 3) {
                cerrarSesion();
            }
            else {
                cout << "Opcion invalida" << endl;
            }
        } else {
            cout << "1. Reproducir aleatorio" << endl;
            cout << "2. Cerrar sesion" << endl;
            cout << "Opcion > ";
            cin >> opcion;

            if (opcion == 1) {
                cout << "Reproduciendo musica aleatoria..." << endl;
            }
            else if (opcion == 2) {
                cerrarSesion();
            }
            else {
                cout << "Opción invalida" << endl;
            }
        }
    }
}

