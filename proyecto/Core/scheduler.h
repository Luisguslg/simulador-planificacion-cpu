#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include <vector>
#include <string>

enum AlgoritmoPlanificacion {
    COMPARAR_ALGORITMOS = -1,  // <- opción especial para comparar
    FCFS = 0,
    SJF,
    ROUND_ROBIN,
    PRIORITY
};


class Scheduler {
private:
    AlgoritmoPlanificacion algoritmo;
    int quantum;

public:
    Scheduler(AlgoritmoPlanificacion alg, int q = 2);
    void ejecutar(std::vector<Proceso>& procesos, int& tiempoTotal);
    std::string nombreAlgoritmo() const;
};

#endif
