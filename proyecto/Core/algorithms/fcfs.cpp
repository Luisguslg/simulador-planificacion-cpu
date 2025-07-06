#include "fcfs.h"
#include <algorithm>
#include <iostream>

using namespace std;

namespace fcfs {

    void ejecutar(std::vector<Proceso>& procesos, int& tiempoTotal) {
        // Ordenamos los procesos por tiempo de llegada
        sort(procesos.begin(), procesos.end(), [](const Proceso& a, const Proceso& b) {
            return a.llegada < b.llegada;
        });

        int tiempoActual = 0;

        for (auto& proceso : procesos) {
            proceso.estado = LISTO;

            // Si el proceso llega después del tiempo actual, esperamos
            if (proceso.llegada > tiempoActual)
                tiempoActual = proceso.llegada;

            proceso.inicio_ejecucion = tiempoActual;
            proceso.estado = EJECUTANDO;

            proceso.tiempo_respuesta = proceso.inicio_ejecucion - proceso.llegada;
            proceso.tiempo_espera = proceso.inicio_ejecucion - proceso.llegada;
            
            tiempoActual += proceso.rafaga;
            proceso.finalizacion = tiempoActual;
            proceso.tiempo_retorno = proceso.finalizacion - proceso.llegada;

            proceso.estado = TERMINADO;
        }

        tiempoTotal = tiempoActual;
    }

}
