#include "Core/scheduler.h"
#include "Core/process.h"
#include "Core/metrics.h"
#include "UI/interface.h"
#include "Utils/file_handler.h"

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Comparación de todos los algoritmos
void compararAlgoritmos(const std::vector<Proceso>& entrada, int quantum_rr = 2) {
    std::vector<std::pair<std::string, AlgoritmoPlanificacion>> algoritmos = {
        {"FCFS", FCFS},
        {"SJF", SJF},
        {"Round Robin", ROUND_ROBIN},
        {"Priority", PRIORITY}
    };

    std::cout << "\n=== Comparación de Algoritmos ===\n";
    std::cout << std::left << std::setw(15) << "Algoritmo"
              << std::setw(20) << "Retorno Prom."
              << std::setw(20) << "Espera Prom."
              << std::setw(20) << "Respuesta Prom."
              << std::setw(10) << "CPU %" << "\n";
    std::cout << std::string(85, '-') << "\n";

    // Variables para seleccionar automáticamente el mejor algoritmo
    std::string mejorAlgoritmo;
    double mejorEspera = 1e9;

    for (const auto& [nombre, tipo] : algoritmos) {
        std::vector<Proceso> copia = entrada;
        Scheduler planificador(tipo, quantum_rr);
        int tiempoTotal = 0;
        planificador.ejecutar(copia, tiempoTotal);

        auto resultados = Metrics::calcular(copia, tiempoTotal);

        std::cout << std::left << std::setw(15) << nombre
                  << std::setw(20) << std::fixed << std::setprecision(2) << resultados.promedioRetorno
                  << std::setw(20) << resultados.promedioEspera
                  << std::setw(20) << resultados.promedioRespuesta
                  << std::setw(10) << resultados.utilizacionCPU << "\n";

        // Elegir el mejor algoritmo según menor tiempo de espera promedio
        if (resultados.promedioEspera < mejorEspera) {
            mejorEspera = resultados.promedioEspera;
            mejorAlgoritmo = nombre;
        }
    }

    std::cout << std::string(85, '=') << "\n";
    std::cout << "✅ Conclusión: El algoritmo con menor tiempo de espera promedio es: **" 
              << mejorAlgoritmo << "**.\n";
}


int main() {
    cout << "====== Simulador de Planificación de CPU ======\n";

    // Paso 1: Selección del algoritmo
    AlgoritmoPlanificacion algoritmo = Interfaz::seleccionarAlgoritmo();

    // Comparación de algoritmos (opción 0)
    if (algoritmo == COMPARAR_ALGORITMOS) {
        cout << "\nIngrese nombre del archivo (ej: procesos_fcfs.txt): ";
        string archivo;
        cin >> archivo;
        vector<Proceso> procesos = FileHandler::cargarProcesosDesdeArchivo(archivo);
        if (procesos.empty()) {
            cerr << "❌ No se pudieron cargar procesos. Verifique el archivo o su formato.\n";
            return 1;
        }
        compararAlgoritmos(procesos);

        return 0;
    }

    // Paso 2: Configurar quantum si es Round Robin
    int quantum = (algoritmo == ROUND_ROBIN) ? Interfaz::solicitarQuantum() : 0;

    // Paso 3: Elección del método de carga
    vector<Proceso> procesos;
    cout << "\n¿Cómo desea cargar los procesos?\n";
    cout << "1. Manualmente\n";
    cout << "2. Desde archivo\n>> ";
    int metodo;
    cin >> metodo;




    if (metodo == 1) {
        procesos = Interfaz::crearProcesosManualmente();
    } else if (metodo == 2) {
        string archivo;
        cout << "Ingrese nombre del archivo (ej: procesos_fcfs.txt): ";
        cin >> archivo;
        procesos = FileHandler::cargarProcesosDesdeArchivo(archivo);
        if (procesos.empty()) {
        std::cerr << "❌ No se pudieron cargar procesos. Verifique el archivo.\n";
        return 1;
        }

    } else {
        cout << "Opción inválida. Finalizando simulación.\n";
        return 1;
    }

    // Paso 4: Ejecutar el algoritmo
    Scheduler planificador(algoritmo, quantum);
    int tiempoTotal = 0;
    planificador.ejecutar(procesos, tiempoTotal);

    cout << "\nAlgoritmo ejecutado: " << planificador.nombreAlgoritmo() << "\n";

    // Paso 5: Calcular y mostrar métricas + Gantt
    ResultadosSistema resultados = Metrics::calcular(procesos, tiempoTotal);
    Metrics::mostrar(procesos, resultados);

    // Paso 6: Guardar resultados
    string nombreSalida = "resultados_" + planificador.nombreAlgoritmo() + ".txt";
    FileHandler::guardarResultados(nombreSalida, procesos);

    cout << "\nSimulación finalizada.\n";
    return 0;
}
