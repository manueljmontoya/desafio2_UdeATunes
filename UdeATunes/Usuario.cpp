#include "Usuario.h"
#include "listaFavoritos.h"
#include "cancion.h"
#include <fstream>

Usuario::Usuario() {
    nickname = "invitado";
    tipoMembresia = "estandar";
    ciudad = "Desconocida";
    pais = "Desconocido";
    fechaInscripcion = "01/01/2025";
    listaFavoritos = nullptr;
    usuarioSeguido = nullptr;
}

Usuario::Usuario(string nick, string tipo, string ciu, string pa, string fecha, string seguido) {
    nickname = nick;
    nicknameUsuarioSeguido=seguido;

    if (tipo != "estandar" && tipo != "premium") {
        tipoMembresia = "estandar";
    } else {
        tipoMembresia = tipo;
    }

    ciudad = ciu;
    pais = pa;
    fechaInscripcion = fecha;

    if (esPremium()) {
        listaFavoritos = new ListaFavoritos(this);
    } else {
        listaFavoritos = nullptr;
    }
}

bool Usuario::seguirUsuario(Usuario* otroUsuario) {
    if (!this->esPremium()) {
        cout << nickname << " no es premium - no puedes seguir a otro usuario" << endl;
        return false;
    }

    if (!otroUsuario->esPremium()) {
        cout << otroUsuario->nickname << " no es premium - no se puede seguir" << endl;
        return false;
    }

    if (this == otroUsuario) {
        cout << " No puedes seguirte a ti mismo" << endl;
        return false;
    }

    if (usuarioSeguido != nullptr) {
        cout << "Ya estas siguiendo a " << usuarioSeguido->getNickname() << endl;
        cout << "Debes dejar de seguirlo primero" << endl;
        return false;
    }

    usuarioSeguido = otroUsuario;
    cout << nickname << " ahora sigue a " << otroUsuario->getNickname() << endl;
    return true;
}

bool Usuario::dejarDeSeguir() {
    if (usuarioSeguido == nullptr) {
        cout << nickname << " no está siguiendo a nadie" << endl;
        return false;
    }

    cout << nickname << " dejó de seguir a " << usuarioSeguido->getNickname() << endl;
    usuarioSeguido = nullptr;
    return true;
}

Cancion** Usuario::generarListaReproduccion(int& totalCanciones) {

    totalCanciones = this->getCantidadFavoritos();

    if (usuarioSeguido != nullptr) {
        totalCanciones += usuarioSeguido->getCantidadFavoritos();
    }

    if (totalCanciones == 0) {
        cout << "No hay canciones para reproducir" << endl;
        return nullptr;
    }

    Cancion** listaTemporal = new Cancion*[totalCanciones];
    int indice = 0;

    for (int i = 0; i < this->getCantidadFavoritos(); i++) {
        listaTemporal[indice] = this->listaFavoritos->buscarCancion(i);
        indice++;
    }

    if (usuarioSeguido != nullptr) {
        for (int i = 0; i < usuarioSeguido->getCantidadFavoritos(); i++) {
            listaTemporal[indice] = usuarioSeguido->listaFavoritos->buscarCancion(i);
            indice++;
        }
    }

    return listaTemporal;
}

void Usuario::setListaFavoritos(Usuario* usuario, ListaCanciones* canciones){

    ListaFavoritos* listaUsuario = new ListaFavoritos(usuario);

    ifstream archivo("data/listas_favoritos.txt");
    string linea;

    while (getline(archivo, linea)) {
        size_t pos1 = linea.find(';');
        string propietario = linea.substr(0, pos1);

        if (propietario == nickname) {
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

    listaFavoritos - listaUsuario;

}

void Usuario::liberarListaReproduccion(Cancion** lista) {
    if (lista != nullptr) {
        delete[] lista;
    }
}

Usuario::~Usuario() {
    delete listaFavoritos;

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
