#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "../process.h"
#include <vector>

namespace rr {
    void ejecutar(std::vector<Proceso>& procesos, int quantum, int& tiempoTotal);
}

#endif
