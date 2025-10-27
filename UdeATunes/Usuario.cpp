#include "Usuario.h"
#include "listaFavoritos.h"
#include "cancion.h"
#include <fstream>

Usuario::Usuario() {
    Metricas::iniciarMedicion("Constructor Usuario por defecto");

    nickname = "invitado";
    tipoMembresia = "estandar";
    ciudad = "Desconocida";
    pais = "Desconocido";
    fechaInscripcion = "01/01/2025";
    listaFavoritos = nullptr;
    usuarioSeguido = nullptr;

    size_t memoria = sizeof(*this) +
                    Metricas::calcularMemoriaString(nickname) +
                    Metricas::calcularMemoriaString(tipoMembresia) +
                    Metricas::calcularMemoriaString(ciudad) +
                    Metricas::calcularMemoriaString(pais) +
                    Metricas::calcularMemoriaString(fechaInscripcion);
    Metricas::agregarMemoria(memoria);

    Metricas::finalizarMedicion();

}

Usuario::Usuario(string nick, string tipo, string ciu, string pa, string fecha, string seguido) {
    Metricas::iniciarMedicion("Constructor Usuario Parametrizado");

    nickname = nick;
    nicknameUsuarioSeguido=seguido;
    Metricas::agregarIteraciones(2);

    if (tipo != "estandar" && tipo != "premium") {
        Metricas::agregarIteraciones(2);
        tipoMembresia = "estandar";
        Metricas::agregarIteraciones(1);

    } else {
        Metricas::agregarIteraciones(1);
        tipoMembresia = tipo;
        Metricas::agregarIteraciones(1);
    }

    ciudad = ciu;
    pais = pa;
    fechaInscripcion = fecha;
    Metricas::agregarIteraciones(3);

    if (esPremium()) {
        Metricas::agregarIteraciones(1);
        listaFavoritos = new ListaFavoritos(this);
        Metricas::agregarIteraciones(1);
    } else {
        Metricas::agregarIteraciones(1);
        listaFavoritos = nullptr;
        Metricas::agregarIteraciones(1);
    }

    size_t memoria = sizeof(*this) +
                    Metricas::calcularMemoriaString(nickname) +
                    Metricas::calcularMemoriaString(tipoMembresia) +
                    Metricas::calcularMemoriaString(ciudad) +
                    Metricas::calcularMemoriaString(pais) +
                    Metricas::calcularMemoriaString(fechaInscripcion) +
                    Metricas::calcularMemoriaString(nicknameUsuarioSeguido);
    Metricas::agregarMemoria(memoria);

    Metricas::finalizarMedicion();
}


bool Usuario::seguirUsuario(Usuario* otroUsuario) {
    Metricas::iniciarMedicion("seguir Usuario");

    if (!this->esPremium()) {
        Metricas::agregarIteraciones(1);
        cout << nickname << " no es premium - no puedes seguir a otro usuario" << endl;
        Metricas::agregarIteraciones(1);
        Metricas::finalizarMedicion();
        return false;
    }
    Metricas::agregarIteraciones(1);

    if (!otroUsuario->esPremium()) {
        Metricas::agregarIteraciones(1);
        cout << otroUsuario->nickname << " no es premium - no se puede seguir" << endl;
        Metricas::agregarIteraciones(1);
        Metricas::finalizarMedicion();
        return false;
    }
    Metricas::agregarIteraciones(1);

    if (this == otroUsuario) {
        Metricas::agregarIteraciones(1);
        cout << " No puedes seguirte a ti mismo" << endl;
        Metricas::agregarIteraciones(1);
        Metricas::finalizarMedicion();
        return false;
    }
    Metricas::agregarIteraciones(1);

    if (usuarioSeguido != nullptr) {
        Metricas::agregarIteraciones(1);
        cout << "Ya estas siguiendo a " << usuarioSeguido->getNickname() << endl;
        cout << "Debes dejar de seguirlo primero" << endl;
        Metricas::agregarIteraciones(2);
        Metricas::finalizarMedicion();
        return false;
    }

    usuarioSeguido = otroUsuario;
    cout << nickname << " ahora sigue a " << otroUsuario->getNickname() << endl;
    Metricas::agregarIteraciones(2);
    Metricas::finalizarMedicion();
    return true;
}

bool Usuario::dejarDeSeguir() {
    Metricas::iniciarMedicion("dejar de seguir Usuario");

    if (usuarioSeguido == nullptr) {
        Metricas::agregarIteraciones(1);
        cout << nickname << " no está siguiendo a nadie" << endl;
        Metricas::agregarIteraciones(1);
        Metricas::finalizarMedicion();
        return false;
    }
    Metricas::agregarIteraciones(1);

    cout << nickname << " dejó de seguir a " << usuarioSeguido->getNickname() << endl;
    Metricas::agregarIteraciones(1);
    usuarioSeguido = nullptr;
    Metricas::agregarIteraciones(1);
    Metricas::finalizarMedicion();
    return true;
}

void Usuario::generarListaReproduccion(Usuario* usuario) {
    Metricas::iniciarMedicion("Generar lista de reproduccion");

    int totalCanciones = this->getCantidadFavoritos();
    Metricas::agregarIteraciones(1);

    if (usuarioSeguido != nullptr) {
        Metricas::agregarIteraciones(1);
        totalCanciones += usuarioSeguido->getCantidadFavoritos();
        Metricas::agregarIteraciones(1);
    }
    else Metricas::agregarIteraciones(1);

    ListaFavoritos* listaTemporal = new ListaFavoritos(usuario);
    listaTemporal->setCapacidad(totalCanciones);
    int indice = 0;
    Metricas::agregarIteraciones(3);

    if (listaFavoritos != nullptr) {

        for (int i = 0; i < this->getCantidadFavoritos(); i++) {
            Metricas::agregarIteraciones(1);
            listaTemporal->agregarCancion(listaFavoritos->getCancion(i));
            indice++;
            Metricas::agregarIteraciones(2);
        }

        size_t memoriaAnterior = sizeof(*listaFavoritos);
        Metricas::removerMemoria(memoriaAnterior);
        delete listaFavoritos;
        Metricas::agregarIteraciones(1); // por removerMemoria + delete
    }
    Metricas::agregarIteraciones(1); // por la condición

    if (usuarioSeguido != nullptr) {
        Metricas::agregarIteraciones(1);
        for (int i = 0; i < usuarioSeguido->getCantidadFavoritos(); i++) {
            Metricas::agregarIteraciones(1);
            listaTemporal->agregarCancion(usuarioSeguido->listaFavoritos->getCancion(i));
            indice++;
            Metricas::agregarIteraciones(1);
        }
    }
    else Metricas::agregarIteraciones(1);

    Metricas::agregarIteraciones(1);
    listaFavoritos=listaTemporal;
    Metricas::finalizarMedicion();
}

void Usuario::setListaFavoritos(Usuario* usuario, ListaCanciones* canciones){
    Metricas::iniciarMedicion("Set lista favoritos");

    ListaFavoritos* listaUsuario = new ListaFavoritos(usuario);
    Metricas::agregarIteraciones(1); // por new

    size_t memoriaNueva = sizeof(*listaUsuario);
    Metricas::agregarMemoria(memoriaNueva);
    Metricas::agregarIteraciones(1); // por agregarMemoria

    ifstream archivo("data/listas_favoritos.txt");
    Metricas::agregarIteraciones(1);
    string linea;

    bool encontrada = false;

    while (getline(archivo, linea)) {
        Metricas::agregarIteraciones(1);

        size_t pos1 = linea.find(';');
        Metricas::agregarIteraciones(1);
        string propietario = linea.substr(0, pos1);
        Metricas::agregarIteraciones(1);

        if (propietario == this->nickname) {
            encontrada = true;
            Metricas::agregarIteraciones(1);

            size_t pos2 = linea.find(';', pos1 + 1);
            Metricas::agregarIteraciones(1);
            string strCantidad = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            Metricas::agregarIteraciones(1);
            int cantidadCanciones = stoi(strCantidad);
            Metricas::agregarIteraciones(1);

            size_t inicio = pos2 + 1;
            size_t fin;

            if (cantidadCanciones == 0){
                listaFavoritos = nullptr;
            }
            else{
                listaUsuario->setCapacidad(cantidadCanciones);
                Metricas::agregarIteraciones(1);
                while ((fin = linea.find(';', inicio)) != string::npos) {
                    Metricas::agregarIteraciones(1);

                    string idCancion = linea.substr(inicio, fin - inicio);
                    Metricas::agregarIteraciones(1);
                    int intIdCancion = stoi(idCancion);
                    Metricas::agregarIteraciones(1);
                    listaUsuario->agregarCancion(canciones->buscarCancion(intIdCancion));
                    Metricas::agregarIteraciones(1);
                    inicio = fin + 1;
                }

                string ultimoIdCancion = linea.substr(inicio);
                if (!ultimoIdCancion.empty()) {
                    Metricas::agregarIteraciones(1);
                    int intIdCancion = stoi(ultimoIdCancion);
                    Metricas::agregarIteraciones(1);
                    listaUsuario->agregarCancion(canciones->buscarCancion(intIdCancion));
                    Metricas::agregarIteraciones(1);
                }
                Metricas::agregarIteraciones(1);
            }
            break;
        }
        Metricas::agregarIteraciones(1);
    }
    archivo.close();
    Metricas::agregarIteraciones(1);

    if (encontrada) {
        listaFavoritos = listaUsuario;
    } else {
        delete listaUsuario;
        listaFavoritos = nullptr;
    }

    Metricas::agregarIteraciones(1);

    Metricas::finalizarMedicion();
}

void Usuario::liberarListaReproduccion(Cancion** lista) {
    if (lista != nullptr) {
        delete[] lista;
    }
}

Usuario::~Usuario() {
    Metricas::iniciarMedicion("Destructor Usuario");

    string linea;
    Metricas::agregarIteraciones(1);

    ifstream inUsuarios("data/usuarios.txt");
    ofstream tempUsuarios("data/usuarios_temp.txt");
    Metricas::agregarIteraciones(2);


    while (getline(inUsuarios, linea)) {
        Metricas::agregarIteraciones(1);

        size_t pos1 = 0, pos2 = 0;
        string campos[6];
        int i = 0;
        Metricas::agregarIteraciones(3);

        while (i < 5 && (pos2 = linea.find(';', pos1)) != string::npos) {
            Metricas::agregarIteraciones(1);

            campos[i] = linea.substr(pos1, pos2 - pos1);
            pos1 = pos2 + 1;
            i++;
            Metricas::agregarIteraciones(3);

        }
        campos[i] = linea.substr(pos1);
        Metricas::agregarIteraciones(1);


        if (campos[0] == nickname) {
            Metricas::agregarIteraciones(1);

            campos[5] = nicknameUsuarioSeguido;
            Metricas::agregarIteraciones(1);

        }
        else Metricas::agregarIteraciones(1);


        tempUsuarios << campos[0] << ";" << campos[1] << ";" << campos[2] << ";"
                     << campos[3] << ";" << campos[4] << ";" << campos[5] << "\n";
        Metricas::agregarIteraciones(1);

    }


    inUsuarios.close();
    tempUsuarios.close();
    Metricas::agregarIteraciones(2);


    remove("data/usuarios.txt");
    rename("data/usuarios_temp.txt", "data/usuarios.txt");
    Metricas::agregarIteraciones(2);



    ifstream inListas("data/listas_favoritos.txt");
    ofstream tempListas("data/listas_favoritos_temp.txt");
    Metricas::agregarIteraciones(2);


    bool listaEncontrada = false;
    Metricas::agregarIteraciones(1);

    while (getline(inListas, linea)) {
        Metricas::agregarIteraciones(1);

        size_t pos = linea.find(';');
        string nickLista = linea.substr(0, pos);
        Metricas::agregarIteraciones(2);


        if (nickLista == nickname) {
            Metricas::agregarIteraciones(1);

            tempListas << nickname << ";" << listaFavoritos->getCantidadCanciones() << ";";
            Metricas::agregarIteraciones(1);


            int total = listaFavoritos->getCantidadCanciones();
            Metricas::agregarIteraciones(1);

            for (int i = 0; i < total; i++) {
                Metricas::agregarIteraciones(1);

                tempListas << listaFavoritos->getCancion(i)->getId();
                Metricas::agregarIteraciones(1);

                if (i < total - 1){
                    Metricas::agregarIteraciones(1);

                    tempListas << ";";
                    Metricas::agregarIteraciones(1);
                }
            }
            tempListas << "\n";
            Metricas::agregarIteraciones(1);

            listaEncontrada = true;
            Metricas::agregarIteraciones(1);

        } else {
            Metricas::agregarIteraciones(1);

            tempListas << linea << "\n";
            Metricas::agregarIteraciones(1);

        }
    }

    if (!listaEncontrada) {
        Metricas::agregarIteraciones(1);

        tempListas << nickname << ";" << listaFavoritos->getCantidadCanciones() << ";";
        Metricas::agregarIteraciones(1);

        int total = listaFavoritos->getCantidadCanciones();
        Metricas::agregarIteraciones(1);

        for (int i = 0; i < total; i++) {
            Metricas::agregarIteraciones(1);

            tempListas << listaFavoritos->getCancion(i)->getId();
            Metricas::agregarIteraciones(1);

            if (i < total - 1){
                Metricas::agregarIteraciones(1);

                tempListas << ";";
                Metricas::agregarIteraciones(1);

            }
        }
        tempListas << "\n";
        Metricas::agregarIteraciones(1);

    }


    inListas.close();
    Metricas::agregarIteraciones(1);

    tempListas.close();
    Metricas::agregarIteraciones(1);

    remove("data/listas_favoritos.txt");
    Metricas::agregarIteraciones(1);

    rename("data/listas_favoritos_temp.txt", "data/listas_favoritos.txt");
    Metricas::agregarIteraciones(1);


    if (listaFavoritos != nullptr) {

        size_t memoriaLista = sizeof(*listaFavoritos);
        Metricas::removerMemoria(memoriaLista);
        delete listaFavoritos;
        Metricas::agregarIteraciones(1);
    }
    Metricas::agregarIteraciones(1);

    Metricas::finalizarMedicion();
}

bool Usuario::esPremium() const {
    if (tipoMembresia == "premium") {
        return true;
    } else {
        return false;
    }
}

void Usuario::setTipoMembresia(string tipo) {
    if (tipo != "estandar" && tipo != "premium") {
        return;
    }

    tipoMembresia = tipo;

    if (tipo == "premium" && listaFavoritos == nullptr) {
        listaFavoritos = new ListaFavoritos(this);
    }
    else if (tipo == "estandar" && listaFavoritos != nullptr) {
        delete listaFavoritos;
        listaFavoritos = nullptr;
    }
}

bool Usuario::agregarAFavoritos(Cancion* cancion) {
    if (!esPremium()) {
        return false;
    }
    if (listaFavoritos == nullptr) {
        return false;
    }

    bool resultado = listaFavoritos->agregarCancion(cancion);
    return resultado;
}

bool Usuario::eliminarDeFavoritos(int idCancion) {
    if (!esPremium()) {
        return false;
    }
    if (listaFavoritos == nullptr) {
        return false;
    }

    bool resultado = listaFavoritos->eliminarCancion(idCancion);
    return resultado;
}

int Usuario::getCantidadFavoritos() const {
    if (!esPremium() || listaFavoritos == nullptr) {
        return 0;
    }
    return listaFavoritos->getCantidadCanciones();
}

bool Usuario::operator==(const Usuario& otro) const {
    if (nickname == otro.nickname) {
        return true;
    } else {
        return false;
    }
}

ostream& operator<<(ostream& os, const Usuario& usuario) {

    os << "Usuario: " << usuario.nickname;
    os << " | Tipo: " << usuario.tipoMembresia;
    os << " | Ciudad: " << usuario.ciudad;
    os << " | Pais: " << usuario.pais;
    os << " | Fecha: " << usuario.fechaInscripcion;

    if (usuario.esPremium() && usuario.listaFavoritos != nullptr) {
        os << " | Favoritos: " << usuario.listaFavoritos->getCantidadCanciones();
    }

    return os;
}
