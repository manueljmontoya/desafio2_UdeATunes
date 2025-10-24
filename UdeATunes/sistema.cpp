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
    canciones = new ListaCanciones();
    anuncios = new SistemaAnuncios();

}

void Sistema::cargarDatos(){

    ifstream archivo1("data/usuarios.txt");
    string linea;
    int contadorLinea = 0;
    while (getline(archivo1, linea)) {
        if (contadorLinea == 0){
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
        if (contadorLinea == 0){
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

/*
    if (usuarioActivo->esPremium()){
        string seguido = usuarioActivo->getNicknameSeguido();

        for (int i=0;i<totalUsuarios;i++){
            if(usuarios[i]->getNickname() == seguido){
                usuarioActivo->setUsuarioSeguido(usuarios[i]);
            }
        }
    }
*/

}



void Sistema::reproducirAleatorio(){

    int calidad;
    if (usuarioActivo->getTipoMembresia() == "estandar"){
        calidad=1;
    }
    else{
        calidad=2;
    }

    for (int i = 0; i < 5; i++) {
        if (calidad==1 && (contadorReproducciones % 3) == 0) {
            anuncios->mostrarAnuncioAleatorio();
        }

        int indiceAleatorio = rand() % totalCanciones;
        canciones->buscarCancion(indiceAleatorio)->reproducir(calidad);

        std::this_thread::sleep_for(std::chrono::seconds(3));
        contadorReproducciones++;
    }

}

void Sistema::reproducirAleatorio(ListaFavoritos* lista){

    for (int i = 0; i < 5; i++) {
        int indiceAleatorio = rand() % (lista->getCantidadCanciones());
        lista->buscarCancion(indiceAleatorio)->reproducir(2);

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
        int historial[6];
        int cantidadHistorial = 0;
        int indiceActual = 0;
        int opcion;

        while (true) {
            cout << "\nOpciones: (1) siguiente, (2) retroceder, (3) salir → ";
            cin >> opcion;

            if (opcion == 1) {
                if (indiceActual >= usuarioActivo->getCantidadFavoritos()) {
                    cout << "Fin de la lista de canciones.\n";
                    continue;
                }

                usuarioActivo->getListaFavoritos()->buscarCancion(indiceActual)->reproducir(2);

                if (cantidadHistorial < 6) {
                    historial[cantidadHistorial] = indiceActual;
                    cantidadHistorial++;
                } else {
                    for (int i = 0; i < 5; i++)
                        historial[i] = historial[i + 1];
                    historial[5] = indiceActual;
                }

                indiceActual++;
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }

            else if (opcion == 2) {
                if (cantidadHistorial <= 1) {
                    cout << "No hay canciones anteriores.\n";
                } else {
                    cantidadHistorial--;
                    indiceActual = historial[cantidadHistorial - 1];
                    usuarioActivo->getListaFavoritos()->buscarCancion(indiceActual)->reproducir(2);
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                }
            }

            else if (opcion == 3) {
                cout << "Saliendo del reproductor...\n";
                break;
            }
        }
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
        cout << "\n=== UdeATunes ===" << endl;
        cout << " 1. Ingresar a la plataforma" << endl;
        cout << " 2. Salir del sistema" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string nickname;
            cout << "Ingrese su nickname: ";
            cin >> nickname;

            if (login(nickname)) {
                mostrarMenuPrincipal();
            }
        }
        else if (opcion == 2) {
            cout << "¡Hasta pronto!" << endl;
            break;
        }
        else {
            cout << "Opcion invalida." << endl;
        }
    }
}

void Sistema::mostrarMenuPrincipal() {
    int opcion;

    while (usuarioActivo != nullptr) {
        cout << "\n=== UdeATunes ===" << endl;
        cout << "Usuario: " << usuarioActivo->getNickname() << endl;

        if (usuarioActivo->esPremium()) {
            cout << "Tipo: Premium" << endl;
        } else {
            cout << "Tipo: Estandar" << endl;
        }

        if (usuarioActivo->esPremium()) {

            cout << " 1. Reproducir aleatorio" << endl;
            cout << " 2. Reproducir mis favoritos" << endl;
            cout << " 3. Cerrar sesion" << endl;
            cout << "Opcion: ";
            cin >> opcion;

            if (opcion == 1) {
                cout << "Reproduciendo musica aleatoria..." << endl;
                reproducirAleatorio();
            }
            else if (opcion == 2) {
                mostrarMenuFavoritos();
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
            cout << "Opcion: ";
            cin >> opcion;

            if (opcion == 1) {
                reproducirAleatorio();
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


void Sistema::mostrarMenuFavoritos() {
    int opcion;
    bool volver = false;

    while (!volver) {
        cout << "=== Mi Lista de Favoritos ===" << endl;
        cout << " 1. Editar mi lista de favoritos" << endl;
        cout << " 2. Seguir otra lista de favoritos" << endl;
        cout << " 3. Ejecutar mi lista de favoritos" << endl;
        cout << " 4. Volver al menú principal" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            menuEditarFavoritos();
        }
        else if (opcion == 2) {
            seguirListaFavoritos();
        }
        else if (opcion == 3) {
            menuEjecutarFavoritos();
        }
        else if (opcion == 4) {
            volver = true;
        }
        else {
            cout << "Opcion invalida." << endl;
        }
    }
}

void Sistema::menuEditarFavoritos() {
    int opcion;
    bool volver = false;

    while (!volver) {
        cout << "=== Editar Mi Lista de Favoritos ===" << endl;
        cout << " 1. Agregar canción por ID" << endl;
        cout << " 2. Eliminar canción por ID" << endl;
        cout << " 3. Volver" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string idCancion;
            cout << "Ingrese el ID de la cancion: ";
            cin >> idCancion;
            agregarFavorito(idCancion);
        }
        else if (opcion == 2) {
            string idCancion;
            cout << "Ingrese el ID de la cancion a eliminar: ";
            cin >> idCancion;
            eliminarFavorito(idCancion);
        }
        else if (opcion == 3) {
            volver = true;
        }
        else {
            cout << "Opcion invalida." << endl;
        }
    }
}

void Sistema::menuEjecutarFavoritos() {
    int opcion;
    bool volver = false;

    while (!volver) {
        cout << "\n=== Ejecutar Mi Lista de Favoritos ===" << endl;
        cout << "¿Como desea reproducir?" << endl;
        cout << " 1. Orden original" << endl;
        cout << " 2. Orden aleatorio" << endl;
        cout << " 3. Volver" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            reproducirLista(2);
            volver = true;
        }
        else if (opcion == 2) {
            reproducirLista(1);
            volver = true;
        }
        else if (opcion == 3) {
            volver = true;
        }
        else {
            cout << "Opcion invalida." << endl;
        }
    }
}

void Sistema::seguirListaFavoritos() {
    string nickname;
    cout << "=== Seguir Lista de Favoritos ===" << endl;
    cout << "Ingrese el nickname del usuario a seguir: ";
    cin >> nickname;

    if (seguirListaUsuario(nickname)) {
        cout << "Ahora sigues la lista de " << nickname << endl;
    } else {
        cout << "Error: No se pudo seguir la lista de " << nickname << endl;
    }
}

void Sistema::agregarFavorito(string idCancion) {
    if (!usuarioActivo->esPremium()) {
        cout << "Error: Solo usuarios premium pueden agregar favoritos" << endl;
        return;
    }

    try {
        int id = stoi(idCancion);
        Cancion* cancion = canciones->buscarCancion(id);

        if (cancion == nullptr) {
            cout << "Error: Cancion con ID " << id << " no encontrada." << endl;
            return;
        }

        if (usuarioActivo->agregarAFavoritos(cancion)) {
            cout << "Cancion agregada a favoritos." << endl;
        } else {
            cout << "Error: Cancion ya esta en favoritos" << endl;
        }
    } catch (...) {
        cout << "Error: ID invalido" << endl;
    }
}

void Sistema::eliminarFavorito(string idCancion) {
    if (!usuarioActivo->esPremium()) {
        cout << "Error: Solo usuarios premium pueden eliminar favoritos" << endl;
        return;
    }

    try {
        int id = stoi(idCancion);

        if (usuarioActivo->eliminarDeFavoritos(id)) {
            cout << "Cancion eliminada de favoritos." << endl;
        } else {
            cout << "Error: la cancion no fue encontrada en favoritos" << endl;
        }
    } catch (...) {
        cout << "Error: ID invalido" << endl;
    }
}

bool Sistema::seguirListaUsuario(string nickname) {
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i]->getNickname() == nickname) {
            return usuarioActivo->seguirUsuario(usuarios[i]);
        }
    }
    cout << "Usuario '" << nickname << "' no encontrado." << endl;
    return false;
}

void Sistema::ejecutar() {
    cargarDatos();
    mostrarMenuLogin();
}
