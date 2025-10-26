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

void Usuario::generarListaReproduccion(Usuario* usuario) {

    int totalCanciones = this->getCantidadFavoritos();

    if (usuarioSeguido != nullptr) {
        totalCanciones += usuarioSeguido->getCantidadFavoritos();
    }

    ListaFavoritos* listaTemporal = new ListaFavoritos(usuario);
    listaTemporal->setCapacidad(totalCanciones);
    int indice = 0;

    for (int i = 0; i < this->getCantidadFavoritos(); i++) {
        listaTemporal->agregarCancion(listaFavoritos->buscarCancion(i));
        indice++;
    }

    if (usuarioSeguido != nullptr) {
        for (int i = 0; i < usuarioSeguido->getCantidadFavoritos(); i++) {
            listaTemporal->agregarCancion(usuarioSeguido->listaFavoritos->buscarCancion(i));
            indice++;
        }
    }

    listaFavoritos=listaTemporal;
}

void Usuario::setListaFavoritos(Usuario* usuario, ListaCanciones* canciones){

    ListaFavoritos* listaUsuario = new ListaFavoritos(usuario);

    ifstream archivo("data/listas_favoritos.txt");
    string linea;

    while (getline(archivo, linea)) {
        size_t pos1 = linea.find(';');
        string propietario = linea.substr(0, pos1);

        if (propietario == this->nickname) {
            size_t pos2 = linea.find(';', pos1 + 1);
            string strCantidad = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            int cantidadCanciones = stoi(strCantidad);

            listaUsuario->setCapacidad(cantidadCanciones);

            size_t inicio = pos2 + 1;
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


    listaFavoritos = listaUsuario;

}

void Usuario::liberarListaReproduccion(Cancion** lista) {
    if (lista != nullptr) {
        delete[] lista;
    }
}

Usuario::~Usuario() {

    string linea;

    ifstream inUsuarios("data/usuarios.txt");
    ofstream tempUsuarios("data/usuarios_temp.txt");

    while (getline(inUsuarios, linea)) {
        size_t pos1 = 0, pos2 = 0;
        string campos[6];
        int i = 0;

        while (i < 5 && (pos2 = linea.find(';', pos1)) != string::npos) {
            campos[i] = linea.substr(pos1, pos2 - pos1);
            pos1 = pos2 + 1;
            i++;
        }
        campos[i] = linea.substr(pos1);

        if (campos[0] == nickname) {
            campos[5] = nicknameUsuarioSeguido;
        }

        tempUsuarios << campos[0] << ";" << campos[1] << ";" << campos[2] << ";"
                     << campos[3] << ";" << campos[4] << ";" << campos[5] << "\n";
    }

    inUsuarios.close();
    tempUsuarios.close();

    remove("data/usuarios.txt");
    rename("data/usuarios_temp.txt", "data/usuarios.txt");


    ifstream inListas("data/listas_favoritos.txt");
    ofstream tempListas("data/listas_favoritos_temp.txt");

    bool listaEncontrada = false;
    while (getline(inListas, linea)) {
        size_t pos = linea.find(';');
        string nickLista = linea.substr(0, pos);

        if (nickLista == nickname) {
            tempListas << nickname << ";";

            int total = listaFavoritos->getCantidadCanciones();
            for (int i = 0; i < total; i++) {
                tempListas << listaFavoritos->getCancion(i)->getId();
                if (i < total - 1)
                    tempListas << ";";
            }
            tempListas << "\n";

            listaEncontrada = true;
        } else {
            tempListas << linea << "\n";
        }
    }

    if (!listaEncontrada) {
        tempListas << nickname << ";";

        int total = listaFavoritos->getCantidadCanciones();
        for (int i = 0; i < total; i++) {
            tempListas << listaFavoritos->getCancion(i)->getId();
            if (i < total - 1)
                tempListas << ";";
        }
        tempListas << "\n";
    }


    inListas.close();
    tempListas.close();

    remove("data/listas_favoritos.txt");
    rename("data/listas_favoritos_temp.txt", "data/listas_favoritos.txt");

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
