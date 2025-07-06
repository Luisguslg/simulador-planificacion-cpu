#include "interface.h"
#include <iostream>
#include <limits>  // Para limpiar el buffer de entrada

using namespace std;

AlgoritmoPlanificacion Interfaz::seleccionarAlgoritmo() {
    int opcion = -1;
    cout << "\nSeleccione algoritmo de planificación:\n";
    cout << "0. Comparar todos los algoritmos\n";
    cout << "1. FCFS\n";
    cout << "2. SJF\n";
    cout << "3. Round Robin\n";
    cout << "4. Prioridades\n";
    cout << ">> ";
    cin >> opcion;

    if (cin.fail() || opcion < 0 || opcion > 4) {
        cerr << "❌ Opción inválida. Finalizando simulación.\n";
        exit(1);
    }

    switch (opcion) {
        case 0: return COMPARAR_ALGORITMOS;
        case 1: return FCFS;
        case 2: return SJF;
        case 3: return ROUND_ROBIN;
        case 4: return PRIORITY;
    }

    // Nunca se debería llegar aquí
    exit(1);
}

int Interfaz::solicitarQuantum() {
    int q;
    cout << "Ingrese quantum para Round Robin: ";
    cin >> q;

    if (cin.fail() || q <= 0) {
        cerr << "❌ Quantum inválido. Debe ser mayor a cero.\n";
        exit(1);
    }

    return q;
}

vector<Proceso> Interfaz::crearProcesosManualmente() {
    int n;
    cout << "¿Cuántos procesos desea ingresar? ";
    cin >> n;

    if (cin.fail() || n <= 0) {
        cerr << "❌ Número inválido de procesos.\n";
        exit(1);
    }

    vector<Proceso> procesos;

    for (int i = 0; i < n; ++i) {
        Proceso p;
        cout << "\nProceso #" << (i + 1) << "\n";

        cout << "ID: ";
        cin >> p.id;
        if (cin.fail()) { cerr << "❌ ID inválido.\n"; exit(1); }

        cout << "Tiempo de llegada: ";
        cin >> p.llegada;
        if (cin.fail() || p.llegada < 0) {
            cerr << "❌ Tiempo de llegada inválido.\n"; exit(1);
        }

        cout << "Tiempo de ráfaga: ";
        cin >> p.rafaga;
        if (cin.fail() || p.rafaga <= 0) {
            cerr << "❌ Tiempo de ráfaga inválido.\n"; exit(1);
        }

        cout << "Prioridad: ";
        cin >> p.prioridad;
        if (cin.fail() || p.prioridad <= 0) {
            cerr << "❌ Prioridad inválida.\n"; exit(1);
        }

        p.estado = NUEVO;
        procesos.push_back(p);
    }

    return procesos;
}
