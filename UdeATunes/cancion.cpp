#include <iostream>
#include "cancion.h"

using namespace std;

void Cancion::reproducir(int calidad){

    cout<<"Artista: "<<this->album.artista.nombre<<endl;
    cout<<"Album: "<<this->album.nombre<<endl;
    cout<<"Ruta a la portada del album: "<<this->album.rutaPortada<<endl;
    cout<<"\0";
    cout<<"Titulo de la cancion: "<<this->nombre<<endl;

    if (calidad==1){
        cout<<"Ruta del archivo de audio (128kbps): "<<this->ruta128<<endl;
    }
    else{
        cout<<"Ruta del archivo de audio (320kbps): "<<this->ruta320<<endl;

    }
    (this->reproducciones)++;

}
