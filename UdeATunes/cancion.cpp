#include <iostream>
#include "cancion.h"
#include "album.h"
#include <fstream>

using namespace std;

void Cancion::reproducir(int calidad){

    ifstream archivo("data/albumes.txt");
    string linea;

    Album* album = nullptr;

    while (getline(archivo, linea)) {
        size_t pos1 = linea.find(';');
        string id = linea.substr(0, pos1);
        int intId = stoi(id);

        if (intId == idAlbum) {
            size_t pos2 = linea.find(';', pos1 + 1);
            size_t pos3 = linea.find(';', pos2 + 1);
            size_t pos4 = linea.find(';', pos3 + 1);
            size_t pos5 = linea.find(';', pos4 + 1);
            size_t pos6 = linea.find(';', pos5 + 1);
            size_t pos7 = linea.find(';', pos6 + 1);

            string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string strIdArtista = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            int idArtista = stoi(strIdArtista);
            string anio = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            string discografica = linea.substr(pos4 + 1, pos5 - pos4 - 1);
            string strDuracion = linea.substr(pos5 + 1, pos6 - pos5 - 1);
            float duracion = stof(strDuracion);
            string portada = linea.substr(pos6 + 1, pos7 - pos6 - 1);
            string strPuntuacion = linea.substr(pos7 + 1);
            float puntuacion = stof(strPuntuacion);

            album = new Album(nombre,intId,anio,discografica,portada,puntuacion,duracion, idArtista);
            break;

        }
    }
    archivo.close();


    cout<<"\nArtista: "<<album->getArtista()->getNombre()<<endl;
    cout<<"Album: "<<album->getNombre()<<endl;
    cout<<"Ruta a la portada del album: "<<album->getRutaPortada()<<endl;
    cout<<"\n";
    cout<<"Titulo de la cancion: "<<this->nombre<<endl;

    if (calidad==1){
        cout<<"Ruta del archivo de audio (128kbps): "<<this->ruta128<<endl;
    }
    else{
        cout<<"Ruta del archivo de audio (320kbps): "<<this->ruta320<<endl;

    }
    (this->reproducciones)++;

    delete album;

}
