#include "SistemaAnuncios.h"
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
}

SistemaAnuncios::~SistemaAnuncios() {

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
}


bool SistemaAnuncios::cargarAnunciosDesdeArchivos() {
    bool exito = true;

    if (!cargarAnunciosAAA("anunciosAAA.txt")){
        exito = false;
    }

    if (!cargarAnunciosB("anunciosB.txt")) {
        exito = false;
    }

    if (!cargarAnunciosC("anunciosC.txt")) {
        exito = false;
    }

    return exito;
}


bool SistemaAnuncios::cargarAnunciosAAA(string archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        return false;
    }

    int cantidadArchivo;
    file >> cantidadArchivo;

    tamañoAAA = cantidadArchivo;
    anunciosAAA = new Anuncio*[tamañoAAA];

    string linea;
    getline(file, linea);

    cantidadAAA = 0;
    while (getline(file, linea) && cantidadAAA < tamañoAAA) {
        if (!linea.empty()) {
            anunciosAAA[cantidadAAA] = new Anuncio(linea, 'A');
            cantidadAAA++;
        }
    }

    file.close();
    return true;
}

bool SistemaAnuncios::cargarAnunciosB(string archivo) {
    ifstream file(archivo);
    if (!file.is_open()) return false;

    int cantidadArchivo;
    file >> cantidadArchivo;

    tamañoB = cantidadArchivo;
    anunciosB = new Anuncio*[tamañoB];

    string linea;
    getline(file, linea);

    cantidadB = 0;  // ← cantidadB
    while (getline(file, linea) && cantidadB < tamañoB) {
        if (!linea.empty()) {
            anunciosB[cantidadB] = new Anuncio(linea, 'B');
            cantidadB++;
        }
    }

    file.close();
    return true;
}

bool SistemaAnuncios::cargarAnunciosC(string archivo) {
    ifstream file(archivo);
    if (!file.is_open()) return false;

    int cantidadArchivo;
    file >> cantidadArchivo;

    tamañoC = cantidadArchivo;
    anunciosC = new Anuncio*[tamañoC];

    string linea;
    getline(file, linea);

    cantidadC = 0;
    while (getline(file, linea) && cantidadC < tamañoC) {
        if (!linea.empty()) {
            anunciosC[cantidadC] = new Anuncio(linea, 'C');
            cantidadC++;
        }
    }

    file.close();
    return true;
}


bool SistemaAnuncios::agregarAnuncioAAA(string mensaje) {
    if (getTotalAnuncios() >= 50) {
        return false;
    }

    if (cantidadAAA >= tamañoAAA) {

        int nuevoTamaño = tamañoAAA + 5;
        Anuncio** nuevoArreglo = new Anuncio*[nuevoTamaño];

        for (int i = 0; i < cantidadAAA; i++) {
            nuevoArreglo[i] = anunciosAAA[i];
        }

        delete[] anunciosAAA;
        anunciosAAA = nuevoArreglo;
        tamañoAAA = nuevoTamaño;
    }

    anunciosAAA[cantidadAAA] = new Anuncio(mensaje, 'A');
    cantidadAAA++;

    return true;
}

bool SistemaAnuncios::agregarAnuncioB(string mensaje) {

    if (getTotalAnuncios() >= 50) {
        return false;
    }


    if (cantidadB >= tamañoB) {
        int nuevoTamaño = tamañoB + 5;

        Anuncio** nuevoArreglo = new Anuncio*[nuevoTamaño];

        for (int i = 0; i < cantidadB; i++) {
            nuevoArreglo[i] = anunciosB[i];
        }

        delete[] anunciosB;
        anunciosB = nuevoArreglo;
        tamañoB = nuevoTamaño;
    }

    anunciosB[cantidadB] = new Anuncio(mensaje, 'B');
    cantidadB++;

    return true;
}

bool SistemaAnuncios::agregarAnuncioC(string mensaje) {
    if (getTotalAnuncios() >= 50) {
        return false;
    }

    if (cantidadC >= tamañoC) {
        int nuevoTamaño = tamañoC + 5;

        Anuncio** nuevoArreglo = new Anuncio*[nuevoTamaño];

        for (int i = 0; i < cantidadC; i++) {
            nuevoArreglo[i] = anunciosC[i];
        }

        delete[] anunciosC;
        anunciosC = nuevoArreglo;
        tamañoC = nuevoTamaño;
    }

    anunciosC[cantidadC] = new Anuncio(mensaje, 'C');
    cantidadC++;

    return true;
}

Anuncio* SistemaAnuncios::seleccionarAnuncioAleatorio() {
    if (getTotalAnuncios() == 0) {
        return nullptr;
    }

    Anuncio* seleccionado = nullptr;
    int intentos = 0;
    const int MAX_INTENTOS = 10;

    do {
        int categoria = rand() % 6 + 1;

        if (categoria <= 3 && cantidadAAA > 0) {
            seleccionado = seleccionarAnuncioAAA();
        } else if (categoria <= 5 && cantidadB > 0) {
            seleccionado = seleccionarAnuncioB();
        } else if (cantidadC > 0) {
            seleccionado = seleccionarAnuncioC();
        }

        intentos++;

        if (intentos >= MAX_INTENTOS && seleccionado == ultimoAnuncioMostrado) {

            if (cantidadAAA > 0 && seleccionarAnuncioAAA() != ultimoAnuncioMostrado) {
                seleccionado = seleccionarAnuncioAAA();
            } else if (cantidadB > 0 && seleccionarAnuncioB() != ultimoAnuncioMostrado) {
                seleccionado = seleccionarAnuncioB();
            } else if (cantidadC > 0 && seleccionarAnuncioC() != ultimoAnuncioMostrado) {
                seleccionado = seleccionarAnuncioC();
            }
            break;
        }

    } while (seleccionado == ultimoAnuncioMostrado && intentos < MAX_INTENTOS);

    ultimoAnuncioMostrado = seleccionado;
    return seleccionado;
}

Anuncio* SistemaAnuncios::seleccionarAnuncioAAA() {
    if (cantidadAAA == 0) {
        return nullptr;
    }

    int posicion = rand() % cantidadAAA;

    return anunciosAAA[posicion];
}

Anuncio* SistemaAnuncios::seleccionarAnuncioB() {
    if (cantidadB == 0) {
        return nullptr;
    }

    int posicion = rand() % cantidadB;

    return anunciosB[posicion];
}

Anuncio* SistemaAnuncios::seleccionarAnuncioC() {
    if (cantidadC == 0) {
        return nullptr;
    }

    int posicion = rand() % cantidadC;

    return anunciosC[posicion];
}

void SistemaAnuncios::mostrarAnuncioAleatorio() {
    Anuncio* anuncio = seleccionarAnuncioAleatorio();

    if (anuncio == nullptr) {
        cout << "No hay anuncios disponibles" << endl;
        return;
    }

    cout << "=== PUBLICIDAD ===" << endl;
    cout << "Categoría: " << anuncio->getCategoria() << endl;  // Ya es "AAA", "B" o "C"
    cout << "Mensaje: " << anuncio->getContenido() << endl;
    cout << "==================" << endl;
}

void SistemaAnuncios::mostrarEstadisticas() const {
    cout << "=== ESTADÍSTICAS DE ANUNCIOS ===" << endl;
    cout << "AAA: " << cantidadAAA << " anuncios" << endl;
    cout << "B:   " << cantidadB << " anuncios" << endl;
    cout << "C:   " << cantidadC << " anuncios" << endl;
    cout << "TOTAL: " << getTotalAnuncios() << "/50 anuncios" << endl;

    cout << "Probabilidades: AAA(50%), B(33%), C(17%)" << endl;
}

int SistemaAnuncios::getTotalAnuncios() const {
    return cantidadAAA + cantidadB + cantidadC;
}

bool SistemaAnuncios::puedeAgregarMasAnuncios() const {
    return getTotalAnuncios() < 50;
}
