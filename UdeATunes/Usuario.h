#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>
using namespace std;

class ListaFavoritos;
class Cancion;
class ListaCanciones;

class Usuario {
private:
    string nickname;
    string tipoMembresia;
    string ciudad;
    string pais;
    string fechaInscripcion;
    ListaFavoritos* listaFavoritos;
    string nicknameUsuarioSeguido;
    Usuario* usuarioSeguido;

public:
    Usuario();
    Usuario(string nick, string tipo, string ciu, string pa, string fecha, string seguido);
    ~Usuario();

    string getNickname() const { return nickname; }
    string getTipoMembresia() const { return tipoMembresia; }
    string getCiudad() const { return ciudad; }
    string getPais() const { return pais; }
    string getFechaInscripcion() const { return fechaInscripcion; }
    ListaFavoritos* getListaFavoritos() { return listaFavoritos; }

    void setUsuarioSeguido(Usuario* user){usuarioSeguido=user;}
    void setTipoMembresia(string tipo);
    bool esPremium() const;
    bool agregarAFavoritos(Cancion* cancion);
    bool eliminarDeFavoritos(int idCancion);
    int getCantidadFavoritos() const;
    string getNicknameSeguido(){return nicknameUsuarioSeguido;}
    bool seguirUsuario(Usuario* otroUsuario);
    bool dejarDeSeguir();
    bool estaSiguiendoAlguien() const { return usuarioSeguido != nullptr; }
    Usuario* getUsuarioSeguido() const { return usuarioSeguido; }
    void setListaFavoritos(Usuario* usuario, ListaCanciones* canciones);

    Cancion** generarListaReproduccion(int& totalCanciones);
    void liberarListaReproduccion(Cancion** lista);

    bool operator==(const Usuario& otro) const;
    friend ostream& operator<<(ostream& os, const Usuario& usuario);

};

#endif
