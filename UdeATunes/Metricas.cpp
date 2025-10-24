#include "Metricas.h"

int Metricas::iteraciones = 0;
size_t Metricas::memoriaTotal = 0;

void Metricas::agregarIteraciones(int cantidad) {
    iteraciones += cantidad;
}

void Metricas::resetearIteraciones() {
    iteraciones = 0;
}

void Metricas::agregarMemoria(size_t bytes) {
    memoriaTotal += bytes;
}

void Metricas::removerMemoria(size_t bytes) {
    if (bytes <= memoriaTotal) {
        memoriaTotal -= bytes;
    } else {
        memoriaTotal = 0;
    }
}

void Metricas::mostrarMetricas() {
    std::cout << "\n=== MÉTRICAS DE EFICIENCIA ===" << std::endl;
    std::cout << "Total de iteraciones: " << iteraciones << std::endl;
    std::cout << "Memoria consumida: " << memoriaTotal << " bytes ("
              << (memoriaTotal / 1024.0) << " KB)" << std::endl;
    std::cout << "==============================\n" << std::endl;

}

int Metricas::getIteraciones() {
    return iteraciones;
}

size_t Metricas::getMemoriaTotal() {
    return memoriaTotal;
}
