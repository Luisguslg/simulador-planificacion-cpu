#include "metrics.h"
#include <iostream>
#include <iomanip>
#include <algorithm>  


using namespace std;

ResultadosSistema Metrics::calcular(const vector<Proceso>& procesos, int tiempoTotalCPU) {
    ResultadosSistema r{};
    double sumaRetorno = 0, sumaEspera = 0, sumaRespuesta = 0;
    double tiempoOcupado = 0;

    for (const auto& p : procesos) {
        sumaRetorno += p.tiempo_retorno;
        sumaEspera += p.tiempo_espera;
        sumaRespuesta += p.tiempo_respuesta;
        tiempoOcupado += p.rafaga; // Tiempo efectivo de uso de CPU
    }

    int n = procesos.size();
    r.promedioRetorno = sumaRetorno / n;
    r.promedioEspera = sumaEspera / n;
    r.promedioRespuesta = sumaRespuesta / n;

    if (tiempoTotalCPU > 0) {
        r.utilizacionCPU = 100.0 * (tiempoOcupado / tiempoTotalCPU);
    } else {
        r.utilizacionCPU = 0.0;
    }

    return r;
}


void Metrics::mostrar(const vector<Proceso>& procesos, const ResultadosSistema& resultados) {
    cout << "\n--- Métricas por Proceso ---\n";
    for (const auto& p : procesos) {
        cout << "Proceso " << p.id << ": ";
        cout << "Retorno=" << p.tiempo_retorno << ", ";
        cout << "Espera=" << p.tiempo_espera << ", ";
        cout << "Respuesta=" << p.tiempo_respuesta << "\n";
    }

    cout << "\n--- Métricas del Sistema ---\n";
    cout << fixed << setprecision(2);
    cout << "Promedio de Retorno:   " << resultados.promedioRetorno << "\n";
    cout << "Promedio de Espera:    " << resultados.promedioEspera << "\n";
    cout << "Promedio de Respuesta: " << resultados.promedioRespuesta << "\n";
    cout << "Utilización de CPU:    " << resultados.utilizacionCPU << "%\n";

    mostrarGantt(procesos);

}

void Metrics::mostrarGantt(const std::vector<Proceso>& procesos) {
    // Ordenar por tiempo de inicio de ejecución
    vector<Proceso> ordenados = procesos;
    sort(ordenados.begin(), ordenados.end(), [](const Proceso& a, const Proceso& b) {
        return a.inicio_ejecucion < b.inicio_ejecucion;
    });

    cout << "\nDiagrama de Gantt:\n";

    // Línea superior con procesos
    for (const auto& p : ordenados) {
        cout << "|--" << p.id << "--";
    }
    cout << "|\n";

    // Línea inferior con tiempos
    int tiempo = 0;
    for (const auto& p : ordenados) {
        cout << tiempo << setw(7) << "";
        tiempo = p.finalizacion;
    }
    cout << tiempo << "\n";
}
