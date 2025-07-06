#include "sjf.h"
#include <algorithm>

using namespace std;

namespace sjf {

    void ejecutar(vector<Proceso>& procesos, int& tiempoTotal) {
        int n = procesos.size();
        int tiempoActual = 0;
        vector<Proceso*> listaEspera;

        vector<bool> terminado(n, false);
        int procesosCompletados = 0;

        while (procesosCompletados < n) {
            // Cargar procesos que han llegado y no están terminados
            for (int i = 0; i < n; ++i) {
                if (!terminado[i] && procesos[i].llegada <= tiempoActual) {
                    listaEspera.push_back(&procesos[i]);
                }
            }

            if (!listaEspera.empty()) {
                // Elegir el de menor ráfaga
                auto siguiente = *min_element(listaEspera.begin(), listaEspera.end(),
                    [](Proceso* a, Proceso* b) {
                        return a->rafaga < b->rafaga;
                    });

                // Ejecutar el proceso
                siguiente->estado = EJECUTANDO;
                siguiente->inicio_ejecucion = tiempoActual;
                siguiente->tiempo_respuesta = tiempoActual - siguiente->llegada;
                siguiente->tiempo_espera = tiempoActual - siguiente->llegada;

                tiempoActual += siguiente->rafaga;
                siguiente->finalizacion = tiempoActual;
                siguiente->tiempo_retorno = siguiente->finalizacion - siguiente->llegada;
                siguiente->estado = TERMINADO;

                // Marcar como terminado
                for (int i = 0; i < n; ++i) {
                    if (&procesos[i] == siguiente) {
                        terminado[i] = true;
                        break;
                    }
                }

                procesosCompletados++;
                listaEspera.clear();
            } else {
                tiempoActual++; // CPU ociosa
            }
        }

        tiempoTotal = tiempoActual;
    }
}
