#ifndef METRICAS_H
#define METRICAS_H

#include <iostream>

class Metricas {
private:
    static int iteraciones;
    static size_t memoriaTotal;

public:

    static void agregarIteraciones(int cantidad);
    static void resetearIteraciones();

    static void agregarMemoria(size_t bytes);
    static void removerMemoria(size_t bytes);

    static void mostrarMetricas();

    static int getIteraciones();
    static size_t getMemoriaTotal();
};

#endif
