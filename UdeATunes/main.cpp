#include "sistema.h"
#include "Metricas.h"
using namespace std;

int main() {
    Sistema sistema;
    sistema.ejecutar();
    Metricas::mostrarResumenCompleto();
    return 0;
}
