#ifndef METRICAS_H
#define METRICAS_H

#include <iostream>
#include <string>

class Metricas {
private:

    static int iteraciones;
    static size_t memoriaTotal;
    static std::string ultimaFuncionalidad;
    static size_t memoriaInicial;
    static const int MAX_FUNCIONALIDADES = 30;
    static std::string nombresFuncionalidades[MAX_FUNCIONALIDADES];
    static int iteracionesFuncionalidades[MAX_FUNCIONALIDADES];
    static size_t memoriaFuncionalidades[MAX_FUNCIONALIDADES];
    static int totalFuncionalidades;


public:

    static void agregarIteraciones(int cantidad);
    static void resetearIteraciones();
    static void agregarMemoria(size_t bytes);
    static void removerMemoria(size_t bytes);
    static void mostrarMetricas(const std::string& nombreFuncionalidad);
    static int getIteraciones();
    static size_t getMemoriaTotal();
    static void iniciarMedicion(const std::string& funcionalidad);
    static void finalizarMedicion();
    static size_t calcularMemoriaString(const std::string& str);
    static void mostrarResumenCompleto();

};

#endif
