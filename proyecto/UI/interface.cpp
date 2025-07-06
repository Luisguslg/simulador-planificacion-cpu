#include "interface.h"
#include <iostream>

using namespace std;

AlgoritmoPlanificacion Interfaz::seleccionarAlgoritmo() {
    int opcion = 0;
    cout << "\nSeleccione algoritmo de planificación:\n";
    cout << "0. Comparar todos los algoritmos\n";
    cout << "1. FCFS\n";
    cout << "2. SJF\n";
    cout << "3. Round Robin\n";
    cout << "4. Prioridades\n";
    cout << ">> ";
    cin >> opcion;

    switch (opcion) {
        case 0: return COMPARAR_ALGORITMOS;  // ← CORRECTO AHORA
        case 1: return FCFS;
        case 2: return SJF;
        case 3: return ROUND_ROBIN;
        case 4: return PRIORITY;
        default:
            cout << "Opción inválida. Usando FCFS por defecto.\n";
            return FCFS;
    }
}

int Interfaz::solicitarQuantum() {
    int q;
    cout << "Ingrese quantum para Round Robin: ";
    cin >> q;
    return q;
}

vector<Proceso> Interfaz::crearProcesosManualmente() {
    int n;
    cout << "¿Cuántos procesos desea ingresar? ";
    cin >> n;

    vector<Proceso> procesos;

    for (int i = 0; i < n; ++i) {
        Proceso p;
        cout << "\nProceso #" << (i + 1) << "\n";
        cout << "ID: ";
        cin >> p.id;
        cout << "Tiempo de llegada: ";
        cin >> p.llegada;
        cout << "Tiempo de ráfaga: ";
        cin >> p.rafaga;
        cout << "Prioridad: ";
        cin >> p.prioridad;
        p.estado = NUEVO;

        procesos.push_back(p);
    }

    return procesos;
}
