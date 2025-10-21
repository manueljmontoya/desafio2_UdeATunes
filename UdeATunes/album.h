#include <iostream>
#include <string>
#ifndef ALBUM_H
#define ALBUM_H
#include "listacanciones.h"

using namespace std;

class Album{

private:

    int codigo;
    string nombre;
    string fecha;
    string disquera;
    string rutaPortada;
    float puntuacion;
    float duracion;
    string artista;

    string generos[4];

    ListaCanciones canciones;

public:

    Album(string n,int cod, string fec,string disq, string port, float punt,
          float dur, string art):nombre(n),codigo(cod),fecha(fec),disquera(disq),
        rutaPortada(port),puntuacion(punt),duracion(dur),artista(art){}

};

#endif // ALBUM_H
