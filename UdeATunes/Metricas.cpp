#include "Metricas.h"

int Metricas::iteraciones = 0;
size_t Metricas::memoriaTotal = 0;
std::string Metricas::ultimaFuncionalidad = "";

std::string Metricas::nombresFuncionalidades[Metricas::MAX_FUNCIONALIDADES];
int Metricas::iteracionesFuncionalidades[Metricas::MAX_FUNCIONALIDADES];
int Metricas::totalFuncionalidades = 0;
size_t Metricas::memoriaFuncionalidades[Metricas::MAX_FUNCIONALIDADES];
size_t Metricas::memoriaInicial = 0;


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

void Metricas::mostrarMetricas(const std::string& nombreFuncionalidad) {
    std::cout << "\n=== METRICAS DE EFICIENCIA ===" << std::endl;
    if (!nombreFuncionalidad.empty()) {
        std::cout << "Funcionalidad: " << nombreFuncionalidad << std::endl;
    }
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

void Metricas::iniciarMedicion(const std::string& funcionalidad) {
    ultimaFuncionalidad = funcionalidad;
    resetearIteraciones();
    memoriaInicial = memoriaTotal;
}

void Metricas::finalizarMedicion() {
    if (ultimaFuncionalidad.empty()) {
        return;
    }
    size_t memoriaConsumida = memoriaTotal - memoriaInicial;

    bool encontrada = false;
    for (int i = 0; i < totalFuncionalidades; i++) {
        if (nombresFuncionalidades[i] == ultimaFuncionalidad) {
            iteracionesFuncionalidades[i] += iteraciones;
            memoriaFuncionalidades[i] += memoriaConsumida;
            encontrada = true;
            break;
        }
    }

    if (!encontrada && totalFuncionalidades < MAX_FUNCIONALIDADES) {
        nombresFuncionalidades[totalFuncionalidades] = ultimaFuncionalidad;
        iteracionesFuncionalidades[totalFuncionalidades] = iteraciones;
        memoriaFuncionalidades[totalFuncionalidades] = memoriaConsumida;
        totalFuncionalidades++;
    }

    resetearIteraciones();
    ultimaFuncionalidad = "";
}

size_t Metricas::calcularMemoriaString(const std::string& str) {
    return sizeof(std::string) + str.capacity();
}

void Metricas::mostrarResumenCompleto() {
    std::cout << "\n\n=== RESUMEN COMPLETO DE MÉTRICAS ===" << std::endl;

    for (int i = 0; i < totalFuncionalidades; i++) {
        std::cout << "--- " << nombresFuncionalidades[i] << " ---" << std::endl;
        std::cout << "Iteraciones: " << iteracionesFuncionalidades[i] << std::endl;
        std::cout << "Memoria: " << memoriaFuncionalidades[i] << " bytes ("
                  << (memoriaFuncionalidades[i] / 1024.0) << " KB)" << std::endl;
    }

    std::cout << "--- MEMORIA TOTAL ---" << std::endl;
    std::cout << "Memoria consumida: " << memoriaTotal << " bytes ("
              << (memoriaTotal / 1024.0) << " KB)" << std::endl;
    std::cout << "==================================" << std::endl;
}
