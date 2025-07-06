#include "priority.h"
#include <algorithm>

using namespace std;

namespace priority {

    void ejecutar(vector<Proceso>& procesos, int& tiempoTotal) {
        int n = procesos.size();
        int completados = 0;
        int tiempoActual = 0;
        vector<bool> terminado(n, false);

        while (completados < n) {
            // Buscar el proceso de mayor prioridad disponible (menor número)
            int mejor = -1;
            for (int i = 0; i < n; ++i) {
                if (!terminado[i] && procesos[i].llegada <= tiempoActual) {
                    if (mejor == -1 ||
                        procesos[i].prioridad < procesos[mejor].prioridad ||
                        (procesos[i].prioridad == procesos[mejor].prioridad &&
                         procesos[i].llegada < procesos[mejor].llegada)) {
                        mejor = i;
                    }
                }
            }

            if (mejor == -1) {
                tiempoActual++; // CPU ociosa
                continue;
            }

            Proceso& p = procesos[mejor];

            p.inicio_ejecucion = tiempoActual;
            p.finalizacion = tiempoActual + p.rafaga;
            p.tiempo_respuesta = p.inicio_ejecucion - p.llegada;
            p.tiempo_retorno = p.finalizacion - p.llegada;
            p.tiempo_espera = p.tiempo_retorno - p.rafaga;
            p.estado = TERMINADO;

            tiempoActual = p.finalizacion;
            terminado[mejor] = true;
            completados++;
        }

        tiempoTotal = tiempoActual;
    }

}
