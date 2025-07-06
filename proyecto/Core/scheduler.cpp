#include "scheduler.h"
#include "algorithms/fcfs.h"
#include "algorithms/sjf.h"
#include "algorithms/round_robin.h"
#include "algorithms/priority.h"

#include <iostream>

Scheduler::Scheduler(AlgoritmoPlanificacion alg, int q) {
    algoritmo = alg;
    quantum = q;
}

void Scheduler::ejecutar(std::vector<Proceso>& procesos, int& tiempoTotal) {
    switch (algoritmo) {
        case FCFS:
            fcfs::ejecutar(procesos, tiempoTotal);
            break;
        case SJF:
            sjf::ejecutar(procesos, tiempoTotal);
            break;
        case ROUND_ROBIN:
            rr::ejecutar(procesos, quantum, tiempoTotal);
            break;
        case PRIORITY:
            priority::ejecutar(procesos, tiempoTotal);
            break;

        default:
            std::cout << "Algoritmo no reconocido.\n";
            break;
    }
}

std::string Scheduler::nombreAlgoritmo() const {
    switch (algoritmo) {
        case FCFS: return "First Come First Served";
        case SJF: return "Shortest Job First";
        case ROUND_ROBIN: return "Round Robin";
        case PRIORITY: return "Priority Scheduling";
        default: return "Desconocido";
    }
}
