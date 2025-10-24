#include "album.h"
#include <iostream>
#include "Artista.h"
#include <fstream>

using namespace std;

Album::Album(string n,int cod, string fec,string disq, string port, float punt,float dur, int art){

    nombre=n;
    codigo=cod;
    fecha=fec;
    disquera=disq;
    rutaPortada=port;
    puntuacion=punt;
    duracion=dur;
    idArtista=art;

    ifstream archivo("data/artistas.txt");
    string linea;

    while (getline(archivo, linea)) {
        size_t pos1 = linea.find(';');
        string id = linea.substr(0, pos1);
        int intId = stoi(id);

        if (intId == idArtista) {
            size_t pos2 = linea.find(';', pos1 + 1);
            size_t pos3 = linea.find(';', pos2 + 1);
            size_t pos4 = linea.find(';', pos3 + 1);
            size_t pos5 = linea.find(';', pos4 + 1);
            size_t pos6 = linea.find(';', pos5 + 1);

            string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string strEdad = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            int edad = stoi(strEdad);
            string pais = linea.substr(pos4 + 1, pos5 - pos4 - 1);
            string strSeguidores = linea.substr(pos5 + 1, pos6 - pos5 - 1);
            int seguidores = stoi(strSeguidores);
            string strPosicion = linea.substr(pos6 + 1);
            int posicion = stoi(strPosicion);

            artista = new Artista(nombre,intId,edad,pais,seguidores,posicion);
            break;

        }
    }
    archivo.close();

}
