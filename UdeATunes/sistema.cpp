#include <iostream>
#include <fstream>
#include "sistema.h"
#include <string>
#include "Usuario.h"
#include "Metricas.h"
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
    Metricas::iniciarMedicion("Cargar Datos Sistema");

    ifstream archivo1("data/usuarios.txt");
    Metricas::agregarIteraciones(1);

    if (!archivo1.is_open()) {
        cout << "Error abriendo archivos de usuarios." << endl;
        Metricas::agregarIteraciones(2);
    }
    Metricas::agregarIteraciones(1);

    string linea;
    int contadorLinea = 0;
    Metricas::agregarIteraciones(2);

    while (getline(archivo1, linea)) {
        Metricas::agregarIteraciones(2);

        if (contadorLinea == 0){
            Metricas::agregarIteraciones(1);
            int intLinea=stoi(linea);
            usuarios = new Usuario*[intLinea];

            size_t memoriaUsuarios = sizeof(Usuario*) * intLinea;
            Metricas::agregarMemoria(memoriaUsuarios);

            contadorLinea++;
            Metricas::agregarIteraciones(3);

        }
        else{
            Metricas::agregarIteraciones(1);

            size_t pos1 = linea.find(';');
            size_t pos2 = linea.find(';', pos1 + 1);
            size_t pos3 = linea.find(';', pos2 + 1);
            size_t pos4 = linea.find(';', pos3 + 1);
            size_t pos5 = linea.find(';', pos4 + 1);
            Metricas::agregarIteraciones(5);

            string nickname = linea.substr(0, pos1);
            string tipo = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string ciudad = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            string pais = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            string fecha = linea.substr(pos4 + 1, pos5 - pos4 -1);
            string usuarioSiguiendo = linea.substr(pos5 + 1);
            Metricas::agregarIteraciones(6);

            usuarios[totalUsuarios] = new Usuario(nickname,tipo,ciudad,pais,fecha,usuarioSiguiendo);
            totalUsuarios++;
            Metricas::agregarIteraciones(2);
        }
    }
    archivo1.close();
    Metricas::agregarIteraciones(1);

    ifstream archivo2("data/canciones.txt");
    linea="";
    contadorLinea=0;
    Metricas::agregarIteraciones(3);

    while (getline(archivo2, linea)) {
        Metricas::agregarIteraciones(2);

        if (contadorLinea == 0){
            Metricas::agregarIteraciones(1);
            int cantidadCanciones=stoi(linea);
            canciones->setCapacidad(cantidadCanciones);
            contadorLinea++;
            Metricas::agregarIteraciones(3);
        }
        else{
            Metricas::agregarIteraciones(1);

            size_t pos1 = linea.find(';');
            size_t pos2 = linea.find(';', pos1 + 1);
            size_t pos3 = linea.find(';', pos2 + 1);
            size_t pos4 = linea.find(';', pos3 + 1);
            size_t pos5 = linea.find(';', pos4 + 1);
            size_t pos6 = linea.find(';', pos5 + 1);
            Metricas::agregarIteraciones(6);

            string strId = linea.substr(0, pos1);
            int id = stoi(strId);
            string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string strIdAlbum = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            int idAlbum = stoi(strIdAlbum);
            string strDuracion = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            float duracion = stof(strDuracion);
            string ruta1 = linea.substr(pos4 + 1, pos5 - pos4 - 1);
            string ruta2 = linea.substr(pos5 + 1, pos6 - pos5 - 1);
            string strRepro = linea.substr(pos6 + 1);
            int reproducciones = stoi(strRepro);
            Metricas::agregarIteraciones(10);

            Cancion* cancionActual= new Cancion(id,duracion,reproducciones,ruta1,ruta2,
                                                 nombre,idAlbum);
            bool agregada=canciones->agregar(cancionActual);
            Metricas::agregarIteraciones(2);

            if (agregada){
                Metricas::agregarIteraciones(1);
                totalCanciones++;
                Metricas::agregarIteraciones(1);
            }
            else Metricas::agregarIteraciones(1);
        }
    }
    archivo2.close();
    Metricas::agregarIteraciones(1);

    anuncios->cargarAnunciosDesdeArchivos();
    Metricas::agregarIteraciones(1);

    Metricas::finalizarMedicion();
}



void Sistema::reproducirAleatorio(){

    Metricas::iniciarMedicion("Reproduccion Aleatoria");

    int calidad;
    if (usuarioActivo->getTipoMembresia() == "estandar"){
        calidad=1;
        Metricas::agregarIteraciones(2);
    }
    else{
        calidad=2;
        Metricas::agregarIteraciones(2);
    }

    for (int i = 0; i < 5; i++) {

        Metricas::agregarIteraciones(1);

        if (calidad==1 && (contadorReproducciones % 3) == 0) {
            Metricas::agregarIteraciones(3);
            anuncios->mostrarAnuncioAleatorio();
        }

        int indiceAleatorio = rand() % totalCanciones;
        Metricas::agregarIteraciones(2);
        canciones->getCancion(indiceAleatorio)->reproducir(calidad);

        std::this_thread::sleep_for(std::chrono::seconds(3));
        contadorReproducciones++;
        Metricas::agregarIteraciones(1);
    }

    Metricas::finalizarMedicion();
}

void Sistema::reproducirAleatorio(ListaFavoritos* lista){
    Metricas::iniciarMedicion("Reproducir Aleatorio Favoritos");

    for (int i = 0; i < 5; i++) {
        Metricas::agregarIteraciones(1);

        int indiceAleatorio = rand() % (lista->getCantidadCanciones());
        Metricas::agregarIteraciones(3);

        lista->getCancion(indiceAleatorio)->reproducir(2);
        Metricas::agregarIteraciones(1);

        std::this_thread::sleep_for(std::chrono::seconds(3));
        Metricas::agregarIteraciones(1);
    }

    Metricas::finalizarMedicion();
}


void Sistema::reproducirLista(int modo){
    Metricas::iniciarMedicion("Reproducir Lista Favoritos");

    if (modo==1){
        Metricas::agregarIteraciones(1);
        reproducirAleatorio(usuarioActivo->getListaFavoritos());
        Metricas::agregarIteraciones(1);
    }
    else{
        Metricas::agregarIteraciones(1);

        int historial[6];
        int cantidadHistorial = 0;
        int indiceActual = 0;
        int opcion;
        Metricas::agregarIteraciones(4);

        while (true) {
            Metricas::agregarIteraciones(1);

            cout << "\nOpciones: (1) siguiente, (2) retroceder, (3) salir → ";
            cin >> opcion;

        Metricas::agregarIteraciones(2);

            if (opcion == 1) {
                Metricas::agregarIteraciones(1);

                cout<<indiceActual<<","<<usuarioActivo->getCantidadFavoritos();

                if (indiceActual >= usuarioActivo->getCantidadFavoritos()) {
                    Metricas::agregarIteraciones(2);
                    cout << "Fin de la lista de canciones.\n";
                    Metricas::agregarIteraciones(1);
                    continue;
                }
                else Metricas::agregarIteraciones(1);

                usuarioActivo->getListaFavoritos()->getCancion(indiceActual)->reproducir(2);
                Metricas::agregarIteraciones(1);

                if (cantidadHistorial < 6) {
                    Metricas::agregarIteraciones(1);
                    historial[cantidadHistorial] = indiceActual;
                    cantidadHistorial++;
                    Metricas::agregarIteraciones(2);
                } else {
                    Metricas::agregarIteraciones(1);
                    for (int i = 0; i < 5; i++){
                        Metricas::agregarIteraciones(1);
                        historial[i] = historial[i + 1];
                        Metricas::agregarIteraciones(1);
                    historial[5] = indiceActual;
                    Metricas::agregarIteraciones(1);
                }
                }

                indiceActual++;
                std::this_thread::sleep_for(std::chrono::seconds(3));
                Metricas::agregarIteraciones(2);
            }

            else if (opcion == 2) {
                Metricas::agregarIteraciones(1);
                if (cantidadHistorial <= 1) {
                    Metricas::agregarIteraciones(1);
                    cout << "No hay canciones anteriores.\n";
                    Metricas::agregarIteraciones(1);
                } else {
                    Metricas::agregarIteraciones(1);

                    cantidadHistorial--;
                    indiceActual = historial[cantidadHistorial - 1];
                    usuarioActivo->getListaFavoritos()->getCancion(indiceActual)->reproducir(2);
                    std::this_thread::sleep_for(std::chrono::seconds(3));

                    Metricas::agregarIteraciones(4);
                }
            }

            else if (opcion == 3) {
                Metricas::agregarIteraciones(1);
                cout << "Saliendo del reproductor...\n";
                Metricas::agregarIteraciones(1);
                break;
            }
        }
    }

}

bool Sistema::login(string nickname) {
    Metricas::iniciarMedicion("Login Usuario");

    if (usuarios == nullptr || totalUsuarios == 0) {
        Metricas::agregarIteraciones(2);
        cout << "No hay usuarios en el sistema" << endl;
        Metricas::finalizarMedicion();
        return false;
    }
    for (int i = 0; i < totalUsuarios; i++) {
        Metricas::agregarIteraciones(1);
        if (usuarios[i]->getNickname() == nickname) {
            Metricas::agregarIteraciones(1);
            usuarioActivo = usuarios[i];
            Metricas::agregarIteraciones(1);

            if (usuarioActivo->esPremium()){
                Metricas::agregarIteraciones(1);
                usuarioActivo->setListaFavoritos(usuarioActivo,canciones);
                Metricas::agregarIteraciones(1);

                if (usuarioActivo->getNicknameSeguido() != "no_aplica"){
                    Metricas::agregarIteraciones(1);
                    string seguido = usuarioActivo->getNicknameSeguido();
                    Metricas::agregarIteraciones(1);

                    for (int i=0;i<totalUsuarios;i++){
                        Metricas::agregarIteraciones(1);
                        if(usuarios[i]->getNickname() == seguido){
                            Metricas::agregarIteraciones(1);
                            usuarioActivo->setUsuarioSeguido(usuarios[i]);
                            usuarios[i]->setListaFavoritos(usuarios[i],canciones);
                            Metricas::agregarIteraciones(3);
                            break;
                        }
                        else Metricas::agregarIteraciones(1);
                    }
                    usuarioActivo->generarListaReproduccion(usuarioActivo);
                    Metricas::agregarIteraciones(1);
                }
                else Metricas::agregarIteraciones(1);

            }

            Metricas::finalizarMedicion();
            return true;
        }
        else Metricas::agregarIteraciones(1);
    }
    Metricas::finalizarMedicion();
    return false;
}

void Sistema::cerrarSesion() {
    delete usuarioActivo;
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
            delete usuarios;
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
            cout << " 2. Opciones lista de favoritos" << endl;
            cout << " 3. Cerrar sesion" << endl;
            cout << "Opcion: ";
            cin >> opcion;

            if (opcion == 1) {
                cout << "\nReproduciendo musica aleatoria..." << endl;
                reproducirAleatorio();
            }
            else if (opcion == 2) {
                if (usuarioActivo->getListaFavoritos() == nullptr){
                    cout<<"\nTu lista de favoritos esta vacia y aun no sigues a \nningun usuario con una lista da favoritos";
                }
                else{
                    mostrarMenuFavoritos();
                }
            }
            else if (opcion == 3) {
                cerrarSesion();
            }
            else {
                cout << "\nOpcion invalida" << endl;
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
                cout << "\nOpción invalida" << endl;
            }
        }
    }
}


void Sistema::mostrarMenuFavoritos() {
    int opcion;
    bool volver = false;

    while (!volver) {
        cout << "\n=== Mi Lista de Favoritos ===" << endl;
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
        cout << "\n=== Editar Mi Lista de Favoritos ===" << endl;
        cout << " 1. Agregar canción por ID" << endl;
        cout << " 2. Eliminar canción por ID" << endl;
        cout << " 3. Volver" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string idCancion;
            cout << "\nIngrese el ID de la cancion: ";
            cin >> idCancion;
            agregarFavorito(idCancion);
        }
        else if (opcion == 2) {
            string idCancion;
            cout << "\nIngrese el ID de la cancion a eliminar: ";
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
        cout << "\n¿Como desea reproducir?" << endl;
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
    cout << "\n=== Seguir Lista de Favoritos ===" << endl;
    cout << "Ingrese el nickname del usuario a seguir: ";
    cin >> nickname;

    if (seguirListaUsuario(nickname)) {
        cout << "Ahora sigues la lista de " << nickname << endl;
    } else {
        cout << "Error: No se pudo seguir la lista de " << nickname << endl;
    }
}

void Sistema::agregarFavorito(string idCancion) {
    Metricas::iniciarMedicion("Agregar Favorito");

    if (!usuarioActivo->esPremium()) {
        Metricas::agregarIteraciones(2);
        cout << "Error: Solo usuarios premium pueden agregar favoritos" << endl;
        Metricas::finalizarMedicion();
        return;
    }
    Metricas::agregarIteraciones(1);

    try {
        int id = stoi(idCancion);
        Cancion* cancion = canciones->buscarCancion(id);
        Metricas::agregarIteraciones(2);

        if (cancion == nullptr) {
            Metricas::agregarIteraciones(2);
            cout << "Error: Cancion con ID " << id << " no encontrada." << endl;
            Metricas::finalizarMedicion();
            return;
        }
        Metricas::agregarIteraciones(1);

        if (usuarioActivo->agregarAFavoritos(cancion)) {
            Metricas::agregarIteraciones(2);
            cout << "Cancion agregada a favoritos." << endl;
        } else {
            Metricas::agregarIteraciones(2);
            cout << "Error: Cancion ya esta en favoritos" << endl;
        }
    } catch (...) {
        Metricas::agregarIteraciones(2);
        cout << "Error: ID invalido" << endl;
    }
    Metricas::finalizarMedicion();
}

void Sistema::eliminarFavorito(string idCancion) {
    Metricas::iniciarMedicion("Eliminar Favorito");

    if (!usuarioActivo->esPremium()) {
        Metricas::agregarIteraciones(1);
        cout << "Error: Solo usuarios premium pueden eliminar favoritos" << endl;
        Metricas::finalizarMedicion();
        return;
    }

    try {
        int id = stoi(idCancion);
        Metricas::agregarIteraciones(1);

        if (usuarioActivo->eliminarDeFavoritos(id)) {
            Metricas::agregarIteraciones(2);
            cout << "Cancion eliminada de favoritos." << endl;
        } else {
            cout << "Error: la cancion no fue encontrada en favoritos" << endl;
            Metricas::agregarIteraciones(2);
        }
    } catch (...) {
        Metricas::agregarIteraciones(2);
        cout << "Error: ID invalido" << endl;
    }

    Metricas::finalizarMedicion();
}

bool Sistema::seguirListaUsuario(string nickname) {
    Metricas::iniciarMedicion("Seguir Lista Usuario");

    for (int i = 0; i < totalUsuarios; i++) {
        Metricas::agregarIteraciones(1);

        if (usuarios[i]->getNickname() == nickname) {
            Metricas::agregarIteraciones(2);
            bool resultado = usuarioActivo->seguirUsuario(usuarios[i]);
            Metricas::finalizarMedicion();
            return resultado;
        }
        Metricas::agregarIteraciones(1);
    }
    Metricas::agregarIteraciones(1);
    cout << "Usuario '" << nickname << "' no encontrado." << endl;
    Metricas::finalizarMedicion();
    return false;
}

void Sistema::ejecutar() {
    cargarDatos();
    mostrarMenuLogin();
}
