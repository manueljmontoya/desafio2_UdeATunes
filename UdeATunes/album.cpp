#include "album.h"
#include <iostream>
#include "Artista.h"
#include "Metricas.h"
#include <fstream>

using namespace std;

Album::Album(string n,int cod, string fec,string disq, string port, float punt,float dur, int art){
    Metricas::iniciarMedicion("Constructor Album");

    nombre=n;
    codigo=cod;
    fecha=fec;
    disquera=disq;
    rutaPortada=port;
    puntuacion=punt;
    duracion=dur;
    idArtista=art;
    Metricas::agregarIteraciones(8);

    ifstream archivo("data/artistas.txt");
    string linea;
    Metricas::agregarIteraciones(2);

    while (getline(archivo, linea)) {
        Metricas::agregarIteraciones(2);

        size_t pos1 = linea.find(';');
        string id = linea.substr(0, pos1);
        int intId = stoi(id);
        Metricas::agregarIteraciones(3);

        Metricas::agregarIteraciones(1);
        if (intId == idArtista) {
            size_t pos2 = linea.find(';', pos1 + 1);
            size_t pos3 = linea.find(';', pos2 + 1);
            size_t pos4 = linea.find(';', pos3 + 1);
            size_t pos5 = linea.find(';', pos4 + 1);
            Metricas::agregarIteraciones(4);

            string nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string strEdad = linea.substr(pos2 + 1, pos3 - pos2 - 1);
            int edad = stoi(strEdad);
            string pais = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            string strSeguidores = linea.substr(pos4 + 1, pos5 - pos4 - 1);
            int seguidores = stoi(strSeguidores);
            string strPosicion = linea.substr(pos5 + 1);
            int posicion = stoi(strPosicion);
            Metricas::agregarIteraciones(8);

            artista = new Artista(nombre,intId,edad,pais,seguidores,posicion);
            Metricas::agregarIteraciones(2);
            break;

        }
    }
    archivo.close();
    Metricas::agregarIteraciones(1);

    size_t memoria = sizeof(*this) +
                    Metricas::calcularMemoriaString(nombre) +
                    Metricas::calcularMemoriaString(fecha) +
                    Metricas::calcularMemoriaString(disquera) +
                    Metricas::calcularMemoriaString(rutaPortada);
    Metricas::agregarMemoria(memoria);

    Metricas::finalizarMedicion();

}

Album::~Album() {

    size_t memoria = sizeof(*this) +
                    Metricas::calcularMemoriaString(nombre) +
                    Metricas::calcularMemoriaString(fecha) +
                    Metricas::calcularMemoriaString(disquera) +
                    Metricas::calcularMemoriaString(rutaPortada);
    Metricas::removerMemoria(memoria);


}
