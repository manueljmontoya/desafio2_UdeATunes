#include <iostream>
#include <string>
#ifndef ALBUM_H
#define ALBUM_H
#include "Artista.h"

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
    int idArtista;
    Artista* artista=nullptr;

    string generos[4];

public:

    Album(string n,int cod, string fec,string disq, string port, float punt,float dur, int art);
    ~Album();
    Artista* getArtista(){return artista;}
    string getRutaPortada(){return rutaPortada;}
    string getNombre(){return nombre;}

};

#endif // ALBUM_H
