#ifndef METRICS_H
#define METRICS_H

#include "process.h"
#include <vector>

struct ResultadosSistema {
    float promedioRetorno;
    float promedioEspera;
    float promedioRespuesta;
    float utilizacionCPU;
};

class Metrics {
public:
    static ResultadosSistema calcular(const std::vector<Proceso>& procesos, int tiempoTotal);
    static void mostrar(const std::vector<Proceso>& procesos, const ResultadosSistema& resultados);
    static void mostrarGantt(const std::vector<Proceso>& procesos);  // ✅ nueva función
};

#endif
