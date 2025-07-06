#ifndef FCFS_H
#define FCFS_H

#include "../process.h"
#include <vector>
#include <string>

namespace fcfs {
    void ejecutar(std::vector<Proceso>& procesos, int& tiempoTotal);
}

#endif
