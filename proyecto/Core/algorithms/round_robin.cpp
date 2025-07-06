#include "round_robin.h"
#include <queue>
#include <algorithm>

using namespace std;

namespace rr {

    void ejecutar(vector<Proceso>& procesos, int quantum, int& tiempoTotal) {
        int n = procesos.size();
        int tiempoActual = 0;
        queue<int> cola;

        vector<int> tiempoRestante(n);
        vector<bool> enCola(n, false);
        int completados = 0;

        for (int i = 0; i < n; ++i) {
            tiempoRestante[i] = procesos[i].rafaga;
        }

        while (completados < n) {
            // Insertar nuevos procesos en la cola si han llegado
            for (int i = 0; i < n; ++i) {
                if (!enCola[i] && procesos[i].llegada <= tiempoActual && tiempoRestante[i] > 0) {
                    cola.push(i);
                    enCola[i] = true;
                }
            }

            if (cola.empty()) {
                tiempoActual++; // CPU ociosa
                continue;
            }

            int i = cola.front(); cola.pop();
            Proceso& p = procesos[i];

            if (p.inicio_ejecucion == -1) {
                p.inicio_ejecucion = tiempoActual;
                p.tiempo_respuesta = tiempoActual - p.llegada;
            }

            p.estado = EJECUTANDO;

            int tiempoEjec = min(quantum, tiempoRestante[i]);
            tiempoRestante[i] -= tiempoEjec;
            tiempoActual += tiempoEjec;

            // Insertar procesos recién llegados durante la ejecución
            for (int j = 0; j < n; ++j) {
                if (!enCola[j] && procesos[j].llegada <= tiempoActual && tiempoRestante[j] > 0) {
                    cola.push(j);
                    enCola[j] = true;
                }
            }

            if (tiempoRestante[i] == 0) {
                p.finalizacion = tiempoActual;
                p.tiempo_retorno = p.finalizacion - p.llegada;
                p.tiempo_espera = p.tiempo_retorno - p.rafaga;
                p.estado = TERMINADO;
                completados++;
            } else {
                cola.push(i); // Reinsertar para próxima ronda
            }
        }

        tiempoTotal = tiempoActual;
    }

}
