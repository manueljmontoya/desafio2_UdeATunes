#include "SistemaAnuncios.h"
#include "Metricas.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

SistemaAnuncios::SistemaAnuncios() {

    anunciosAAA = nullptr;
    anunciosB = nullptr;
    anunciosC = nullptr;
    tamañoAAA = 0;
    tamañoB = 0;
    tamañoC = 0;
    cantidadAAA = 0;
    cantidadB = 0;
    cantidadC = 0;
    ultimoAnuncioMostrado = nullptr;
    srand(time(0));
    size_t memoria = sizeof(*this);
    Metricas::agregarMemoria(memoria);
}

SistemaAnuncios::~SistemaAnuncios() {

    size_t memoriaArrays = sizeof(Anuncio*) * (tamañoAAA + tamañoB + tamañoC);
    size_t memoriaObjeto = sizeof(*this);

    for (int i = 0; i < cantidadAAA; i++) {
        delete anunciosAAA[i];
    }
    delete[] anunciosAAA;

    for (int i = 0; i < cantidadB; i++) {
        delete anunciosB[i];
    }
    delete[] anunciosB;

    for (int i = 0; i < cantidadC; i++) {
        delete anunciosC[i];
    }
    delete[] anunciosC;

    Metricas::removerMemoria(memoriaArrays + memoriaObjeto);
}


bool SistemaAnuncios::cargarAnunciosDesdeArchivos() {
    Metricas::iniciarMedicion("Cargar Anuncios Desde Archivos");

    bool exito = true;
    Metricas::agregarIteraciones(1);

    if (!cargarAnunciosAAA("data/anunciosAAA.txt")){
        Metricas::agregarIteraciones(2);
        exito = false;
    }
    else Metricas::agregarIteraciones(1);

    if (!cargarAnunciosB("data/anunciosB.txt")) {
        Metricas::agregarIteraciones(2);
        exito = false;
    }
    else Metricas::agregarIteraciones(1);

    if (!cargarAnunciosC("data/anunciosC.txt")) {
        Metricas::agregarIteraciones(2);
        exito = false;
    }
    else Metricas::agregarIteraciones(1);

    Metricas::finalizarMedicion();
    return exito;
}


bool SistemaAnuncios::cargarAnunciosAAA(string archivo) {
    Metricas::iniciarMedicion("Cargar Anuncios AAA");

    ifstream file(archivo);
    Metricas::agregarIteraciones(1);

    if (!file.is_open()) {
        Metricas::agregarIteraciones(2);
        Metricas::finalizarMedicion();
        return false;
    }
    Metricas::agregarIteraciones(1);

    int cantidadArchivo;
    file >> cantidadArchivo;
    Metricas::agregarIteraciones(1);

    tamañoAAA = cantidadArchivo;
    anunciosAAA = new Anuncio*[tamañoAAA];
    Metricas::agregarIteraciones(2);

    size_t memoriaArray = sizeof(Anuncio*) * tamañoAAA;
    Metricas::agregarMemoria(memoriaArray);

    string linea;
    getline(file, linea);

    cantidadAAA = 0;
    Metricas::agregarIteraciones(1);

    while (getline(file, linea) && cantidadAAA < tamañoAAA) {
        Metricas::agregarIteraciones(2);

        if (!linea.empty()) {
            Metricas::agregarIteraciones(1);
            anunciosAAA[cantidadAAA] = new Anuncio(linea, 'A');
            cantidadAAA++;
            Metricas::agregarIteraciones(2);
        }
        else {
            Metricas::agregarIteraciones(1);
        }
    }

    file.close();
    Metricas::agregarIteraciones(1);

    Metricas::finalizarMedicion();
    return true;
}

bool SistemaAnuncios::cargarAnunciosB(string archivo) {
    Metricas::iniciarMedicion("Cargar Anuncios B");

    ifstream file(archivo);
    Metricas::agregarIteraciones(1);

    if (!file.is_open()) {

        Metricas::agregarIteraciones(2);
        Metricas::finalizarMedicion();
        return false;
    }
    Metricas::agregarIteraciones(1);

    int cantidadArchivo;
    file >> cantidadArchivo;
    Metricas::agregarIteraciones(1);

    tamañoB = cantidadArchivo;
    anunciosB = new Anuncio*[tamañoB];
    Metricas::agregarIteraciones(2);

    size_t memoriaArray = sizeof(Anuncio*) * tamañoB;
    Metricas::agregarMemoria(memoriaArray);
    Metricas::agregarIteraciones(1);

    string linea;
    getline(file, linea);
    Metricas::agregarIteraciones(2);


    cantidadB = 0;
    Metricas::agregarIteraciones(1);
    while (getline(file, linea) && cantidadB < tamañoB) {
        Metricas::agregarIteraciones(2);

        if (!linea.empty()) {
            Metricas::agregarIteraciones(1);
            anunciosB[cantidadB] = new Anuncio(linea, 'B');
            cantidadB++;
            Metricas::agregarIteraciones(2);
        }
        else {
            Metricas::agregarIteraciones(1);
        }
    }

    file.close();
    Metricas::agregarIteraciones(1);
    Metricas::finalizarMedicion();
    return true;
}

bool SistemaAnuncios::cargarAnunciosC(string archivo) {
    Metricas::iniciarMedicion("Cargar Anuncios C");
    ifstream file(archivo);
    Metricas::agregarIteraciones(1);

    if (!file.is_open()) {
        Metricas::agregarIteraciones(2);
        Metricas::finalizarMedicion();
        return false;
    }

    int cantidadArchivo;
    file >> cantidadArchivo;
    Metricas::agregarIteraciones(1);

    tamañoC = cantidadArchivo;
    anunciosC = new Anuncio*[tamañoC];
    Metricas::agregarIteraciones(2);

    size_t memoriaArray = sizeof(Anuncio*) * tamañoC;
    Metricas::agregarMemoria(memoriaArray);

    string linea;
    getline(file, linea);
    Metricas::agregarIteraciones(2);

    cantidadC = 0;
    Metricas::agregarIteraciones(1);

    while (getline(file, linea) && cantidadC < tamañoC) {
        Metricas::agregarIteraciones(2);

        if (!linea.empty()) {
            Metricas::agregarIteraciones(1);

            anunciosC[cantidadC] = new Anuncio(linea, 'C');
            cantidadC++;
            Metricas::agregarIteraciones(2);
        }
    }

    file.close();
    Metricas::agregarIteraciones(1);
    Metricas::finalizarMedicion();
    return true;
}

Anuncio* SistemaAnuncios::seleccionarAnuncioAleatorio() {
    Metricas::iniciarMedicion("Seleccionar Anuncio Aleatorio");
    if (getTotalAnuncios() == 0) {

        Metricas::agregarIteraciones(2);
        Metricas::finalizarMedicion();

        return nullptr;
    }

    Metricas::agregarIteraciones(1);

    Anuncio* seleccionado = nullptr;
    int intentos = 0;
    const int MAX_INTENTOS = 10;
    Metricas::agregarIteraciones(3);

    do {
        Metricas::agregarIteraciones(1);

        int categoria = rand() % 6 + 1;
        Metricas::agregarIteraciones(1);

        if (categoria <= 3 && cantidadAAA > 0) {
            Metricas::agregarIteraciones(2);
            seleccionado = seleccionarAnuncioAAA();
            Metricas::agregarIteraciones(1);

        } else if (categoria <= 5 && cantidadB > 0) {
            Metricas::agregarIteraciones(3);
            seleccionado = seleccionarAnuncioB();
            Metricas::agregarIteraciones(1);

        } else if (cantidadC > 0) {
            Metricas::agregarIteraciones(2);
            seleccionado = seleccionarAnuncioC();
            Metricas::agregarIteraciones(1);
        }
        Metricas::agregarIteraciones(1);

        intentos++;
        Metricas::agregarIteraciones(1);

        if (intentos >= MAX_INTENTOS && seleccionado == ultimoAnuncioMostrado) {
            Metricas::agregarIteraciones(2);

            if (cantidadAAA > 0 && seleccionarAnuncioAAA() != ultimoAnuncioMostrado) {
                Metricas::agregarIteraciones(3);
                seleccionado = seleccionarAnuncioAAA();
                Metricas::agregarIteraciones(1);

            } else if (cantidadB > 0 && seleccionarAnuncioB() != ultimoAnuncioMostrado) {
                Metricas::agregarIteraciones(3);
                seleccionado = seleccionarAnuncioB();
                Metricas::agregarIteraciones(1);
            } else if (cantidadC > 0 && seleccionarAnuncioC() != ultimoAnuncioMostrado) {
                Metricas::agregarIteraciones(3);
                seleccionado = seleccionarAnuncioC();
                Metricas::agregarIteraciones(1);
            }
            Metricas::agregarIteraciones(1);
            break;
        }
        Metricas::agregarIteraciones(1);

    } while (seleccionado == ultimoAnuncioMostrado && intentos < MAX_INTENTOS);
    Metricas::agregarIteraciones(2);

    ultimoAnuncioMostrado = seleccionado;
    Metricas::agregarIteraciones(1);

    Metricas::finalizarMedicion();
    return seleccionado;
}

Anuncio* SistemaAnuncios::seleccionarAnuncioAAA() {
    Metricas::iniciarMedicion("Seleccionar Anuncio AAA");

    if (cantidadAAA == 0) {
        Metricas::agregarIteraciones(2);
        Metricas::finalizarMedicion();
        return nullptr;
    }
    Metricas::agregarIteraciones(1);

    int posicion = rand() % cantidadAAA;
    Metricas::agregarIteraciones(2);

    Metricas::finalizarMedicion();
    return anunciosAAA[posicion];
}

Anuncio* SistemaAnuncios::seleccionarAnuncioB() {
    Metricas::iniciarMedicion("Seleccionar Anuncio B");

    if (cantidadB == 0) {
        Metricas::agregarIteraciones(2);
        Metricas::finalizarMedicion();
        return nullptr;
    }
    Metricas::agregarIteraciones(1);

    int posicion = rand() % cantidadB;
    Metricas::agregarIteraciones(2);

    Metricas::finalizarMedicion();
    return anunciosB[posicion];
}

Anuncio* SistemaAnuncios::seleccionarAnuncioC() {
    Metricas::iniciarMedicion("Seleccionar Anuncio C");

    if (cantidadC == 0) {
        Metricas::agregarIteraciones(2);
        Metricas::finalizarMedicion();
        return nullptr;
    }
    Metricas::agregarIteraciones(1);

    int posicion = rand() % cantidadC;
    Metricas::agregarIteraciones(2);

    Metricas::finalizarMedicion();
    return anunciosC[posicion];
}

void SistemaAnuncios::mostrarAnuncioAleatorio() {
    Metricas::iniciarMedicion("Mostrar Anuncio Aleatorio");
    Metricas::agregarIteraciones(1);

    Anuncio* anuncio = seleccionarAnuncioAleatorio();

    if (anuncio == nullptr) {
        Metricas::agregarIteraciones(2);
        cout << "No hay anuncios disponibles" << endl;
        Metricas::finalizarMedicion();
        return;
    }
    Metricas::agregarIteraciones(1);

    cout << "\n=== PUBLICIDAD ===" << endl;
    cout << anuncio->getContenido() << endl;
    cout << "==================" << endl;
    Metricas::agregarIteraciones(3);

    Metricas::finalizarMedicion();
}

int SistemaAnuncios::getTotalAnuncios() const {
    return cantidadAAA + cantidadB + cantidadC;
}
