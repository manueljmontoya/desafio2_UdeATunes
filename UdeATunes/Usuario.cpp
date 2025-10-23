#include "Usuario.h"
#include "listaFavoritos.h"
#include "cancion.h"

Usuario::Usuario() {
    nickname = "invitado";
    tipoMembresia = "estandar";
    ciudad = "Desconocida";
    pais = "Desconocido";
    fechaInscripcion = "01/01/2025";
    listaFavoritos = nullptr;
    usuarioSiguiendo = "";
}

Usuario::Usuario(string nick, string tipo, string ciu, string pa, string fecha, string siguiendo) {
    nickname = nick;

    if (tipo != "estandar" && tipo != "premium") {
        tipoMembresia = "estandar";
    } else {
        tipoMembresia = tipo;
    }

    ciudad = ciu;
    pais = pa;
    fechaInscripcion = fecha;
    usuarioSiguiendo = siguiendo;

    if (esPremium()) {
        listaFavoritos = new ListaFavoritos(this);
    } else {
        listaFavoritos = nullptr;
    }
}

Usuario::~Usuario() {
    if (listaFavoritos != nullptr) {
        delete listaFavoritos;
    }
}

void Usuario::setListaFavoritos(ListaFavoritos* lista){

    listaFavoritos=lista;

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

bool Usuario::seguirUsuarioPremium(Usuario* usuario) {
    if (!esPremium()) {
        return false;
    }
    if (listaFavoritos == nullptr) {
        return false;
    }
    if (usuario == nullptr) {
        return false;
    }
    if (!usuario->esPremium()) {
        return false;
    }

    listaFavoritos->fusionarListas(*usuario->getListaFavoritos());
    return true;
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
    // Mostrar información básica
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
